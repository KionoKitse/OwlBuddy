### Description  
P09_00_00 OwlBuddy
This project is a simple modify but not repurpose hack. I'm taking a mechanical owl timer that doesn't work very well and converting it into a digital animatronics timer.  
Features
 * Adjustable timing between 1-60 min
 * Servo motion for head movement
 * Detection of timing adjustment
 * Audio feedback
 * LED strobe beacon
 * Battery powered
 * Charge level monitoring
 * Integrated USB charging
 * Automatic sleep and wakeup

### Notes to user
 * Project documented at https://kionokitse.wordpress.com/owlbuddy
 * In development
 
### Hardware
 * Arduino Pro Mini clone ATmega328 5V
 * Micro servo Tower Pro SG90
 * Micro stepper motor
 * High output LED
 
### Progress log 
 * 2020-06-15 Initial project idea 
 * 2020-06-16 Deciding on features and components
 * 2020-06-16 Ordering components
 * 2020-06-16 Initial design sketches
 * 2020-06-17 Ordering components
 * 2020-06-17 Testing LEDs
 * 2020-06-17 Solder stepper motor
 * 2020-06-17 CAD design
 * 2020-06-17 Gear train 
 * 2020-07-04 Redesign CAD P09_00_01
 * 2020-07-04 Start writing software
 * 2020-07-13 Finished 3D printing main components
 * 2020-07-13 Got the VCC readings from the pro mini
 * 2020-07-13 Modify servo for continuous rotation 3.3kOhm resistors
 * 2020-07-13 Testing drive servo with low battery (didn't work)
 * 2020-07-13 Testing direct drive with Arduino pins for the servo motor (didn't work)
 * 2020-07-13 Possible to drive motor using battery leads
 * 2020-07-13 Remove H bridge from SG90 (117L 929 datasheet not found)
 * 2020-07-13 Mapping H bridge pins from SG90
 * 2020-07-13 Modify owl base to accept mini USB adapter
 * 2020-07-14 Probing H bridge found working pinout still a couple unknown pins
 * 2020-09-22 Testing hall effect sensor based encoder 
 * 2020-09-22 Hall encoder results look noisy filtering is very difficult maybe need another approach
 * 2020-09-22 Search mode is the best filter mode so far average filter offsets results slightly
 * 2020-09-22 Inconsistent resistance results in some sections moving faster requiring different filter settings
 * 2020-09-22 Should consider adjustable filter settings
 * 2020-09-26 Testing the idea of adding magnets to the internal gears of the servo
 * 2020-09-27 Testing using metal rods instead of magnets in internal gears
 * 2020-09-27 Tests worked but the process damages the gears not a (feasible option)
 * 2020-09-27 Revisiting the two potentiometer design with trace reinforcement
 
### What's next
 * Test wake up from sleep using potentiometer
 * Design layout
 * Test pro mini pins
 * Need to reduce the battery until I can find the min voltage that will drive this project
 
### Function
 * Hardware is asleep 
 * User sets owl time
 * Moving the head will trigger the wakeup command (maybe I need a switch here)
 * Arduino checks the battery voltage if the voltage is low the LED will blink rapidly
 * Timer waits for a few seconds before reading the potentiometer 
 * Timer reads time value
 * Beacon is activated for a few seconds
 * Drive motor goes back to zero then negative whatever value was put include
 * Drive motor goes back to set value
 * Beacon is activated again once the timer starts
 * Arduino goes to sleep
 * Arduino wakes up and moves the drive motor every minute towards zero
 * Arduino also remembers the last set value
 * If the user adjusts the time while the timer is activated the timer will adjust the time accordingly and blink the LED to acknolegde
 * Once the timer goes to zero owl moves 180 then -180 twice before returning to zero
 * During this time the beacon is activated
 * Afterwards the Arduino goes to sleep
 
### Notebook
 * Battery source Li-Po, Li-ion, or Ni-Mh. Ni-Mh has a similar capacity to Li-ion and weight isn't an issue. I already have these batteries and a simple USB charger for them. Size is a little big but it can fit ore or less.  
  
 * Direct control of mini stepper motor			https://www.youtube.com/watch?v=MaByP2w_vtA
 * Idea for slip ring power for LED strobe		https://gizmoplans.com/product/wind-turbine-slip-rings/
 * Interesting page on li-po charging			https://electronics-project-hub.com/arduino-lithium-ion-battery-charger/
 * CAD for SG90 Servo							https://www.thingiverse.com/thing:787942
 * Putting Arduino to sleep with watchdog		https://learn.adafruit.com/low-power-wifi-datalogging/power-down-sleep
 * Adjust VCC pin reading (didn't use)    		https://forum.arduino.cc/index.php?topic=435065.0 
 * Use VCC pin to read voltage		        	https://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
 
### Next Blog Post
2020-09-24 <font color="63C0EC"><b>P09_00_00 Starting a project from the middle</b></font>
Wow where to begin? I'm somewhat conflicted with this project. It's something that I started back in June to be a present for a birthday in July. I originally thought that this project would be super simple and I could get it done in a few weeks then write about it in the blog. As time ticked by, things got more and more desperate as the deadline loomed and I started realizing that the project would not be done in time. Things like that happen and it's best to learn from past experiences and think of those things when evaluating a project time line. For this case it was not so much of a big deal since I can easily just call it a Christmas present and give myself some more time. After all these projects are intended to be enjoyable things that challenge me and bring joy. The part that is conflicting is just where to start with documenting this project? I'm 3 months into this project and knee deep in several hardware revisions. I feel like I've learned so much from this project and gained some valuable insight that I would love to share. At the same time I'd like to get this done well before Christmas since the post service can be quite slow and who know what issues are around the corner. This project has proven to be easily underestimated and fraught with unseen complications. I think what I will do is blog as if I have been doing so and try to fill in the gaps as I go. That will give me the most flexibility and allow for unforeseen delays at the risk on not remembering all the good stories I'd like to tell.  
<font color="63C0EC">Category:</font> Engineering
<font color="63C0EC">Tags:</font> Animatronics, Arduino, Engineering, Mechatronics, P09_00_00, Timer
<a href="https://kionokitse.wordpress.com/HydroGarden/">Project Page</a>

<a href="https://kionokitse.wordpress.com/owlbuddy"><font size="6" color="63C0EC"><b>OwlBuddy</b></font></a>
<font color="63C0EC">Designation:</font> P09_00_00
<font color="63C0EC">Category:</font> Engineering
<font color="63C0EC">Status:</font> Exploratory
<font color="63C0EC">Last update:</font> 2020-09-23
<font color="63C0EC">Description:</font> Hacking an owl timer into an awesome owl timer 

 
