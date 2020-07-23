/*
   P09_00_00-Test
   Project: P09_00_00 OwlBuddy
   Notes: Test place

   Connections
   GND   - Potentiometer GND
   Pin02 - Potentiometer output
*/

//Sleep mode (interrupt)
#include <avr/sleep.h>
#define WakePin 2   //Pin to indicate when the timer has been activated

//Settings
byte AppxPosErr = 10;
byte FinePosErr = 5;

//Global variables (General)
byte i;
bool Nap;
byte TimePos;
byte SensorNumber;
int  SensorValue;

//Define pins
#define SensorPWR     9  //Potentiometer power
#define SensorA      A0  //Blue wire
#define SensorB      A1  //White wire 
#define DriveA       3  //Drive motor H bridge Pin02 White 10
#define DriveB       4  //Drive motot H bridge Pin03 Blue 11

//Global variables (Potentiometer Functions)
int ValSensorA;
int ValSensorB;
bool StableA;
bool StableB;

//Global variables (Movement)
byte HeadTime; //Last know position of the head (time)
bool ActiveSensor; //AorB
int TempSensor, TempOffset;


//Potentiometer Calibration
//int ValidSensorA[] = {1020, 1990};
//int ValidSensorB[] = {2020, 2990};
int ValidSensorA[] = {20, 990};
int ValidSensorB[] = {20, 990};
double Slope = -28.94;
double Intercept = 2481.87;
int OffsetSensorA = 168;
byte TimeSensorA[] = {11, 44};
byte WrapAroundVal = 44;

void setup()
{
  //Serial
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Setup");

    //Sleep mode (interrupt)
  pinMode(WakePin,INPUT_PULLUP);  //Set internal pull up resistor


  //General pin setup
  pinMode(SensorPWR, OUTPUT);
  pinMode(DriveA, OUTPUT);
  pinMode(DriveB, OUTPUT);

  //Get unknown position
  GetUnkownPos();
  Serial.println(Pos2Time(SensorValue));



/*
  SensorNumber = 2;
  SensorValue = 58;
  Move2TimeKnown(0, -1);
  */
}



void loop()
{

  GetPosition();

  /*
    Serial.println("");
    int SetTime = 2;

    //Configure timer
    long EndTime = millis()+((long)SetTime * 60000L);
    long Minute = millis()+60000L;
    Serial.println(EndTime);

    //Timer is active
    Serial.println("Start");
    while (millis() < EndTime)
    {
    //Search for changes in set time
    Move2TimeKnown(48, 0);

    //Change move head position every min
    if (millis() >= Minute)
    {
      //Set next minute
      Minute = millis()+60000L;
      Serial.println("A min");
    }

    }
    Serial.println("End");
  */
}

void GetPosition(){
  //Turn sensor on
  digitalWrite(SensorPWR, HIGH);
  delay(2);

  //Get sensor reading
  ValSensorA = analogRead(SensorA);
  ValSensorB = analogRead(SensorB);

  //Turn sensor off
  digitalWrite(SensorPWR, LOW);

  Serial.print(ValSensorA);
  Serial.print(",");
  Serial.print(ValSensorB);
  Serial.print(",");

  //Check for valid readings
  bool SensorAValid = SensorValid(ValSensorA, ValidSensorA);
  bool SensorBValid = SensorValid(ValSensorB, ValidSensorB);
  
//  Serial.print(SensorAValid);
//  Serial.print(",");
//  Serial.print(SensorBValid);
//  Serial.print(",");

  //One of the sensors were invalid
  if(!SensorAValid || !SensorBValid)
  {
    //Serial.print("S");
    //SensorA was valid
    if(SensorAValid)
    {
      SensorValue = ValSensorA;
      SensorNumber = 1;
    }
    //SensorB was valid
    else
    {
      SensorValue = ValSensorB;
      SensorNumber = 2;
    }
  }
  //Both sensors were valid
  else
  {
    //Serial.print("H");
    
    //Calculate the difference between SensorA and SensorB
    int DeltaAB = ValSensorA-ValSensorB;
    //Serial.print(DeltaAB);

    //Both readings are actualy valid use SensorA
    if(abs(DeltaAB) > 700)
    {
      //Serial.print("B");
      SensorValue = ValSensorA;
      SensorNumber = 1;
    }
    //Within bad zone
    else
    {
      //Serial.print("D");
      //SensorA is valid
      if(DeltaAB > 0)
      {
        SensorValue = ValSensorA;
        SensorNumber = 1;
      }
      //SensorB is valid
      else
      {
        SensorValue = ValSensorB;
        SensorNumber = 2;
      }
    }
    
  }
  Serial.println(SensorValue);
}

