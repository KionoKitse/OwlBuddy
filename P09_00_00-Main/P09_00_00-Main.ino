/*
   P09_00_00-Main
   Project: P09_00_00 OwlBuddy
   
   Notes:
 * Working on switch cases
 * Need to fill in code for MoveToZeroFine 
 * 

   Connections
   GND   - Servo potentiometer GND
   Pin02 - Servo potentiometer output
*/

//Sleep mode (interrupt)
#include <avr/sleep.h>
#define WakePin 2   //Pin to indicate when the timer has been activated

//Settings
int PotMax = 900;         //Max potentiometer value
int PotMin = 795;         //Min potentiometer value
long MinVoltage = 5000;   //Voltage level (mV) to trigger low voltage warning
int SetTimeDelay = 3000;  //Amount of time to wait before setting the timer
byte ZeroTolerance = 8;   //Tolerance on positioning of owl head at zero
byte ZeroPos = 542; //InvalidSensorA[] = {145, 939} -> ((939-145)/2)+145 = 542
 
//Define pins
#define LED         13  //Beacon LED
#define SensorPWR     9  //Potentiometer power
#define SensorA      A0  //Blue wire
#define SensorB      A1  //White wire //interrupt

//Global variables
byte CaseMode;
long BatteryVoltage;
bool LowBattery;
int HeadPos;
byte i;
int ValSensorA, ValSensorB;


void setup() 
{
  //Serial
  Serial.begin(9600);
  Serial.println("Setup");

  //Check battery status
  CheckBattery();

  //Sleep mode (interrupt)
  pinMode(WakePin,INPUT_PULLUP);  //Set internal pull up resistor

  //Set default case
  CaseMode = 0;

  //General pin setup
  pinMode(LED,OUTPUT);

  //Blink at setup done
  for(int i=0; i<5; i++)
  {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
}



void loop() 
{
  switch (CaseMode) 
  {
    case 1:
      Serial.println("Owl is awake getting set time");

      //Check for low battery
      CheckBattery();

      //Delay for setting the time 
      //Note: If low battery a delay is already applied
      if (!LowBattery)
      {
        delay(SetTimeDelay); 
      }

      //Get the time value
      GetHeadPos();
      Serial.println(HeadPos);
      ConvertTime();
      
      CaseMode = 2;
      break;
    case 2:
      Serial.println("case 2");
      break;
    default: 
      Serial.println("Sleep until activated");
      
      //Move the head to the zero position
      MoveToZeroFine();
      
      //ActivateSleep();
      CaseMode = 1;
      break;
  }
}
//Function to convert head position to time
void ConvertTime()
{
  //Delta senor for 1 min
  double DeltaMin = (double)(PotMax - PotMin)/60;
  Serial.println(DeltaMin);
}
//Function to read head position
void GetHeadPos()
{
  //Turn sensor on
  digitalWrite(SensorPWR, HIGH); 
  delay(2);
  
  //Read the sensor
  ValSensorA = analogRead(SensorA);
  ValSensorB = analogRead(SensorB);

  //Determine if SensorA is invalid
  if((ValSensorB > InvalidSensorA[0]) && (ValSensorB < InvalidSensorA[1]))
  {
    Serial.println("SensorA invalid");
  }
  //Determine if SensorB is invalid
  else if ((ValSensorA > InvalidSensorB[0]) && (ValSensorA < InvalidSensorB[1]))
  {
    Serial.println("SensorB invalid");
  }
  //Both sensors are valid
  else
  {
    Serial.println("Both sensors valid");
  }
    //Read value
  HeadPos = analogRead(Sensor);
  //Determine 
  
  //Turn sensor off
  digitalWrite(SensorPWR, LOW);
}


//Function to check for low battery
void CheckBattery()
{
  //Get the battery voltage
  BatteryVoltage = ReadVcc();
  Serial.println(BatteryVoltage);

  //Check for low power
  if (BatteryVoltage < MinVoltage)
  {
    LowBattery = true;

    //Blink LED to indicate low battery
    for(i=0; i<8; i++)
    {
      digitalWrite(LED,HIGH);
      delay(200);
      digitalWrite(LED,LOW);
      delay(200);
    }
  }
  else
  {
    LowBattery = false;
  }
}

//Function that calculates Vcc (in mV)
long ReadVcc() {
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

//Function to move owl head to zero 
void MoveToZeroFine()
{
  //Note: Interrupt is on SensorA so using SensorB to set position (Switch in HW)
  bool AtZero = false;

  //Turn on power for potentiometers
  digitalWrite(SensorPWR,HIGH);
  while(!AtZero)
  {
    //Read the sensor
    ValSensorB = analogRead(SensorB);

    //Need to rotate counter clockwise
    if(ValSensorB > (ZeroPos + ZeroTolerance))
    {
      StepMotor(0, 2);
    }
    //Need to rotate clockwise
    else if (ValSensorB < (ZeroPos - ZeroTolerance))
    {
      StepMotor(1, 2);
    }
    //Within nominal range
    else
    {
      AtZero = true;
    }
  }
  digitalWrite(SensorPWR,LOW);
}

//Function to step drive motor
void StepMotor(bool Clockwise, int Time)
{
  if(Clockwise)
  {
    digitalWrite(InA,LOW);
    digitalWrite(InB,HIGH);
    delay (Time);
    digitalWrite(InB,LOW);
  }
  else
  {
    digitalWrite(InB,LOW);
    digitalWrite(InA,HIGH);
    delay (Time);
    digitalWrite(InA,LOW);
  }
}
//Function that activates the sleep mode (interrupt)
void ActivateSleep()
{
  Serial.println("ActivateSleep");
    
  //Enable sleep mode
  sleep_enable();

  //Sleep mode settings
  attachInterrupt(0, WakeUp, LOW); //0 = Pin02
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  //Go to sleep
  sleep_cpu();
}

//Interrrupt routine
void WakeUp()
{
  sleep_disable();//Disable sleep mode
  detachInterrupt(0); //0 = Pin02
}



/*
***** ROLL THE CREDITS *****
  >> ReadVcc <<
  * Adjust VCC pin reading (didn't use)    https://forum.arduino.cc/index.php?topic=435065.0 
  * Use VCC pin to read voltage            https://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/

  >> ActivateSleep <<
  * Wake Arduino with interrupts     https://forum.arduino.cc/index.php?topic=435065.0 
 
***** Thanks everyone! *****
*/
