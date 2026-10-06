const int buzzerPin = 4;   // GPIO4

void setup() {
  pinMode(buzzerPin, OUTPUT);
}

void loop() {

  // Balayage de 1 kHz à 5 kHz
  for (int freq = 1000; freq <= 5000; freq += 100) {
    tone(buzzerPin, freq);   // génère la fréquence
    delay(200);              // reste 200 ms sur chaque fréquence
  }

  noTone(buzzerPin);         // arrêt du son
  delay(1000);               // pause avant de recommencer
}