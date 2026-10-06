#define EMG_PIN 46

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("Lecture EMG GPIO46");

  // ADC configuration ESP32-S3
  analogReadResolution(12);        // 0 → 4095
  analogSetAttenuation(ADC_11db);  // plage 0–3.3V
}

void loop() {

  int emg_raw = analogRead(EMG_PIN);

  // conversion tension
  float voltage = emg_raw * 3.3 / 4095.0;

  Serial.print("EMG RAW = ");
  Serial.print(emg_raw);
  Serial.print(" | Voltage = ");
  Serial.print(voltage, 3);
  Serial.println(" V");

  delay(5);   // ~200 Hz lecture
}