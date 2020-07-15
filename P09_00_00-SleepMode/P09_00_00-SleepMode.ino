/*
 P09_00_00-SleepMode
 Project: P09_00_00 OwlBuddy
*/
//Sleep mode
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
volatile bool f_wdt=1;


void setup() {
  Serial.begin(115200);
  for (int i=0; i<5; i++)
  {
    Serial.println(" ");
  }
  Serial.println("Setup");
  delay(100);

  //Configure watchdog
  MCUSR &= ~(1<<WDRF); 
  WDTCSR |= (1<<WDCE) | (1<<WDE);
  WDTCSR = 1<<WDP0 | 1<<WDP3; 
  WDTCSR |= _BV(WDIE);
}

void loop() {
  SleepMode(17000);
  Serial.println("17000");

  
}
//Funcnction to be in sleep mode
void SleepMode(unsigned int TimeMs){
  
  //Determine cycles to sleep 
  byte CyclesToSleep  = TimeMs/8000;
  int RemainderTime = TimeMs - CyclesToSleep*8000;

  //Enter sleep mode for the number of cycles required
  bool KeepSleeping = true;
  volatile byte SleepCycles = 0;
  while (KeepSleeping)
  {
    //Watchdog just woke up
    if(f_wdt == 1)
    {
      //Check if it's time to wake up
      if (SleepCycles < CyclesToSleep)
      {
        SleepCycles++;
      }
      else
      {
        break;
      }
      
      //Clear the flag
      f_wdt = 0;
      
      //Re-enter sleep mode.
      enterSleep();
    }
  }
  //Delay for the remainder of the time
  delay(RemainderTime);
  
}
//Watchdog Interrupt Service. This is executed when watchdog timed out.
ISR(WDT_vect)
{
  if(!f_wdt)
  {
    f_wdt=true;
  }
  else
  {
    Serial.println("WDT Overrun!!!");
  }
}

//Enters the arduino into sleep mode.
void enterSleep(void)
{
  //Set sleep mode
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
  sleep_enable();
  
  //Enter sleep mode
  sleep_mode();
  
  //After waking up disable the sleep mode
  sleep_disable(); 
  
  // Re-enable the peripherals
  //power_all_enable();
}

/*
***** ROLL THE CREDITS *****
  >> Sleep Mode <<
  Sleep Mode        http://donalmorrissey.blogspot.com/2010/04/sleeping-arduino-part-5-wake-up-via.html
***** Thanks everyone! *****
*/
