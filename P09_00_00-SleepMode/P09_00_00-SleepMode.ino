/*
 P09_00_00-SleepMode
 Project: P09_00_00 OwlBuddy
*/

//Sleep mode
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
volatile bool f_wdt=1;

//Global variables (General)
byte i;
bool Nap;
byte SetTime;

//Global variables (Nap mode)
int CyclesToNap;
int DelayToNap;
long Time1;
long Time2;

void setup() 
{
  //Serial
  Serial.begin(9600);
  Serial.println("");
  
  //Configure watchdog
  MCUSR &= ~(1<<WDRF); 
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 1<<WDP0 | 1<<WDP3; 
  WDTCSR |= _BV(WDIE);
}



void loop() 
{
  Serial.println(""); 
  SetTime = 1;
  byte RemainingTime = SetTime;
  Time1 = millis();
  Time2 = millis();
  int NapTime;
  Serial.println("Start");
  delay(200);
  while (RemainingTime > 0)
  {
    //Adjust 1 min nap time to take into consideration time spent moving the head
    NapTime = 60*1000-(Time2-Time1);
    
    //Sleep 1 min
    TakeNap(NapTime);
    Time1 = millis();

    //Adjust remaining time
    RemainingTime --;
    
    //Move head 

    Time2 = millis();
  }
  Serial.println("Stop");
}

void TakeNap(unsigned int TimeMs){
  //Convert time in ms to number of 8sec blocks and delay
  byte Cycles = TimeMs/8000;
  int NapDelay = TimeMs - 8000*Cycles;
  //Serial.println(Cycles);
  //Serial.println(NapDelay);

  //Enter sleep mode for the number of cycles required
  bool KeepSleeping = true;
  volatile byte NapCycles = 0;
  while (KeepSleeping)
  {
    //Watchdog just woke up
    if(f_wdt == 1)
    {
      //Check if it's time to wake up
      if (NapCycles < Cycles)
      {
        NapCycles++;
      }
      else
      {
        break;
      }
      
      //Clear the flag
      f_wdt = 0;
      
      //Re-enter sleep mode.
      enterNap();
    }
  }
  //Delay for the remainder of the time
  delay(NapDelay); 
  Time1 = millis();
}




ISR(WDT_vect){                          //Watchdog Interrupt Service. This is executed when watchdog timed out.
  if(!f_wdt)
  {
    f_wdt=true;
  }
  else
  {
    Serial.println("WDT Overrun!!!");
  }
}
void enterNap(void){                    //Routine for entering sleep mode
  //Set sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
  sleep_enable();
  
  //Enter sleep mode
  sleep_mode();
  
  //After waking up disable the sleep mode
  sleep_disable(); 
}


/*
***** ROLL THE CREDITS *****
  >> Sleep Mode <<
  Sleep Mode        http://donalmorrissey.blogspot.com/2010/04/sleeping-arduino-part-5-wake-up-via.html
***** Thanks everyone! *****
*/
