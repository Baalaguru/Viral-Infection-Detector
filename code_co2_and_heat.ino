#include<DHT.h>
#include "MQ135.h"
#include<Wire.h>
#include <ESP8266WiFi.h>
#include<LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN,DHTTYPE);
#define RZERO 1
MQ135 gasSensor = MQ135(A0);
int val; 
int sensorPin = A0; 
int sensorValue = 0;

void setup() { 
  Wire.begin(D2,D3);
  lcd.init();
  lcd.backlight();
  Serial.begin(115200);  
  pinMode(sensorPin, INPUT);
    dht.begin();
 
} 
 
void loop() { 
  val = analogRead(A0); 
  Serial.print ("raw = ");
  lcd.setCursor(0,0);
  lcd.println(val); 
  Serial.println (val); 
  float zero = gasSensor.getRZero(); 
  Serial.print ("rzero: ");
  lcd.setCursor(0,1);
  lcd.println(zero);
  Serial.println (zero); 
  float ppm = gasSensor.getPPM();
  Serial.print ("ppm: ");
  lcd.setCursor(0,0);
  lcd.println(ppm);
  Serial.println (ppm); 
  delay(2000); 
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  float hi = dht.computeHeatIndex(f, h);

  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.print(" *C ");
  Serial.print(f);
  Serial.print(" *F\t");
  Serial.print("Heat index: ");
  Serial.print(hi);
  Serial.println(" *F");
}
