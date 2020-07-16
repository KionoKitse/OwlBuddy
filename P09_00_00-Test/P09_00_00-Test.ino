/*
   P09_00_00-Test
   Project: P09_00_00 OwlBuddy
   Notes: Test place

   Connections
   GND   - Potentiometer GND
   Pin02 - Potentiometer output
*/

//Define pins
#define InA  10 //Brown
#define InB  11 //Purple
#define SensorA      A0  //Blue wire
#define SensorB      A1  //White wire
#define SensorPWR   9  //Potentiometer power

//Settings 
int MinSensorA = 12;
int MaxSensorA = 995;
int MinSensorB = 7;
int MaxSensorB = 992;

int InvalidSensorA[] = {145, 939}; //{195, 889};
int InvalidSensorB[] = {76, 869}; //{126, 819};

//Global variables
byte CaseMode;
long BatteryVoltage;
bool LowBattery;
int HeadPos;
byte i;
bool ValidSensorA;
bool ValidSensorB;

void setup() 
{
  //Serial
  Serial.begin(9600);
  pinMode(SensorPWR,OUTPUT);

}



void loop() 
{

  GetHeadPos();
  TestMotor(1);

  //GetHeadPos();
  //Serial.println(HeadPos);
  //TestMotor(1);
}
void TestMotor(bool Forward){
  int Time = 5;
  if(Forward)
  {
    digitalWrite(InA,LOW);
    digitalWrite(InB,HIGH);
    delay (Time);
    digitalWrite(InB,LOW);
    delay(500);
  }
  else
  {
    digitalWrite(InB,LOW);
    digitalWrite(InA,HIGH);
    delay (Time);
    digitalWrite(InA,LOW);
    delay(500);
  }
  
}

//Function to read head position
void GetHeadPos()
{
  //Turn sensor on
  digitalWrite(SensorPWR, HIGH); 
  delay(2);

  //Read value
  int SensorAVal = analogRead(SensorA);
  int SensorBVal = analogRead(SensorB);
  
  //Turn sensor off
  digitalWrite(SensorPWR, LOW);

  Serial.print(SensorAVal);
  Serial.print(",");
  Serial.println(SensorBVal);
  
}
