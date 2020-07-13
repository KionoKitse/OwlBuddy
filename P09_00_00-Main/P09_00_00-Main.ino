/*
 * void ReadSensor(): Reads the potentiometer
 * bool DeltaTime(): Checks if the head has moved (True/False)
 * void SetTime(): Sets the timer function
 * byte IntToMin(): Function that converts sensor time to minutes
*/

//Define pins
#define Sensor      A0	//Potentiometer
#define SensorPWR 	A1  //Potentiometer power
#define DriveServo  11
#define ServoB      12
#define LED         13  //Beacon LED

//Global variables
int Position = 0;
int SensorVal = 0;
byte SetTime = 0;   //Time set by the user
int NapTime = 0;    //Sensor time when the system takes a nap
int WakeTime = 0;   //Sensor time when the system wakes from a nap

//User settings
int SetTimeDelay = 3000; //Amount of time to wait before setting the time
long MinVoltage = 3000; //Voltage level to trigger low voltage warning




void setup() {
  Serial.begin(9600);
  
  //Set pin mode
  pinMode(DriveServo, OUTPUT);
  pinMode(ServoB, OUTPUT);
  pinMode(LED, OUTPUT);
  pinMode(SensorPWR, OUTPUT);
  pinMode(Sensor, INPUT);

  //Blink at setup
  for(int i=0; i<5; i++){
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }


}

void loop() {
  // Routine on wake up from sleep
  if(!CheckBattery()) //Battery voltage is low 
  {
    LowBattery();
  }
  else
  {
    //delay(SetTimeDelay); //Wait to set time
    Serial.println(readVcc());
    SensorVal = ReadSensor(); //Read the Potentiometer
    //Serial.println(scale_constant);
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

//Function that blinks the LED to indicate that the battery is low
void LowBattery(){
  for(int i=0; i<8; i++){
    digitalWrite(LED,HIGH);
    delay(200);
    digitalWrite(LED,LOW);
    delay(200);
  }
}
//Function that checks the battery voltage returns true or false 
bool CheckBattery(){
  long BatteryVoltage = readVcc();
  if (BatteryVoltage > MinVoltage){
    return true;
  }
  else{
    return false;
  }
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

/*
***** ROLL THE CREDITS *****
 * Adjust VCC pin reading (didn't use)    https://forum.arduino.cc/index.php?topic=435065.0 
 * Use VCC pin to read voltage		        https://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/

***** Thanks everyone! *****
*/
