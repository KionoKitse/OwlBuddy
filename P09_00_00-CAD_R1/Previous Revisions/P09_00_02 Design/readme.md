Name: P09_00_02 CAD Design
Software Version: FreeCAD 0.15 and FreeCAD 0.18* 
Notes: Design superseded by P09_00_03
Comments: Worm gear design worked but seemed to be somewhat unreliable. Additionally the gear ratio wasn't high enough, resulting in a beacon that spun too fast. Gear noise was almost as loud as SG90 under normal conditions.

Description:
This design is the second third iteration of P90_00_00. It calls for one SG90 servo to control the owl head movement and another SG90 motor to drive the worm gear for the beacon motion. The SG90 servo is modified for continuous rotation and is directly connected to the owl head. The continuous rotation modification disallows for the usage of the SG90 potentiometer so a DIY one is designed to fit with the owl body and head section. The potentiometer makes use of 26GA nichrome wire which will also be needed. For the worm gear drive train a motor is removed from a SG90 and mated to the worm gear. The worm gear is supported by a 2mm axle shaft and drives a worm wheel that is mated to the shell of a bic pen. The LED mount is installed on the bic pen shaft and wires to the LED are passed through the hollow shaft. Power to the LED is supplied by a DIY slip ring making use of nichrome wires as the the slip ring brushes.

Assembly: The parts aligned to check for interference
BeaconLens: The red lens that covers the LED on top of the owl's head (unmodified since P09_00_00)
LEDMount: The mounting part that mates the pen shaft with the LED
GearboxTop*: Top part of the worm gear drive train enclosure. Also contains the mounting points for the slip ring brushes
WormWheel*: Worm wheel that mates with the worm gear
WormGear*: Worm gear that mates to the SG90 motor and drives the worm wheel
GearboxBottom*: Bottom part of the worm gear drive train enclosure
BeaconBase: Top part of the potentiometer and base for stepper mast. Placed inside of owl head (unmodified since P09_00_01R1)
ServoHead: Attachment part that mates the servo to the top part of the potentiometer (unmodified since P09_00_01R1)
MainFrame: The main frame component where the servo is attached to the owl body. Also comprises of the bottom half of the potentiometer (unmodified since P09_00_01R1)
BottomPlate: Support plate for drive servo and other electronics. Goes in the bottom half of owl timer (unmodified since P09_00_00R3)
SG90ServoMotor: Motor removed from SG90 (modeled for fit)
*Modeled with FreeCAD 0.18