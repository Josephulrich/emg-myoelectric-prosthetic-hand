#define FSR_PIN 1
const float Rfix = 10000;
const float Vref = 3.3;
const surface = 36*36;
float m ; //en gramme
float P = 0.00757 * m; 

/*P = F/S P(Pa), F(N), S(m²) ici S = 36x36mm²=0.001296m²
or F = m *a m(1000g)  a(9.81N/Kg = 0.00981N/g)
-> P=F/S
   P=(m*0.00981(g))/0.001296(m²)
   P(Pa) = 7.57*m(g)
   P(kPa) = 7.57*m(g)/1000
   P(kPa) = 0.00757*m(g)
 */
void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);  // important
}

void loop() 
{
  //1-ADC-TENSION--------------------------
  float Vout = analogRead(FSR_PIN);

  //2-TENISON-Rfsr---------------------------
  Rfsr = Rfix*(Vref/Vout - 1);

  //3-Resistance en force------------------

  //mesure expérimentale 
  /*
  COnstruire un tableau R<->F

  Masse(g)   |  ADC  |   V    |  Rfsr  |
  0
  100
  500
  1000
  
  */
  delay(20);
}