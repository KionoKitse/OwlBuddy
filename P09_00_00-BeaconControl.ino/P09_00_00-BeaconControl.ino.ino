double SensorVal;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  SensorVal = analogRead(A7); //0 to 1019
  Serial.print(SensorVal);
  Serial.print(",");
  SensorVal = SensorVal / 1019;
  SensorVal = 255 * SensorVal;
  Serial.println(SensorVal);
  analogWrite(9, SensorVal);
}
