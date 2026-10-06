#include <Adafruit_NeoPixel.h>

#define LED_PIN   4        // Ta pin DATA
#define LED_COUNT 10


Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

// Fonction interpolation entre deux couleurs
uint32_t lerpColor(uint8_t r1, uint8_t g1, uint8_t b1,
                   uint8_t r2, uint8_t g2, uint8_t b2,
                   float t) {

  uint8_t r = r1 + (r2 - r1) * t;
  uint8_t g = g1 + (g2 - g1) * t;
  uint8_t b = b1 + (b2 - b1) * t;

  return strip.Color(r, g, b);
}

void afficherGradient() {

  for (int i = 0; i < LED_COUNT; i++) {

    float x = (float)i / (LED_COUNT - 1);   // position 0.0 → 1.0

    uint32_t couleur;

    if (x <= 0.5) {
      // De 0 à 0.5 : vert → jaune
      float t = x / 0.5;
      couleur = lerpColor(0, 255, 0,   255, 255, 0, t);
    } 
    else {
      // De 0.5 à 1 : jaune → rouge
      float t = (x - 0.5) / 0.5;
      couleur = lerpColor(255, 255, 0, 255, 0, 0, t);
    }

    strip.setPixelColor(i, couleur);
  }

  strip.show();
}

void setup() {
  strip.begin();
  strip.setBrightness(20);   // Tu peux monter jusqu’à 100 si alim solide
  strip.clear();
  strip.show();

  afficherGradient();
}

void loop() {
  // gradient fixe
}