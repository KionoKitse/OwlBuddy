

//Define pins
#define Sensor      A0  //Potentiometer
#define SensorPWR   9  //Potentiometer power
#define DriveB  10 //Green
#define DriveA  11 //Red

//Global variables
int SensorVal = 0;


void setup() {
  Serial.begin(9600);
  
  //Set pin mode
  pinMode(SensorPWR, OUTPUT);
  pinMode(Sensor, INPUT);
  pinMode(DriveA, OUTPUT);
  pinMode(DriveB, OUTPUT);
  

}

void loop() {
  //Serial.println(readVcc());
  SensorVal = ReadSensor(); //Read the Potentiometer
  Serial.println(SensorVal);
  DriveMotor(1);


}

//Function to run drive motor
void DriveMotor(bool Forward){
  if(Forward){
    digitalWrite(DriveA,HIGH);
    digitalWrite(DriveB,LOW);
    delay(10000);
    digitalWrite(DriveA,LOW);
  }
  else{
    digitalWrite(DriveB,HIGH);
    digitalWrite(DriveA,LOW);
    delay(10000);
    digitalWrite(DriveB,LOW);
  }
}

//Function that reads the the potentiometer value
int ReadSensor()
{
  digitalWrite(SensorPWR, HIGH); 
  delay(2);
  int result = analogRead(Sensor);
  //Need to modify this value
  digitalWrite(SensorPWR, LOW);
  return result;
}
//Function that calculates Vcc (in mV)
long readVcc() {
  
  // Read 1.1V reference against AVcc
  // set the reference to Vcc and the measurement to the internal 1.1V reference
  #if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
    ADMUX = _BV(REFS0) | _BV(MUX4) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #elif defined (__AVR_ATtiny24__) || defined(__AVR_ATtiny44__) || defined(__AVR_ATtiny84__)
    ADMUX = _BV(MUX5) | _BV(MUX0);
  #elif defined (__AVR_ATtiny25__) || defined(__AVR_ATtiny45__) || defined(__AVR_ATtiny85__)
    ADMUX = _BV(MUX3) | _BV(MUX2);
  #else
    ADMUX = _BV(REFS0) | _BV(MUX3) | _BV(MUX2) | _BV(MUX1);
  #endif  

  delay(2); // Wait for Vref to settle
  ADCSRA |= _BV(ADSC); // Start conversion
  while (bit_is_set(ADCSRA,ADSC)); // measuring

  uint8_t low  = ADCL; // must read ADCL first - it then locks ADCH  
  uint8_t high = ADCH; // unlocks both

  long result = (high<<8) | low;

  result = 1142437L / result; // Calculate Vcc (in mV); 1125300 = 1.1*1023*1000
  return result; // Vcc in millivolts
}
http://www.kcsemitech.com/upLoad/down/month_1902/201902261540192521.pdf

2 4
3 6
4 `6
-5 A `5
-6 G
7 8
-8 B

(1,?)    (8,Out)
(2,UL)    (7,GND)
(3,VL)    (6,GND)
(4,VCC)   (5,Out)     

VDD
UH
VH