void Move2TimeKnown(int Time, int Direction)
{
  //Path variables
  byte SensorPath[6];
  int PositionPath[6];
  byte PathId = 0;
  int Delta;

  //Set first value
  PositionPath[0] = SensorValue;
  SensorPath[0] = SensorNumber;
  int TimeIndex = SensorValue;

  //Moving clockwise with time getting smaller
  if (Direction < 0)
  {
    Serial.println("Clockwise");

    //Calculate amount of movement
    if (SensorValue > Time)
    {
      Delta = SensorValue - Time;
    }
    else
    {
      Delta = SensorValue + 60 - Time;
    }

    //Check already in transition
    if (SensorValue == TimeSensorA[0])
    {
      SensorNumber = 2;
    }
    if (SensorValue == TimeSensorA[1] + 1)
    {
      SensorNumber = 1;
    }

    //Look for the rest of the path
    for (byte i = 1; i <= Delta; i++)
    {
      //Set time index
      TimeIndex--;
      //Handle wrap around
      if (TimeIndex < 0)
      {
        TimeIndex = 59;
      }

      //Set last value and break out
      if (i == Delta)
      {
        PathId++;
        PositionPath[PathId] = TimeIndex;
        SensorPath[PathId] = SensorNumber;
        PathId++;
        break;
      }

      //In SensorA range
      if (SensorNumber == 1)
      {
        //Search for exit SensorA
        if (TimeIndex == TimeSensorA[0])
        {
          PathId++;
          PositionPath[PathId] = TimeIndex;
          SensorPath[PathId] = 1;
          SensorNumber = 2;
        }
      }
      //In SensorB range
      else
      {
        //Search for exit SensorB
        if (TimeIndex == TimeSensorA[1] + 1)
        {
          PathId++;
          PositionPath[PathId] = TimeIndex;
          SensorPath[PathId] = 2;
          SensorNumber = 1;
        }
      }
    }
  }
  //Moving clockwise with time getting larger
  else
  {
    Serial.println("Counter Clockwise");

    //Calculate amount of movement
    if (SensorValue < Time)
    {
      Delta = Time - SensorValue;
    }
    else
    {
      Delta = Time + 60 - SensorValue;
    }

    //Check already in transition
    if (SensorValue == TimeSensorA[1])
    {
      SensorNumber = 2;
    }
    if (SensorValue == TimeSensorA[0] - 1)
    {
      SensorNumber = 1;
    }

    //Look for the rest of the path
    for (byte i = 1; i <= Delta; i++)
    {

      //Set time index
      TimeIndex++;

      //Handle wrap around
      if (TimeIndex > 59)
      {
        TimeIndex = 0;
      }

      //Set last value and break out
      if (i == Delta)
      {
        PathId++;
        PositionPath[PathId] = TimeIndex;
        SensorPath[PathId] = SensorNumber;
        PathId++;
        break;
      }

      //In SensorA range
      if (SensorNumber == 1)
      {
        //Search for exit SensorA
        if (TimeIndex == TimeSensorA[1])
        {
          PathId++;
          PositionPath[PathId] = TimeIndex;
          SensorPath[PathId] = 1;
          SensorNumber = 2;
        }
      }
      //In SensorB range
      else
      {
        //Search for exit SensorB
        if (TimeIndex == TimeSensorA[0] - 1)
        {
          PathId++;
          PositionPath[PathId] = TimeIndex;
          SensorPath[PathId] = 2;
          SensorNumber = 1;
        }
      }
    }

  }
  //Print results
  for (byte i = 0; i < PathId; i++)
  {
    Serial.print(PositionPath[i]);
    Serial.print(",");
    Serial.println(SensorPath[i]);
  }

  //Convert time to position
  for (byte i = 1; i < PathId; i++)
  {
    PositionPath[i] = Time2Pos(PositionPath[i]);
  }

  //Print results
  Serial.println("Position path");
  for (byte i = 0; i < PathId; i++)
  {
    Serial.print(PositionPath[i]);
    Serial.print(",");
    Serial.println(SensorPath[i]);
  }

//byte AppxPosErr = 10;
//byte FinePosErr = 5;
  
  //Move clockwise
  if (Direction < 0)
  {
    //Turn sensor on
    digitalWrite(SensorPWR, HIGH);
    delay(2);

    //Turn on motors for clockwise movement
    digitalWrite(DriveB, LOW);
    digitalWrite(DriveA, HIGH);

    //Move approximate
    for (byte i = 1; i < PathId - 1; i++) //2916,2 - 2164,1 - 2482,2
    {
      //Set settings
      if (SensorPath[PathId] == 1)
      {
        TempSensor = SensorA;
        TempOffset = 1000+OffsetSensorA;
      }
      else
      {
        TempSensor = SensorB;
        TempOffset = 2000;
      }

      //Continue until reaching approximate position
      while(abs(PositionPath[PathId]-SensorValue) > AppxPosErr)
      {
        SensorValue = analogRead(TempSensor) + TempOffset;
      }
    }
    //Turn off motors
    digitalWrite(DriveA, LOW);


    //Move fine
    //Turn off sensor
    digitalWrite(SensorPWR, LOW);
  }

  //Move counter clockwise
  else
  {
  }

  /*

    //Determine read sensor
    byte ReadSensor; //SensorA, SensorB, SensorAB
    if (Time > 12 && Time < 46)
    {
      Serial.println("SensorA");
      ReadSensor = 0;
    }
    else if (Time > 47 || Time < 11)
    {
      Serial.println("SensorB");
      ReadSensor = 1;
    }
    else // 11-12 && 46-47
    {
      Serial.println("Both");
      ReadSensor = 2;
    }

    //Convert time for wrap around values
    if (Time > 46)
    {
      Time = Time - 60;
    }

    //Calculate head position
    int Position = round((Time - Intercept) / Slope);

    //Now I have a sensor number and an expected stop value
    //Check for sensor transitions



    //Determine read sensor

    Serial.println(Position);
  */
}

