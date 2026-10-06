#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SDA_PIN 47
#define SCL_PIN 48

Adafruit_PWMServoDriver pca(0x40);

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);

  pca.begin();
  pca.setPWMFreq(50);
  delay(200);

  Serial.println("CH0 = LOW (0V) 3s");
  pca.setPWM(0, 0, 0);      // toujours LOW
  delay(3000);

  Serial.println("CH0 = HIGH (3.3V) 3s");
  pca.setPWM(0, 4096, 0);   // toujours HIGH (full ON)
  delay(3000);

  Serial.println("CH0 = PWM milieu 3s");
  pca.setPWM(0, 0, 2048);   // ~50%
  delay(3000);

  Serial.println("FIN");
}

void loop() {}