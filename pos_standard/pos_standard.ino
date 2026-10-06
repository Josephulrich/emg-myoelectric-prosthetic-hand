#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Ajuste si besoin pour ton servo
#define SERVOMIN 150   // ~0° [web:62]
#define SERVOMAX 600   // ~180° [web:62]

uint16_t angleToPulse(int angle) {
  if (angle < 0) angle = 0;
  if (angle > 200) angle = 200;      // on limite la consigne de test
  // map sur 0–180 : au‑delà de 180 tu seras de toute façon en butée mécanique
  return map(angle, 0, 180, SERVOMIN, SERVOMAX);  // [web:38][web:144]
}

void setup() {
  Wire.begin(47, 48);        // SDA=47, SCL=48 [web:62]
  pwm.begin();
  pwm.setPWMFreq(50);        // 50 Hz [web:38]
  delay(500);
}

void loop() {
  // Monter de 0° à 200° (le servo va saturer vers sa butée, ~180°)
  for (int angle = 0; angle <= 200; angle += 10) {
    uint16_t p = angleToPulse(angle);
    pwm.setPWM(3, 0, p);     // channel 3
    delay(400);
  }

  delay(1000);

  // Redescendre de 200° à 0°
  for (int angle = 200; angle >= 0; angle -= 10) {
    uint16_t p = angleToPulse(angle);
    pwm.setPWM(3, 0, p);
    delay(400);
  }

  delay(2000);
}
 