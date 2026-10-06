#define MOTOR_PIN 16  // TON GPIO

void setup() {
  pinMode(MOTOR_PIN, OUTPUT);

  // Sur certaines cartes ESP32, analogWrite existe directement.
  // Si ça compile, c'est gagné.
}

void loop() {
  analogWrite(MOTOR_PIN, 80);   // faible
  delay(1500);

  analogWrite(MOTOR_PIN, 150);  // moyen
  delay(1500);

  analogWrite(MOTOR_PIN, 255);  // fort
  delay(1500);

  analogWrite(MOTOR_PIN, 0);    // stop
  delay(1500);
}