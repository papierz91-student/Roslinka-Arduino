#include <Wire.h>
#include <BH1750.h>
#include <Adafruit_BMP280.h>

BH1750 lightMeter;
Adafruit_BMP280 bmp; 

void setup() {
  Serial.begin(9600); 
  Wire.begin();
  
  Serial.println(F("--- START STACJI POGODOWEJ (UNO) ---"));

  if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    Serial.println(F("BH1750: OK"));
  } else {
    Serial.println(F("BH1750: BLAD (Sprawdz adres 0x23 i luty!)"));
  }
  if (bmp.begin(0x76)) {
    Serial.println(F("BMP280: OK"));
  } else {
    Serial.println(F("BMP280: BLAD (Sprawdz adres 0x76 i luty!)"));
  }
}

void loop() {
  float lux = lightMeter.readLightLevel();
  float temp = bmp.readTemperature();
  float pres = bmp.readPressure() / 100.0;

  int soilRaw = analogRead(A0);

  Serial.print("<");

  Serial.print("T:"); Serial.print(temp, 2); Serial.print(";");
  Serial.print("P:"); Serial.print(pres, 2); Serial.print(";");
  Serial.print("L:"); Serial.print(lux, 2);  Serial.print(";");
  Serial.print("S:"); Serial.print(soilRaw);

  Serial.println(">");

  delay(2000);
}