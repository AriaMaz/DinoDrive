The specific goals for this round are to enable communication between the Raspberry Pi Pico W and the Logitech F310 Wired Gamepad using an Arduino and Python script. In addition, a rough cardboard prototype should be started to get a better mechanical understanding of a specific module.
The team’s goal for this round is to get a basis for the Dino Drives design and strategy to win the challenge. To get closer to this objective 2 tasks with subtasks are described below. 

# 1.    Choose which objectives within competition details to prioritize (Aria)

## Timing
| Module | Time |
| --- | --- |
| Autonomous Mode | 30 Seconds |
| Manuel Mode | 30 Seconds |

## Scoring
| Action | Points |
| --- | --- |
| Exit gate autonomously using push button | 8 |
| Exit gate autonomously using line following | 4 |
| Dinosaurs corralled | Max 6 (scaled to number in corral)|
| Doll saved (from pit to helipad) | Max 6 (scaled to the accelerometer)|

- If the points between teams are equal, the winner completes the tasks in the least amount of time.

### Slow & Steady Wins the Race
Based on the scoring system it should be noted that completing the task in a short amount of time is only valuable when the points between the teams are equal. Among all the actions that can earn you points saving the doll with 6 points "scaled to the accelerometer," assuming the accelerometer is somewhat precise, it will be very rare for two teams to finish with the same amount of points. Therefore, trying to optimize the time it takes to complete actions should be the last priority and the design of the robot should focus on precision, accuracy, and stability over speed.

Corralling dinosaurs and saving the doll will be given an equal weighting in priority and the highest priority will be given to exiting the gate using the pushbutton since it is awarded the most points and seems to be the easiest to achieve.

# 2.    Determine constraints on size of robot (Aria & Daniel)
Multiple things limit the size of the robot so they are split into subtasks shown below.

### 2.1 - Dimensions of the board (Aria)
The robot must be a specific width to fit through the gate or a specific length to be able to easily stand on the platform above the ramp. These constraints are explored in more detail within the [Back of the Envelope Calculation File](https://code.engineering.queensu.ca/mren303_w2024/section003_group10_dinodrive/-/blob/main/Round1/Activity_4.4-4_Back-of-the-Envelope_Calculation.md?ref_type=heads) within the [Round 1 Folder](https://code.engineering.queensu.ca/mren303_w2024/section003_group10_dinodrive/-/tree/main/Round1?ref_type=heads).

### 2.2 - Volume consumed by the print (Daniel)
The robot must not use 3D print filament that consumes a volume greater than 11 in<sup>3</sup> which is 180.258 cm<sup>3</sup> in the metric system. Because ample planning will be conducted it will be assumed that no more than 1.5 times more filament than intended will be used (this estimate is on the higher end to play it safe) resulting from errors and changes in design. This leaves us with 120.172 cm<sup>3</sup>. This is a small amount of volume to work with so 3D printing will be used for the intracit pieces of the board such as the TPU Gripper we are creating seen below and other parts can be created using the much larger MDF Panel (23.5" x 11.75" - 1/8").

<p align="center">
  <img src="Images/Gripper.png" alt="TPU Gripper" width="50%"/>
  <br>
  <strong>Figure 1:</strong> TPU Gripper
</p>

[1] “Adaptive gripper fingers,” YouTube, https://www.youtube.com/watch?v=jOc3e5O5OPM&ab_channel=FestoCanada (accessed Jan. 24, 2024). 

### 2.3 - Other (Daniel)
It is too early within the preliminary design to consider other constraints such as the maximum torque of the robotic arm supplied by the servo's since the goal is to get a basis for the design and to start doing torque calculations for the design for at least the arm of the robot should be completed.

Another constraint that may arise can be fine-tuning the COM of the robot such that when picking up the doll (the heaviest object required to be moved) the robot does not tip over from the weight of the arm and the additional weight of the doll, but again a design for the robot should be decided on before tackling this possible problem.