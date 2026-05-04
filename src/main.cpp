#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_BMP280.h>

BH1750 lightMeter;
Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(9600); 
  Wire.begin();
  
  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {

  }
  
  if (bmp.begin(0x76)) {

  }
}

void loop() {

  float lux = lightMeter.readLightLevel();
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure() / 100.0;
  int soilRaw = analogRead(A0);


  String dataPayload = "T:" + String(temp, 2) + 
                       ";P:" + String(pres, 2) + 
                       ";L:" + String(lux, 2) + 
                       ";S:" + String(soilRaw) + ";";


  byte checksum = 0;
  for (unsigned int i = 0; i < dataPayload.length(); i++) {
    checksum ^= (byte)dataPayload[i];
  }

  Serial.print("<");
  Serial.print(dataPayload);
  Serial.print("CS:");
  Serial.print(checksum);
  Serial.println(">");

  delay(5000);
}