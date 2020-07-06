//Define pins
#define inA1 6
#define inA2 7
#define inB1 8
#define inB2 9 
#define Sensor A0
#define SensorPWR A1  
#define ServoA 11
#define ServoB 12
#define LED 13

//Global variables
int Position = 0;
int SensorVal = 0;
int stepDelay = 40;



void setup() {
  Serial.begin(9600);
  
  //Set pin mode
  pinMode(inA1, OUTPUT);
  pinMode(inA2, OUTPUT);
  pinMode(inB1, OUTPUT);
  pinMode(inB2, OUTPUT);
  pinMode(ServoA, OUTPUT);
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

  LowPower();
}

void loop() {
  int spin = 3;
  int loops = 4*spin;
  for (int i=0; i<=loops; i++){ 
    step1(); 
    step2();
    step3();
    step4();
  }
  stopMotor();
  delay(2000);
  
  for (int i=0; i<=loops; i++){
    step3();
    step2();
    step1();
    step4(); 
  }
  
  stopMotor();
  delay(2000);
}
void ReadSensor()
{
  digitalWrite(SensorPWR, HIGH);
  delay(1);
  SensorVal = analogRead(Sensor);
  digitalWrite(SensorPWR, LOW);
  Serial.println(SensorVal);
}

void BeaconMode()
{
  
}

void LowPower()
{
  for(int i=0; i<10; i++){
    digitalWrite(LED,HIGH);
    delay(50);
    digitalWrite(LED,LOW);
    delay(50);
  }
}

void step1() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
  
}
void step2() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, HIGH);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step3() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, HIGH);   
  delay(stepDelay);
}
void step4() {
  digitalWrite(inA1, HIGH);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, HIGH);   
  digitalWrite(inB2, LOW);   
  delay(stepDelay);
}
void stopMotor() {
  digitalWrite(inA1, LOW);   
  digitalWrite(inA2, LOW);   
  digitalWrite(inB1, LOW);   
  digitalWrite(inB2, LOW);   
}
