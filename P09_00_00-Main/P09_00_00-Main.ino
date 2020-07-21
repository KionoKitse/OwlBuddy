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
long MinVoltage = 5000;   //Voltage level (mV) to trigger low voltage warning
int SetTimeDelay = 3000;  //Amount of time to wait before setting the timer
byte ZeroTolerance = 8;   //Tolerance on positioning of owl head at zero
byte ZeroPos = 542; //InvalidSensorA[] = {145, 939} -> ((939-145)/2)+145 = 542
 
//Define pins
#define LED         13  //Beacon LED
#define SensorPWR     9  //Potentiometer power
#define SensorA      A0  //Blue wire
#define SensorB      A1  //White wire //interrupt
#define DriveA       10  //Drive motor H bridge brown
#define DriveB       11  //Drive motot H bridge purple

//Global variables (General)
byte CaseMode;
int HeadPos;
int SetTime;
byte i;
bool Sleeping;

//Global variables (Potentiometer Functions)
int ValSensorA;
int ValSensorB;
bool StableA;
bool StableB;

//Global variables (Battery Control Functions)
long BatteryVoltage;
bool LowBattery;

//Potentiometer Calibration
int ValidSensorA[] = {1020, 1990};
int ValidSensorB[] = {2020, 2990};
double Slope = -0.03472536;
double Intercept = 87.37676476;
int OffsetSensorA = 170;


void setup() {
  //Serial
  Serial.begin(9600);
  Serial.println("Setup");

  //Check battery status
  CheckBattery();

  //Sleep mode (interrupt)
  pinMode(WakePin,INPUT_PULLUP);  //Set internal pull up resistor

  //Set default case
  CaseMode = 0;

  //Apply sensor offset
  ValidSensorA[0] = ValidSensorA[0]+OffsetSensorA;
  ValidSensorA[1] = ValidSensorA[1]+OffsetSensorA;

  //General pin setup
  pinMode(LED,OUTPUT);
  pinMode(SensorPWR,OUTPUT);

  //Blink at setup done
  for(int i=0; i<5; i++)
  {
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }
}



void loop() {
  switch (CaseMode) 
  {
    case 1:
      //Serial.println("Owl is awake getting set time");

      
      //Check for low battery
      CheckBattery();

      //Delay for setting the time 
      //Note: If low battery a delay is already applied
      if (!LowBattery)
      {
        delay(SetTimeDelay); 
      }
      
      //Get the time value based on unknown position
      HeadPos = GetUnkownPos();
      SetTime = Pos2Time(HeadPos);
      Serial.print("Set Timer: ");
      Serial.println(SetTime);
      
      CaseMode = 2;
      break;
    case 2:
      Serial.println("Sleep until time is up");
      Sleeping = true;
      while (Sleeping)
      {
        
      }
      break;
    default: 
      Serial.println("Sleep until activated");
      
      //Move the head to the zero position
      //MoveToZeroFine(); //TODO
      
      //ActivateSleep();
      CaseMode = 1;
      break;
  }
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

//>>>DONE<<<


//Function to step drive motor
void StepMotor(bool Clockwise, int Time)
{
  if(Clockwise)
  {
    digitalWrite(DriveA,LOW);
    digitalWrite(DriveB,HIGH);
    delay (Time);
    digitalWrite(DriveB,LOW);
  }
  else
  {
    digitalWrite(DriveB,LOW);
    digitalWrite(DriveA,HIGH);
    delay (Time);
    digitalWrite(DriveA,LOW);
  }
}

// >> Potentiometer Functions << 
int Pos2Time(int Position){                 //Convert sensor position to time
  //Calculate time based on position to time equation
  double Time = Slope*Position+Intercept;

  //Round values to an integer
  int Result = round(Time);

  //Check for wrap around values
  if(Result < 0)
  {
    Result = Result+60; 
  }

  return Result;
}
int GetUnkownPos(){                         //Get unknown position
  int Position;
  //Turn sensor on
  digitalWrite(SensorPWR, HIGH); 
  delay(2);
    
  //Get sensor reading
  ValSensorA = analogRead(SensorA)+1000+OffsetSensorA;
  ValSensorB = analogRead(SensorB)+2000;

  //Turn sensor off
  digitalWrite(SensorPWR, LOW);

  //Serial.print(ValSensorA);
  //Serial.print(",");
  //Serial.print(ValSensorB);
  //Serial.print(": ");

  //Check for valid readings
  bool SensorAValid = SensorValid(ValSensorA, ValidSensorA);
  bool SensorBValid = SensorValid(ValSensorB, ValidSensorB);

  //Check reading stability if both readings are valid
  if(SensorAValid && SensorBValid)
  {
    StableA = true;
    StableB = true;
    CheckStable();
    CheckStable();

    //Both readings are actually stable use SensorA
    if (StableA && StableB)
    {
      //Serial.print("Stable ");
      Position = ValSensorA;
    }
    //Sensor B was unstable so use SensorA
    else if (StableA)
    {
      Position = ValSensorA;
    }
    //SensorA was unstable so use SensorB
    else 
    {
      Position = ValSensorB;
    }
  }
  //SensorB was unstable so use SensorA
  else if (SensorAValid)
  {
    Position = ValSensorA;
  }
  //SensorA was unstable so use SensorB
  else
  {
    Position = ValSensorB;
  }
  
  //Serial.println(Position);
  return Position;
}
bool SensorValid(int Value, int Limits[2]){ //Check if sensor reading is valid
  if ((Value > Limits[0]) && (Value < Limits[1]))
  {
    return true;
  }
  return false;
}
void CheckStable(){                         //Check stability of sensors over 10 readings
  //Calculate the sum of 10 measurements
  unsigned int TotalA = 0;
  unsigned int TotalB = 0;
  for (i=0; i<10; i++)
  {
    //Turn sensor on
    digitalWrite(SensorPWR, HIGH); 
    delay(2);
    
    //Get sensor reading
    ValSensorA = analogRead(SensorA)+1000+OffsetSensorA;
    ValSensorB = analogRead(SensorB)+2000;

    //Turn sensor off
    digitalWrite(SensorPWR, LOW);

    //Calculate the sum
    TotalA = TotalA + ValSensorA;
    TotalB = TotalB + ValSensorB;
  }

  //Calculate theoretical total
  unsigned int TotalATheo = 10*ValSensorA;
  unsigned int TotalBTheo = 10*ValSensorB;

  //Determine how much the actual total and the theoretical total differ
  int DeltaA = TotalATheo - TotalA;
  int DeltaB = TotalBTheo - TotalB;
  DeltaA = abs(DeltaA);
  DeltaB = abs(DeltaB);

  //Determine which reading is valid
  if (DeltaA > 11)
  {
    StableA = false;
  }
  if (DeltaB > 11)
  {
    StableB = false;
  }
}

// >> Battery Control Functions <<
void CheckBattery(){                        //Check for low battery
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
long ReadVcc() {                            //Calculate Vcc (in mV)
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

// >> Sleep Functions <<
void ActivateSleep(){                       //Activate the sleep mode (interrupt)
  Serial.println("ActivateSleep");
    
  //Enable sleep mode
  sleep_enable();

  //Sleep mode settings
  attachInterrupt(0, WakeUp, LOW); //0 = Pin02
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  //Go to sleep
  sleep_cpu();
}
void WakeUp(){                              //Interrrupt routine
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
