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

//Settings 
int MinSensorA = 12;
int MaxSensorA = 995;
int MinSensorB = 7;
int MaxSensorB = 992;

int InvalidSensorA[] = {2155, 2899}; //SensorB reading when SensorA is invalid
int InvalidSensorB[] = {1110, 1850}; //SensorA reading when SensorB is invalid

int LookupTable[] = 
{2543, 2396, 2256, 1911, 1788, 1663, 1509, 1364, 1221, 1089, 2808, 2692};
//2    2     2     1     1     1     1     1     1     1     2     2      //Sensor numbers
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

void setup() 
{
  //Serial
  Serial.begin(9600);
  pinMode(SensorPWR,OUTPUT);
}



void loop() 
{
  GetUnkownPos();
  //GetHeadPos();
  //TestMotor(1);

  //GetHeadPos();
  //Serial.println(HeadPos);
  //TestMotor(1);
}


//Function to get unkonwn position 
void GetUnkownPos()
{
  //int InvalidSensorA[] = {2155, 2899}; //SensorB reading when SensorA is invalid
  //int InvalidSensorB[] = {1110, 1850}; //SensorA reading when SensorB is invalid

  //Calculate the variance of 100 samples from each sensor
  unsigned long SumA1 = 0;
  unsigned long SumA2 = 0;
  unsigned long SumB1 = 0;
  unsigned long SumB2 = 0;
  long VarA;
  long VarB;
  digitalWrite(SensorPWR, HIGH); 
  for (i=0; i<100; i++)
  {
    //Turn sensor on
    digitalWrite(SensorPWR, HIGH); 
    delay(2);
    
    //Get sensor reading
    ValSensorA = analogRead(SensorA)+1000;
    ValSensorB = analogRead(SensorB)+2000;

    //Turn sensor off
    digitalWrite(SensorPWR, LOW);

    //Calculate squared value Sum(X^2)
    SumA1 = SumA1 + (ValSensorA*ValSensorA);
    Serial.println(SumA1);
    SumB1 = SumB1 + (ValSensorB*ValSensorB);

    //Calculate sum value
    SumA2 = SumA2 + ValSensorA;
    SumB2 = SumB2 + ValSensorB; 

    //Print
    Serial.print(ValSensorA);
    Serial.print(",");
    Serial.println(ValSensorB);
  }

  //Square sum2
  SumA2 = SumA2*SumA2;
  SumB2 = SumB2*SumB2;

  //Finish math
  SumA2 = SumA2/100;
  SumA2 = SumA2/100;
  VarA = SumA1 - SumA2;
  VarB = SumB1 - SumB2;

  Serial.println("");
  Serial.print(SumA1);
  Serial.print(",");
  Serial.println(SumA2);
  Serial.println("");
  
  Serial.println("");
  Serial.print(VarA);
  Serial.print(",");
  Serial.println(VarB);
  Serial.println("");

  delay(1000);
  

}

bool SensorValid(int Value, int Limits[2])
{
  if ((Value < Limits[0]) && (Value > Limits[0]))
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
