// Arduino UNO (simulation)
// Buzzer passif sur BUZZ_PIN (avec transistor recommandé)
// Potentiomètre sur A0 (3.3/5V -> pot -> GND, curseur -> A0)

const int BUZZ_PIN = 4;   // PWM pas obligatoire avec tone(), mais 5 est OK
const int POT_PIN  = A0;  // entrée analogique

void beep(int freqHz, int durationMs, int volumePercent)
{
  volumePercent = constrain(volumePercent, 0, 100);

  // "Volume" = rapport ON/OFF rapide (gating)
  const int gatePeriodMs = 5; // 200 Hz
  int onMs  = (gatePeriodMs * volumePercent) / 100;
  int offMs = gatePeriodMs - onMs;

  unsigned long t0 = millis();
  while (millis() - t0 < (unsigned long)durationMs) {
    if (onMs > 0) {
      tone(BUZZ_PIN, freqHz);
      delay(onMs);
    }
    noTone(BUZZ_PIN);
    delay(offMs);
  }
  noTone(BUZZ_PIN);
}

void setup() {
  Serial.begin(115200);
  pinMode(BUZZ_PIN, OUTPUT);
}

void loop() {
  int raw = analogRead(POT_PIN);                 // 0..1023 (UNO)
  int vol = map(raw, 0, 1023, 0, 100);           // 0..100%

  // Démo simple : 3 bips, volume au pot
  beep(800,  200, vol); delay(150);
  beep(1500, 200, vol); delay(150);
  beep(2500, 250, vol); delay(400);

  Serial.print("Volume % = ");
  Serial.println(vol);
}