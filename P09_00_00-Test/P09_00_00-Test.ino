/*
   P09_00_00-Test
   Project: P09_00_00 OwlBuddy
   Notes: Test place

   Connections
   GND   - Potentiometer GND
   Pin02 - Potentiometer output
*/

//Define pins
//#define InA  10 //Brown
//#define InB  11 //Purple
#define SensorA      A0  //Blue wire
#define SensorB      A1  //White wire //interrupt
#define SensorPWR   9  //Potentiometer power
#define LED         13
//Settings 
int MinSensorA = 12;
int MaxSensorA = 995;
int MinSensorB = 7;
int MaxSensorB = 992;

int InvalidSensorA[] = {2155, 2900}; //SensorB reading when SensorA is invalid
int InvalidSensorB[] = {1110, 1850}; //SensorA reading when SensorB is invalid

int ValidSensorA[] = {1020, 1990};
int ValidSensorB[] = {2020, 2990};


int TimeTable[60] = {2505,2482,2462,2433,2408,2375,2337,2308,2278,2247,2207,2189,1970,1953,1928,1898,1874,1852,1825,1797,1773,1745,1718,1691,1667,1638,1614,1591,1559,1517,1486,1447,1425,1397,1365,1338,1303,1277,1252,1223,1184,1156,1130,1110,1086,1059,1029,2882,2858,2831,2800,2774,2751,2722,2697,2673,2644,2619,2593,2562};

/*
0    *   543    0  -149   -29.8
5    *   396    0  -147   -29.4
10   *   256    0  -140   -28
15  911  103    0  -153   -30.6
20  788   *   -123   0    -24.6
25  663   *   -125   0    -25
30  509   *   -154   0    -30.8
35  364   *   -145   0    -29
40  221   *   -143   0    -28.6
45  89   961  -132   0    -26.4
50   *   808    0  -153   -30.6
55   *   692    0  -116   -23.2

SensorA (40 - 899): Min
SensorA (951 - 155): Max  
SensorB (850 - 40): Min
SensorB  (110 - 975): Max
*/  
//Global variables
int HeadPos;
long ValSensorA;
long ValSensorB;
int ValSensor;
byte i;
bool StableA;
bool StableB;

void setup() 
{
  //Serial
  Serial.begin(9600);
  pinMode(SensorPWR,OUTPUT);
}



void loop() 
{
  CalibrateTimer();
}

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

//Function to get unkonwn position 
int GetUnkownPos()
{
  int pos;
  //Turn sensor on
  digitalWrite(SensorPWR, HIGH); 
  delay(2);
    
  //Get sensor reading
  ValSensorA = analogRead(SensorA)+1000;
  ValSensorB = analogRead(SensorB)+2000;

  //Turn sensor off
  digitalWrite(SensorPWR, LOW);

  Serial.print(ValSensorA);
  Serial.print(",");
  Serial.print(ValSensorB);
  Serial.print(": ");

  //Check for valid readings
  bool SensorAValid = SensorValid(ValSensorA, ValidSensorA);
  bool SensorBValid = SensorValid(ValSensorB, ValidSensorB);

  //Check reading stability
  if(SensorAValid && SensorBValid)
  {
    StableA = true;
    StableB = true;
    CheckStable();
    CheckStable();
    
    if (StableA && StableB)
    {
      Serial.print("Stable ");
      pos = ValSensorA;
    }
    else if (StableA)
    {
      pos = ValSensorA;
    }
    else 
    {
      pos = ValSensorB;
    }
  }
  else if (SensorAValid)
  {
    pos = ValSensorA;
  }
  else
  {
    pos = ValSensorB;
  }
  Serial.println(pos);
  return pos;



  //delay(100);
  

}

void CheckStable()
{
  
  
  //Calculate the average for 10 samples
  unsigned int TotalA = 0;
  unsigned int TotalB = 0;
  for (i=0; i<10; i++)
  {
    //Turn sensor on
    digitalWrite(SensorPWR, HIGH); 
    delay(2);
    
    //Get sensor reading
    ValSensorA = analogRead(SensorA)+1000;
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

bool SensorValid(int Value, int Limits[2])
{
  if ((Value > Limits[0]) && (Value < Limits[1]))
  {
    return true;
  }
  return false;
}


//Function to get the set time
byte GetSetTime(){
  //Serial.println("Get set time");
  bool Both = 0;

  //Turn sensor on
  digitalWrite(SensorPWR, HIGH); 
  delay(2);
  
  //Read the sensor
  ValSensorA = analogRead(SensorA)+1000;
  ValSensorB = analogRead(SensorB)+2000;

  

  //Turn sensor off
  digitalWrite(SensorPWR, LOW); 

  //Determine if SensorA is invalid
  if((ValSensorB > InvalidSensorA[0]) && (ValSensorB < InvalidSensorA[1]))
  {
    ValSensor = ValSensorB;
  }
  //Determine if SensorB is invalid
  else if ((ValSensorA > InvalidSensorB[0]) && (ValSensorA < InvalidSensorB[1]))
  {
    ValSensor = ValSensorA;
  }
  //Both sensors are valid select the one that is farthest from it's limits
  else
  {
    Both = 1;
    //Distance to limits
    int DeltaA = DeltaLimits(ValSensorA, InvalidSensorB);
    int DeltaB = DeltaLimits(ValSensorB, InvalidSensorA);
   
    //Select sensor that is farthest from it's limits
    if (DeltaA > DeltaB)
    {
      ValSensor = ValSensorA;
    }
    else
    {
      ValSensor = ValSensorB;
    }
  }
  Serial.print(ValSensorA);
  Serial.print(",");
  Serial.print(ValSensorB);
  Serial.print(": ");
  Serial.print(ValSensor);
  Serial.print(" ");
  Serial.println(Both);
}


//Function to measure min distace to limits
int DeltaLimits (int Value, int Limits[2])
{
  int DeltaL = abs(Value-Limits[0]);
  int DeltaR = abs(Value-Limits[1]);
  if (DeltaL > DeltaR)
  {
    return DeltaR;
  }
  else
  {
    return DeltaL;
  }
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

  Serial.print(ValSensorA);
  Serial.print(",");
  Serial.println(ValSensorB);

  bool ActiveSensor;

  //Determine if SensorA is invalid
  if((ValSensorB > InvalidSensorA[0]) && (ValSensorB < InvalidSensorA[1]))
  {
    Serial.println("SensorA invalid");
    ValSensor = ValSensorB;
    ActiveSensor = 1;
  }
  //Determine if SensorB is invalid
  else if ((ValSensorA > InvalidSensorB[0]) && (ValSensorA < InvalidSensorB[1]))
  {
    Serial.println("SensorB invalid");
    ValSensor = ValSensorA;
    ActiveSensor = 0;
  }
  //Both sensors are valid select the one that is farthest from it's limits
  else
  {
    Serial.println("Both sensors valid");
	
  	//Distance to limits
  	int DeltaA = DeltaLimits(ValSensorA, InvalidSensorB);
    int DeltaB = DeltaLimits(ValSensorB, InvalidSensorA);
   
  	//Select sensor that is farthest from it's limits
  	if (DeltaA > DeltaB)
    {
      ValSensor = ValSensorA;
      ActiveSensor = 0;
    }
    else
    {
      ValSensor = ValSensorB;
      ActiveSensor = 1;
    }
}
  



  //Turn sensor off
  digitalWrite(SensorPWR, LOW);
}
