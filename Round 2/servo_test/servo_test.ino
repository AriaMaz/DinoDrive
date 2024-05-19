#include <Servo.h>

Servo servo1;
Servo servo2;
//Servo servo3;

void setup() {
  servo1.attach(0, 600, 2500); 
  servo2.attach(2, 600, 2500); 
  //servo3.attach(5, 600, 2500); 
}

void loop() {
  servo1.write(0);
  delay(1000);
  servo1.write(180);

  servo2.write(90); //Neutral position
  delay(1000);
  servo2.write(0);

  //servo3.write(90); //Neutral position
  //delay(1000);
  //servo3.write(0);
}