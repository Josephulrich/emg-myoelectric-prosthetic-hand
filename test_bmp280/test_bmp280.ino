#include <Wire.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(115200);

  Wire.begin(47, 48);   // I2C sur GPIO8 et GPIO9  

  if (!bmp.begin(0x76)) {
    Serial.println("BMP280 non trouvé !");
    while (1);
  }

  Serial.println("BMP280 OK !");
}

void loop() {
  Serial.print("Température: ");
  Serial.print(bmp.readTemperature());
  Serial.println(" °C");

  Serial.print("Pression: ");
  Serial.print(bmp.readPressure() / 100.0);
  Serial.println(" hPa");

  delay(1000);
}