double SampleVariance(double Values[20])
{
  //Variables
  double Avg = 0;
  double Numerator = 0;

  //Calculate average
  for (byte i=0; i<20; i++)
  {
    Avg = Avg + Values[i];
  }
  Avg = Avg/20;

  //Calculate numerator
  for (byte i=0; i<20; i++)
  {
    Numerator = Numerator + ((Values[i] - Avg)*(Values[i] - Avg));
  }
  Serial.print("Numerator: ");
  Serial.println(Numerator);

  double Result = Numerator/20;
  return Result;
  
}
/*
  void CalibrateTimer()
  {
  byte Position = 0;
  Serial.print("Move to Zero ");
  delay(5000);
  for (int i=0; i<60; i++)
  {
     Serial.print("Move to position: ");
     Serial.print(Position);
     Serial.print(": ");
     delay(5000);

     TimeTable[i] = GetUnkownPos();
     digitalWrite(LED,HIGH);
     delay(100);
     digitalWrite(LED,LOW);

     Position++;
  }
  Serial.println("");
  for(int i=0; i<60; i++)
  {
    Serial.print(TimeTable[i]);
    Serial.print(" ");
  }
  Serial.println("");

  }
*/
//int TimeTable[60] = {2505,2482,2462,2433,2408,2375,2337,2308,2278,2247,2207,2189,1970,1953,1928,1898,1874,1852,1825,1797,1773,1745,1718,1691,1667,1638,1614,1591,1559,1517,1486,1447,1425,1397,1365,1338,1303,1277,1252,1223,1184,1156,1130,1110,1086,1059,1029,2882,2858,2831,2800,2774,2751,2722,2697,2673,2644,2619,2593,2562};

