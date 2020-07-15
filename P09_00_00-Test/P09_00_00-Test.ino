/*
   P09_00_00-Test
   Project: P09_00_00 OwlBuddy
   Notes: Test place

   Connections
   GND   - Potentiometer GND
   Pin02 - Potentiometer output
*/


#define WakePin 2

void setup() 
{
  //Serial
  Serial.begin(9600);
  Serial.println("Setup");

  pinMode(WakePin,INPUT_PULLUP);
}



void loop() 
{
  Serial.println(analogRead(WakePin));
}
