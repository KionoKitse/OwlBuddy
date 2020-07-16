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

int InvalidSensorA[] = {145, 939}; //SensorB reading when SensorA is invalid (195, 889)
int InvalidSensorB[] = {76, 869}; //SensorA reading when SensorA is invalid (126, 819)

int LookupTable[] = 
{543, 396, 256, 911, 788, 663, 509, 364, 221, 89, 808, 692};
//2   2    2    1    1    1    1    1    1    1   2    2      //Sensor numbers
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
int ValSensorA, ValSensorB;

void setup() 
{
  //Serial
  Serial.begin(9600);
  pinMode(SensorPWR,OUTPUT);
}



void loop() 
{

  GetHeadPos();
  //TestMotor(1);

  //GetHeadPos();
  //Serial.println(HeadPos);
  //TestMotor(1);
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
  delay(100);

  //0  (~,514)
  //> (1013,300)
  //90 (827, 53)
  //> (704,36)
  //180 (500,~)
  //> 223,1013
  //270 (47, 892)
  //> (18,750)
  
  /*

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
  */
  //Turn sensor off
  digitalWrite(SensorPWR, LOW);
}
