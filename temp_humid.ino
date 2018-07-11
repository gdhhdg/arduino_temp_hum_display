#include "Nokia_5110.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#define DHTPIN            6        // Pin which is connected to the DHT sensor.
#define DHTTYPE           DHT11     // DHT 11 

#define RST 13
#define CE 11
#define DC 10
#define DIN 9
#define CLK 8
#define BLPIN 5
#define PUSHBTN 2
int btnVal = 0;

Nokia_5110 lcd = Nokia_5110(RST, CE, DC, DIN, CLK);
DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

void setup() {
  /**
     Note: if instead of text being shown on the display, all the segments are on, you may need to decrease contrast value.
  */
  //lcd.setContrast(60); // 60 is the default value set by the driver

//backlight
pinMode(BLPIN, OUTPUT);
pinMode(PUSHBTN, INPUT);


  lcd.print("Please Wait ...");
  delay(1000);
  lcd.clear();
  // Initialize device.
  dht.begin();
  
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
 
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
      delay(1000);
  lcd.clear();
}

void loop() {
  digitalWrite(BLPIN, HIGH);
  // Delay between measurements.
  delay(delayMS);
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
   btnVal = digitalRead(PUSHBTN);
  
  if (isnan(event.temperature)) {
    lcd.println("reading...");
  }
  else {
    
    lcd.print("Temperature: ");
    lcd.setCursor(0,1);
    lcd.print(event.temperature);
    lcd.println(" *C");
    lcd.setCursor(0,2);
    lcd.print(event.temperature*9/5+32);
    lcd.print(" *F");
  
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if (isnan(event.relative_humidity)) {
    lcd.println("Error reading humidity!");
  }
  else {
    lcd.setCursor(0,4);
    lcd.print("Humidity: ");
    lcd.setCursor(0,5);
    lcd.print(event.relative_humidity);
    lcd.println("%");
   
  }

  }
