# Overarching Design Problem 

 1. Press the button, if the button press is not feasible then return to line following
    - leave the initial starting position using ultrasonic sensors by comparing the distance of all three sides. 
       - add PID to have precise movement during ultrasonic sensing
    - use the ultrasoninc sensors to align the robot in a way to press the button
    - set the grabbing/scooping portion of robot aligned at a predetermined height 
    - have back up line following code in case of any ultrasoninc sensor fails.
    
 2. Be able to enter through the door
    - realign the robot using the ultra sonic sensors and hard coded time to be able to enter through the door. 
    - since the ultrasonic sensors will be on the right, left, and front side have a max distance for the front side so the robot does not crash into the back wall

 3. Grab all the dinosaurs and place them into the black bucket
    - drive the robot using the Logitech Controller
    - knock off dinosaurs from the rocks or carefully grab them
    - grab each dinosaur separately and put them one by one into the bucket or push the dinosaurs together and scoop them into the bucket

 4. Ride up the ramp
    - ensure the robot does not bottom out when moving up the ramp
    - ensure the robot does not fall backwards comming up the ramp
    - ensure the robot does not get caught on the edge of the ramp

 5. Grab Ken 
    - grab or scoop Ken lighlty
    - raise him out of the ditch and continue down the ramp 
    - add fine steering control to make sure that Ken does not hit anything on any part of the journey

 6. Slowly take Ken to the helipad 
    - move fast enough to save time but slow enough to ensure the ride is smooth for Ken

# Constraints

1. 3D Printing Material
   - not exceeding the allowed amount

2. Time 
   - time is not being graded but a robot should not take too long to complete a task because that would be a waste of resources

3. Motors
   - only 3 servo motors and 2 DC motors are given. 

4. No Navigation Sensors Given (ex. LiDAR, Camera)
   - only ultrasonic sensors can be used for guidance 

5. Can Only Use Kit Materials
   - no other materials can be added 

6. Batteries Charge in 10 Hours so for iteration purposes the the back up batteries should always be charging

7. Batteries Output 4.8 volts when the DC motors require around 6V