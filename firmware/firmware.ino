#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_BMP280.h>

#define sda 47
#define scl 48
#define BUZZ_PIN 15
#define vibro 16
#define sig_emg 46
#define FSR 1 
#define pot 20
#define LED_PIN 4




/*********ruuban led***************/
#define LED_PIN 4
#define LED_COUNT 10
#define led_type WS2812B
#define brightness 80

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
/************************/

const float FSR_max = 10.0; //Kg
const float Temp_max = 40;//°C
const float vref = 3.3;
const float R0 = 10000.0;
const float gain_fsr = 1.0f;



/******BMP280 sensor Temp************/
Adafruit_BMP280 bmp;
/************************/


float adcToRes(int adc)//ADC---->RESISTANCE
{
  if (adc <= 0) return 1e9;                 
  float vout = (adc / 4095.0f) * vref;
  if (vout < 0.001f) vout = 0.001f;         
  float Rfsr = (vref * R0 / vout) - R0;
  return Rfsr;
}


float FRStoKG(float Rohm) //Resistance 
{
  float Rk = Rohm/1000;
  if(Rk<=0.0f)return 0.0f;

  //Etude scientifique
  float F_N = gain_fsr*271.0f*pow(Rk, -0.69f); //fprce approximatie en Newton

  float m_kg = F_N/9.81f;
  if(m_kg>10.0) m_kg = 10.0f; //limite normative du capteur 
  if(m_kg<0.0) m_kg  = 0.0f;

  return m_kg;
}

float fsrTokg_estimate(int adc)
{
  float R = adcToRes(adc);
  return FRStoKG(R);
}

//////////////////////////////////retour haptique//////////////////////////////////////

void updateFeedback(float level) {
  if (level < 0.0f) level = 0.0f;
  if (level > 1.0f) level = 1.0f;

  int ledsOn = (int)round(level * LED_COUNT);
  if (ledsOn > LED_COUNT) ledsOn = LED_COUNT;

  // dégradé vert -> rouge
  uint8_t r = (uint8_t)(255 * level);
  uint8_t g = (uint8_t)(255 * (1.0f - level));
  uint8_t b = 0;

  for (int i = 0; i < LED_COUNT; i++) {
    if (i < ledsOn) strip.setPixelColor(i, strip.Color(r, g, b));
    else            strip.setPixelColor(i, 0, 0, 0);
  }
  strip.show();


////vibro proportio
int duty = (int)(255*level);
ledcWrite(vibro, duty); 
}
//// température/buzzer
void checktemp()
{
  float t = bmp.readTemperature();

  if (t >= Temp_max)
  {
    ledcWrite(BUZZ_PIN, 128);   // ON (son)
  }
  else
  {
    ledcWrite(BUZZ_PIN, 0);     // OFF
  }
}

void checkcoude()
{
  int adc_val = analogRead(pot);
  Serial.print("POT(GPIO");
  Serial.print(pot);
  Serial.print(") = ");
  Serial.println(adc_val);
}

//////////////////////////////////////////////////////////////////////////////////
void setup() 
{
  Serial.begin(115200);
  analogReadResolution(12); //0 - 4095
  analogSetAttenuation(ADC_11db);  // important pour vref = 3.3v

  // Vibromoteurs PWM via 2N2222 sur GPIO16
// Vibromoteur PWM
      // Vibromoteur PWM
  ledcAttach(vibro, 2000, 8);
  ledcWrite(vibro, 0);      

  // Buzzer passif (PWM audio)
  ledcAttach(BUZZ_PIN, 2000, 8);   // 2 kHz
  ledcWrite(BUZZ_PIN, 0);           // OFF

  // Ruban LED  
  strip.begin();
  strip.show();
  strip.setBrightness(80);

  // I2C + BMP280
  Wire.begin(sda, scl);
  if (!bmp.begin(0x76)) {          // adresse BMP280 courante 
    Serial.println("BMP280 non trouve");
  }

  Serial.println("Init OK (FSR + LEDs + Vibro PWM + BMP)");
}

void loop()
{
  // ===== Lecture FSR =====
  int adc_fsr = analogRead(FSR);

  float Rfsr = adcToRes(adc_fsr);
  float force_kg = FRStoKG(Rfsr);

  float level = force_kg / FSR_max;
  updateFeedback(level);

  // ===== Lecture température =====
  float temperature = bmp.readTemperature();

  // ===== Affichage Moniteur Série =====
 Serial.printf(
  "FSR=%4d | Force=%5.2f kg | Temp=%5.2f C\n",
  adc_fsr,
  force_kg,
  temperature
);
  checktemp();
  checkcoude();
  delay(500); // rafraîchissement 2 Hz
}
