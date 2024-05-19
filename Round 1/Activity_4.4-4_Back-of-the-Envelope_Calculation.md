To determine the constraints on the size of the robot, it is paramount to have an accurate model of the arena size. So, what are the dimensions of the arena, and how does this limit the robot's size?

## Assumptions
1. Other factors do not entirely control the size of the robot.
    - The maximum volume consumed by the prints.
    - The maximum torque of the robotic arm supplied by the servos (compared to the weight length of the arm itself).
    - Adjusting weight and COM such that the robot does not tip over from the weight of the arm and the additional weight of the doll (heaviest object required to be moved).

2. The robot's orientation is parallel to the walls, with the front-facing out of the starting position and towards the doll when climbing the ramp.

## Measurements & Calculations

The entire arena with all relevant dimensions is measured and displayed in Figure 1 below.

<p align="center">
  <img src="Images/MREN303Arena.png" alt="Arena" width="50%"/>
  <br>
  <strong>Figure 1:</strong> Scaled arena with relavant dimensions.
</p>

After analysis of the measurements, it was determined that the constraining distance for the width (W) of the robot is the width of the door (25 cm). The constraining distance for the length (L) of the robot is the distance between the highest point of the ramp and the edge of the pit where the doll lies closest to the ramp. This was calculated below to be 24 cm.

$42 cm - 18 cm = 24 cm$

## Take Aways
While these numbers work in theory, it is essential to note that we need to allow for tolerance in real life. Therefore, allowing for a 0.5 cm error on either side of the robot as the minimum tolerance we can realistically achieve, the final constraints for the maximum length and width of the robot are listed below.

$L = 23 cm$
<p>
$W = 24 cm$
<p>

While it may be possible to complete the task with these dimensions, the smaller the robot, the easier it will be to maneuver, and the less chance factors like the limit of 3D print volume will come into play.

 In addition, if any of the robot parts, such as the arm/claw, reach over the door or hang over the pit, these values would only apply to the robot's body as long as the robot COM is taken into consideration to avoid it tipping over.