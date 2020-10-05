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
 * 2020-09-29 Testing dual pot results seem promising
 * 2020-09-29 For the dual pot design I'm noticing when pin A0 is floating it closely resembles pin A1 (not floating) but with more variance
 
### What's next
 * Write a filter to sort out which potentiometer to read from
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
 * Battery source Li-Po, Li-ion, or Ni-Mh. Ni-Mh has a similar capacity to Li-ion and weight isn't an issue. I already have these batteries and a simple USB charger for them. Size is a little big but it can fit more or less.  
 
 * Sum of squares function that seems to work well https://www.thoughtco.com/sum-of-squares-formula-shortcut-3126266
 * Direct control of mini stepper motor			https://www.youtube.com/watch?v=MaByP2w_vtA
 * Idea for slip ring power for LED strobe		https://gizmoplans.com/product/wind-turbine-slip-rings/
 * Interesting page on li-po charging			https://electronics-project-hub.com/arduino-lithium-ion-battery-charger/
 * CAD for SG90 Servo							https://www.thingiverse.com/thing:787942
 * Putting Arduino to sleep with watchdog		https://learn.adafruit.com/low-power-wifi-datalogging/power-down-sleep
 * Adjust VCC pin reading (didn't use)    		https://forum.arduino.cc/index.php?topic=435065.0 
 * Use VCC pin to read voltage		        	https://provideyourown.com/2012/secret-arduino-voltmeter-measure-battery-voltage/
 
### Next Blog Post
2020-09-29 <font color="63C0EC"><b>P09_00_00 Dual pot design</b></font>
Currently the big sticking point of this project is determining and controlling the head position. I have an SG90 servo that is directly coupled to the head and fixed to the body. I want the head to be able to rotate 360 degrees to allow the user to set a time between 1-60 min. The SG90 servo is only rated to 180 degrees of rotation so I've removed the limits. This allows me to drive the servo as essentially a gear head motor but removes the feedback loop. I've tried a lot of different ideas from hall effect sensors to pulse counting and stacked potentiometers. What I'm doing now is that stack potentiometer idea again. It was one of the first ideas I tried but I noticed that after a few days the potentiometers started bugging out. After disassembly I noticed that the wiper had worn down traces in the sections of the potentiometers that it was not designed to be in. The silver traces did not have any protection against the mechanical abrasion of the wiper. 
>>>IMAGE<<<
The idea was abandoned because I did not see any good way to prevent this from happening and still get continuous rotation. After a lot of trying other stuff it seemed that the dual potentiometer idea was the only idea that had shown some promise. Revisiting the idea I decided that maybe the best option was to protect the traces. For this, I've decided to use a bit of super glue to lay down a protective layer over the silver traces. I'm not sure how well this will stand up to the repeated abrasion but I'm keen to see if it will work. Here is an image of the dual potentiometer I've put together. The two potentiometers have their wipers in opposing positions so when one potentiometer is in the invalid range the other will be in it's valid range.
>>>IMAGE<<< 
<font color="63C0EC">Category:</font> Engineering
<font color="63C0EC">Tags:</font> Animatronics, Arduino, Engineering, Mechatronics, P09_00_00, Timer
<a href="https://kionokitse.wordpress.com/owlbuddy/">Project Page</a>

2020-09-29 <font color="63C0EC"><b>P09_00_00 Dual pot output</b></font>
Recently I had a chance to test the new dual potentiometer design. The results are looking promising but not quite what I had been expecting. One of the effects of coating the traces in super glue is that they are no longer conductive. This is a good thing because if it was conductive, the power would short between the contacts. I hadn't thought of that but note to self: super glue is non-conductive. The other effect that was unexpected is that it seems that a floating pin (no signal) will mirror a non-floating pin on the Arduino. I'm not sure under what cases this is true but in my case it was. On my setup I had A0 reading potentiometer A (PotA) and A1 reading potentiometer B (PotB). When PotA was in the invalid region and thus acting as a floating pin I noticed that it mirrored the results seen on PotB. The same happens if PotB is in the invalid region and PotA is in the valid region. Originally I though that maybe I had some sort of short that was connecting the output of PotA and PotB but that was not the case. If I move PotA into the valid region and transverse the valid region on PotB it's clear to see that there is no connection between them. In effect, this means that I will always be reading two values from the potentiometers that on the surface look valid. Here is a graph of two periods or 520 degrees of rotation.
>>>IMAGE<<<
It's not clear which sensor is in the valid region and which sensor is in the invalid region. One thing I noticed though was that it was possible to distinguish the two based on the amount of noise in the data. If a pin is floating then it's likely that all the data that is coming in in noise. Not quite what is happening here but with noise there tends to be quite a lot of variance compare to a set pin. When I look closer and the signal data it's easy to see which sensor is actually in the valid region.
>>>IMAGE<<<
>>>IMAGE<<<
<font color="63C0EC">Category:</font> Engineering
<font color="63C0EC">Tags:</font> Animatronics, Arduino, Engineering, Mechatronics, P09_00_00, Timer
<a href="https://kionokitse.wordpress.com/owlbuddy/">Project Page</a>
 
