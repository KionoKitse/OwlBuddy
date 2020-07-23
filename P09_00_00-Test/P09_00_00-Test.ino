/*
   P09_00_00-Test
   Project: P09_00_00 OwlBuddy
   Notes: Test place

   Connections
   GND   - Potentiometer GND
   Pin02 - Potentiometer output
*/

//Sleep mode

//Global variables (General)
byte i;
bool Nap;
byte TimePos;
byte SensorNumber;
int  SensorValue;

//Global variables (Movement)
byte HeadTime; //Last know position of the head (time)
bool ActiveSensor; //AorB


//Potentiometer Calibration
int ValidSensorA[] = {1020, 1990};
int ValidSensorB[] = {2020, 2990};
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

  SensorNumber = 2;
  SensorValue = 58;
  Move2TimeKnown(0, -1);
}



void loop()
{
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
  for (byte i = 0; i < PathId; i++)
  {
    Serial.print(PositionPath[i]);
    Serial.print(",");
    Serial.println(SensorPath[i]);
  }
  

  //Move clockwise
  if (Direction < 0)
  {
    //Move approximate
    for (byte i = 1; i < PathId - 1; i++)
    {

    }
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


int Time2Pos(int Time){
  //Check for wrap around values
  if(Time > WrapAroundVal)
  {
    Time = Time - 60;
  }
  //Calculate position based on calibration
  double Position = Slope * Time + Intercept;
  return round(Position);
}

//General Referance
//Arduino variable limits https://thmuses.wordpress.com/2014/01/05/arduino-variable-types/
