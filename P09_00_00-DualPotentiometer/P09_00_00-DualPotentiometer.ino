//Define pins
#define SensorPWR     9  //Potentiometer power
#define SensorA      A0  //Blue wire
#define SensorB      A1  //White wire 

//Global variables (Potentiometer Functions)
int ValSensorA;
int ValSensorB;

void setup() {
  //Serial
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Setup");

  //General pin setup
  pinMode(SensorPWR, OUTPUT);


}

void loop() {
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
  Serial.println(ValSensorA-ValSensorB);

}
