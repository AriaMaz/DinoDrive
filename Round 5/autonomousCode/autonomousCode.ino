// #include <WiFi.h>
// #include <WiFiUdp.h>
// #include <Wire.h>
#include <SparkFun_TB6612.h>

// DC Motors
#define AIN1 13
#define AIN2 14
#define PWMA 15

#define BIN1 18
#define BIN2 17
#define PWMB 16

#define STBY 19

//const int offsetA = 1;
//const int offsetB = 1;

// Ultrasonic Sensor
const int trigPin = 16;
const int echoPin = 13;

// Defines variables
long duration;
int distance;

void setup(){

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, 0);

    // Initialize motor driver pins as outputs
    pinMode(STBY, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);
    pinMode(PWMA, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
    pinMode(PWMB, OUTPUT);

    // Initialize trig and echo pins
    pinMode(trigPin, OUTPUT); 
    pinMode(echoPin, INPUT); 

    Serial.begin(9600);
}

void loop(){
    //currentTime = millis();

//----------------------------------------------------------Sensors--------------------------------------------------------
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    Serial.print(duration);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    // Prints the distance on the Serial Monitor
    Serial.print("Distance (cm): ");
    Serial.println(distance);
    delay(100);
//----------------------------------------------------------Sensors--------------------------------------------------------

//----------------------------------------------------------Actuators--------------------------------------------------------
    int speedLeft = 0;
    int speedRight = 0;

    // Turning
    if (valueRx > 0)
    {
        // Right
        // speedLeft += map(valueRx, 0, 255, 0, 255);
        speedLeft += valueRx;
        speedRight -= map(valueRx, 0, 255, 0, 255);
    }
    else if (valueRx < 0)
    {
        // Left
        int mappedValue = map(-valueRx, 0, 255, 0, 255);
        speedLeft -= mappedValue;
        speedRight += mappedValue;
    }

    // Driving
    if (valueLy > 0)
    {
        // Forward
        int speedFwd = map(valueLy, 0, 255, 0, 255);
        speedLeft += speedFwd;
        speedRight += speedFwd;
    }
    else if (valueLy < 0)
    {
        // Backward
        int speedBck = map(-valueLy, 0, 255, 0, 255);
        speedLeft -= speedBck;
        speedRight -= speedBck;
    }

    // Ensure speeds are within motor limits
    speedLeft = constrain(speedLeft, -255, 255);
    speedRight = constrain(speedRight, -255, 255);

    // Drive motors
    motor1.drive(speedLeft);
    motor2.drive(speedRight);
//----------------------------------------------------------Actuators--------------------------------------------------------
}