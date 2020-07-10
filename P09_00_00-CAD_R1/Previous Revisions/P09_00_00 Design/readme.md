Name: P09_00_00 CAD Design
Software Version: FreeCAD 0.15
Notes: Design superseded by P09_00_01
Comments: This design did not work well. The gears were not supported well and caused pinching which was too much friction for the servo. Additionally the design was somewhat restrictive in only being able to rotate 360 degrees.

Description:
Assembly: The parts aligned to check for interference
BeaconLens: The red lens that covers the LED on top of the owl's head
LEDMount: The mounting part that mates the stepper motor with the LED
StepperMast: Part that holds the stepper motor vertically and mates to the BeaconBase to ensure the mast is centered
 *R2: Redesigned with a hallow center for passing wires though the BeaconBase and DriveGear
BeaconBase: Platform for beacon in the owl timer head
 *R2: Design modified for attaching directly to the drive gear. R1 design was flawed
DriveGear: Main drive gear for owl head motion connected to servo motor in owl body
 *R2: Reduced the gear module
ServoGear: Gear that is placed on servo head to drive the head action
 *R2: Reduced the gear module
MainFrame: The main frame component where the servo is attached to the owl body
 *R2: Redesigned with the servo motor at an angle for better access and better component sizing
DriveRetainer: Part for retaining the drive gear in the MainFrame
 *R2: Modified sizing on the DriveRetainer
BottomPlate: Support plate for drive servo and other electronics. Goes in the bottom half of owl timer
 *R2: Simplified the design for less space
 *R3: Resized hole for servo. Fit is much better
 