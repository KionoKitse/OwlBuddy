/*
Connections
 * GND   - Potentiometer GND
 * Pin02 - Potentiometer output
*/


//Sleep mode
#include <avr/sleep.h>
#define WakePin 2  //Pin to indicate when the timer has been activated

//Define pins
#define LED         13  //Beacon LED


//Global variables



void setup() {
  Serial.begin(9600);
  pinMode(LED,OUTPUT);
  pinMode(WakePin,INPUT_PULLUP);

  //Blink at setup
  Serial.println("Setup");
  for(int i=0; i<5; i++){
    digitalWrite(LED,HIGH);
    delay(100);
    digitalWrite(LED,LOW);
    delay(100);
  }

  
}

void loop() {
  Serial.println("Loop");
  digitalWrite(LED,HIGH);
  delay(2000);
  digitalWrite(LED,LOW);
  ActivateSleep();

}

void ActivateSleep(){
    Serial.println("ActivateSleep");
    
    //Enable sleep mode
    sleep_enable();

    //Sleep mode settings
    attachInterrupt(0, WakeUp, LOW); //0 = Pin02
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);

    //Go to sleep
    sleep_cpu();

    //Code to run after interrupt routine 
    Serial.println("Awake: Finish ActivateSleep -> Loop"); 
  }

void WakeUp(){
  Serial.println("Interrrupt Fired");
   sleep_disable();//Disable sleep mode
  detachInterrupt(0); //0 = Pin02
}



/*
***** ROLL THE CREDITS *****
 * Wake Arduino with interrupts     https://forum.arduino.cc/index.php?topic=435065.0 
 * Use VCC pin to read voltage            https://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/

***** Thanks everyone! *****
*/
