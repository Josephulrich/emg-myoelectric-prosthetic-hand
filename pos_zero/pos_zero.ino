#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

// Pour les servos ANGLE (0,3,4,6)
#define SERVOMIN_ANG 150   // à ajuster
#define SERVOMAX_ANG 600   // à ajuster

// Pour les servos CONTINUS (1,2,5) → neutre (STOP)
#define SERVOMIN_CONT 150  // même base
#define SERVOMAX_CONT 600
#define PULSE_STOP   ((SERVOMIN_CONT + SERVOMAX_CONT) / 2)  // ≈ 1,5 ms [web:70][web:72]

void setup() {
  Wire.begin(47, 48);      // SDA=47, SCL=48
  Serial.begin(115200);
  delay(1000);

  pwm.begin();
  pwm.setPWMFreq(50);      // 50 Hz pour servos [web:71]

  // 1) Servos positionnels → 0° sur 0,3,4,6
  setAngleServo(0, 0);
  setAngleServo(3, 0);
  setAngleServo(4, 0);
  setAngleServo(6, 0);

  // 2) Servos continus → STOP sur 1,2,5
  setContinuousStop(1);
  setContinuousStop(2);
  setContinuousStop(5);

  Serial.println("Reset terminé : angle=0° sur 0,3,4,6 et STOP sur 1,2,5");
}

void loop() {
  // rien, tout est fait au setup
}

// ---------- Fonctions utilitaires ----------

// angle 0–180° → pulse pour servos ANGLE [web:7][web:71]
uint16_t angleToPulse(int angle) {
  if (angle < 0) angle = 0;
  if (angle > 180) angle = 180;
  return map(angle, 0, 180, SERVOMIN_ANG, SERVOMAX_ANG);
}

// Met un servo POSITIONNEL à un angle donné
void setAngleServo(uint8_t ch, int angle) {
  uint16_t p = angleToPulse(angle);
  pwm.setPWM(ch, 0, p);
  Serial.print("Canal "); Serial.print(ch);
  Serial.print(" -> "); Serial.print(angle); Serial.println(" deg");
}

// Met un servo CONTINU à l'arrêt (neutre)
void setContinuousStop(uint8_t ch) {
  pwm.setPWM(ch, 0, PULSE_STOP);
  Serial.print("Canal "); Serial.print(ch);
  Serial.println(" (continu) -> STOP");
}
