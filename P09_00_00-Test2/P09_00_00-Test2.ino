/*
   P09_00_00-Test2
   Project: P09_00_00 OwlBuddy
   Notes: Testing reading two sensors

   Connections
   GND   - Potentiometer GND
   VCC   - Potentiometer vcc
   PinA0 - Potentiometer 1 output
   PinA1 - Potentiometer 2 output
*/

//Sleep mode (interrupt)

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

//Global variables (Potentiometer Functions)
int   ValSensor;
int   ValSensorA;
int   ValSensorB;
bool  StableA;
bool  StableB;
double   Position;
int   Selected;
int SensorReadingsA[20];
int SensorReadingsB[20];

//Potentiometer Calibration
int LimitA[] = {7,900};
int LimitB[] = {28,900};  
double EqA[] = {-4.806935248,944.398238};
double EqB[] = {-4.879848796,1843.686565};


//Temporary variables
double temp;

void setup()
{
  //Serial
  Serial.begin(9600);
  Serial.println("Setup");

  //General pin setup
  pinMode(SensorPWR, OUTPUT);
  pinMode(SensorA, INPUT);
  pinMode(SensorB, INPUT);
}



void loop()
{

  GetPosition();
}

void GetPosition(){
  //Get sensor reading
  //ValSensorA = analogRead(SensorA)+1000;
  //ValSensorB = analogRead(SensorB)+2000;
  ValSensorA = analogRead(SensorA);
  ValSensorB = analogRead(SensorB);

  //Condition both sensors might be valid
  /*
  if (
       (
        (ValSensorA>LimitA[0]) && (ValSensorA<LimitA[1])
       ) 
       && 
       (
        (ValSensorB>LimitB[0]) && (ValSensorB<LimitB[1])
       )
     ){

int LimitA[] = {7,900};
int LimitB[] = {28,900};  
     */

    Position = 0;
    if((ValSensorA<900) && (ValSensorB<900) && (ValSensorA>7) && (ValSensorB>28)){
      for (byte i=0; i<20; i++){
        SensorReadingsA[i] = analogRead(SensorA);
        SensorReadingsB[i] = analogRead(SensorB);
      }
      //Calculate variance
    //double VarianceSensorA = SampleVariance(SensorReadingsA);
    //double VarianceSensorB = SampleVariance(SensorReadingsB);
    }else{
      if(ValSensorA > 900){
        Selected = ValSensorB;
        temp = ValSensorB-EqB[1];
        Position = (ValSensorB-EqB[1])/EqB[0];
      }
      else{
        Selected = ValSensorA;
        Position = (ValSensorA-EqA[1])/EqA[0];
      }
      //Position = (ValSensorA > 900) ? (EqB[0]*ValSensorB+EqB[1]) : (EqA[0]*ValSensorA+EqA[1]);
    }
    

  Serial.print(ValSensorA);
  Serial.print(",");
  Serial.print(ValSensorB);
  Serial.print(",");
  Serial.print(Selected);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.println(Position);
}

//General Referance
//Arduino variable limits https://thmuses.wordpress.com/2014/01/05/arduino-variable-types/
