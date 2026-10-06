#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define SDA_PIN 47
#define SCL_PIN 48

Adafruit_PWMServoDriver pca(0x40);

// limites servo standard (à ajuster si besoin)
#define SERVOMIN 150   // 0°
#define SERVOMAX 600   // 180°

uint16_t angleToPulse(int angle) {
  angle = constrain(angle, 0, 180);
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);
}

void setup() {

  Wire.begin(SDA_PIN, SCL_PIN);

  pca.begin();
  pca.setPWMFreq(50);
  delay(10);

  // ===== position 0° =====
  pca.setPWM(0, 0, angleToPulse(0));
  pca.setPWM(6, 0, angleToPulse(0));

  delay(500);

  // ===== position 90° (milieu) =====
  pca.setPWM(0, 0, angleToPulse(90));
  pca.setPWM(6, 0, angleToPulse(90));

  pca.setPWM(0, 0, angleToPulse(30));
  pca.setPWM(6, 0, angleToPulse(30));

  pca.setPWM(0, 0, angleToPulse(180));
  pca.setPWM(6, 0, angleToPulse(180));
}

void loop() {
}