int Time2Pos(int Time) {
  //Check for wrap around values
  if (Time > WrapAroundVal)
  {
    Time = Time - 60;
  }
  //Calculate position based on calibration
  double Position = Slope * Time + Intercept;
  return round(Position);
}

int Pos2Time(int Pos)
{
  //Calculate time based on calibration
  double Time = ((double)Pos-Intercept)/Slope;
  Serial.println(Time);
  //Check for wrap around
  if (Time < 0)
  {
    Time = Time + 60;
  }
   Serial.println(Time);
  return round(Time);
}

// >> Potentiometer Functions << 
void GetUnkownPos() {                         //Get unknown position
  //Turn sensor on
  digitalWrite(SensorPWR, HIGH);
  delay(2);

  //Get sensor reading
  ValSensorA = analogRead(SensorA) + 1000 + OffsetSensorA;
  ValSensorB = analogRead(SensorB) + 2000;

  //Turn sensor off
  digitalWrite(SensorPWR, LOW);

  Serial.print(ValSensorA);
  Serial.print(",");
  Serial.print(ValSensorB);
  Serial.print(": ");

  //Check for valid readings
  bool SensorAValid = SensorValid(ValSensorA, ValidSensorA);
  bool SensorBValid = SensorValid(ValSensorB, ValidSensorB);

  //Check reading stability if both readings are valid
  if (SensorAValid && SensorBValid)
  {
    StableA = true;
    StableB = true;
    CheckStable();
    CheckStable();

    //Both readings are actually stable use SensorA
    if (StableA && StableB)
    {
      //Serial.print("Stable ");
      SensorValue = ValSensorA;
      SensorNumber = 1;
    }
    //Sensor B was unstable so use SensorA
    else if (StableA)
    {
      SensorValue = ValSensorA;
      SensorNumber = 1;
    }
    //SensorA was unstable so use SensorB
    else
    {
      SensorValue = ValSensorB;
      SensorNumber = 2;
    }
  }
  //SensorB was invalid so use SensorA
  else if (SensorAValid)
  {
    SensorValue = ValSensorA;
    SensorNumber = 1;
  }
  //SensorA was invalid so use SensorB
  else
  {
    SensorValue = ValSensorB;
    SensorNumber = 2;
  }

  Serial.println(SensorValue);
}
bool SensorValid(int Value, int Limits[2]) {  //Check if sensor reading is valid
  if ((Value > Limits[0]) && (Value < Limits[1]))
  {
    return true;
  }
  return false;
}
void CheckStable() { 
  //Get 20 readings from both sensors
  double SensorReadingsA[20];
  double SensorReadingsB[20];
  for (byte i=0; i<20; i++)
  {
    //Turn sensor on
    digitalWrite(SensorPWR, HIGH);
    delay(2);

    //Get sensor reading
    SensorReadingsA[i] = analogRead(SensorA) + 1000 + OffsetSensorA;
    SensorReadingsB[i] = analogRead(SensorB) + 2000;

    //Turn sensor off
    digitalWrite(SensorPWR, LOW);
  }

  //Calculate variance
  double VarianceSensorA = SampleVariance(SensorReadingsA);
  double VarianceSensorB = SampleVariance(SensorReadingsB);

  //Return sensor with the lowest variance
  
  

    
  //Check stability of sensors over 10 readings
  //Calculate the sum of 10 measurements
  unsigned int TotalA = 0;
  unsigned int TotalB = 0;
  for (byte i = 0; i < 10; i++)
  {
    //Turn sensor on
    digitalWrite(SensorPWR, HIGH);
    delay(2);

    //Get sensor reading
    ValSensorA = analogRead(SensorA) + 1000 + OffsetSensorA;
    ValSensorB = analogRead(SensorB) + 2000;

    //Turn sensor off
    digitalWrite(SensorPWR, LOW);

    //Calculate the sum
    TotalA = TotalA + ValSensorA;
    TotalB = TotalB + ValSensorB;
  }

  //Calculate theoretical total
  unsigned int TotalATheo = 10 * ValSensorA;
  unsigned int TotalBTheo = 10 * ValSensorB;

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
//General Referance
//Arduino variable limits https://thmuses.wordpress.com/2014/01/05/arduino-variable-types/
