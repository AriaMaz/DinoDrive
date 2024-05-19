// MREN 303 Pico W Wifi Gamepad Read
// Written For MREN 303

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <Wire.h>
#include <SparkFun_TB6612.h>

Servo servo1;
Servo servo2;
Servo servo3;

#ifndef STASSID
#define STASSID "MREN303_wifi"
#define STAPSK "MREN@303p1"
#endif

// Define Statements

//Servos
#define servo1Pin 0
#define servo2Pin 1
#define servo3Pin 2

//DC Motors
#define AIN1 13
#define AIN2 14
#define PWMA 15

#define BIN1 18
#define BIN2 17
#define PWMB 16

#define STBY 19

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

unsigned int localPort = 8888;  // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged\r\n";        // a string to send back
// char Arrays to match commands from gamepad
char stringA[17] = "A1";
char stringA2[17] = "A0";
char stringB[17] = "B1";
char stringB2[17] = "B0";
char stringY[17] = "Y1";
char stringY2[17] = "Y0";
char stringX[17] = "X1";
char stringX2[17] = "X0";
char stringLB[17] = "LB1";
char stringLB2[18] = "LB0";
char stringRB[17] = "RB1";
char stringRB2[18] = "RB0";
char stringLS[17] = "LS1";
char stringLS2[17] = "LS0";
char stringRS[17] = "RS1";
char stringRS2[17] = "RS0";
char stringBack[17] = "Back1";
char stringBack2[17] = "Back0";
char stringStart[17] = "Strt1";
char stringStart2[17] = "Strt0";
char stringUp[17] = "Udp1";
char stringUp2[17] = "Udp0";
char stringDown[17] = "Ddp1";
char stringDown2[18] = "Ddp0";
char stringLeft[17] = "Ldp1";
char stringLeft2[18] = "Ldp0";
char stringRight[17] = "Rdp1";
char stringRight2[19] = "Rdp0";
char stringLX[17] = "LSX ";
char stringLY[17] = "LSY ";
char stringRX[17] = "RSX ";
char stringRY[17] = "RSY ";
char stringLT[17] = "LT ";
char stringRT[17] = "RT ";

int valueLx = 0;
int valueLy = 0;
int valueRx = 0;
int valueRy = 0;
int valueLt = 0;
int valueRt = 0;

// Servo Variables
int servo1Value = 0;
int servo2Value = 0;
int servo3Value = 0;

bool ledOn = false;
bool rbPressed = false;
bool lbPressed = false;
bool rtPressed = false;
bool ltPressed = false;
bool rsPressed = false;
bool lsPressed = false;
bool isServoAt180 = false;

WiFiUDP Udp;

void setup() {  //This handles network function and runs on core 1
  Serial.begin(115200);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.println();
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}
void setup1() {  //This handles all inputs and outputs and runs on core 2

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
  servo1.attach(servo1Pin, 600, 2500);
  servo2.attach(servo2Pin, 600, 2500);
  servo3.attach(servo3Pin, 600, 2500);
}

void loop() {  //This loop executes on Core 1 of the Pico, handles networking and recieves commands
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d)\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort(), Udp.destinationIP().toString().c_str(), Udp.localPort());

    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;

    char comparisonString[17] = "";
    char valueString[5] = "";

    for (int i = 0; i < 16; i++) {
      comparisonString[i] = packetBuffer[i];
    }
    comparisonString[16] = 0;

    Serial.println("Comp String:");
    Serial.println(comparisonString);

    //Servo 1 Logic
    if (strcmp(comparisonString, stringRB) == 0) {
      rbPressed = true;
      lbPressed = false; // Ensure LB is not pressed
    } else if (strcmp(comparisonString, stringLB) == 0) {
      lbPressed = true;
      rbPressed = false; // Ensure RB is not pressed
    } else if (strcmp(comparisonString, stringRB2) == 0) {
      rbPressed = false;
    } else if (strcmp(comparisonString, stringLB2) == 0) {
      lbPressed = false;
    }
    
    //Servo 2 Logic
    if (strcmp(comparisonString, stringRS) == 0) {
      rsPressed = true;
      lsPressed = false; // Ensure LB is not pressed
    } else if (strcmp(comparisonString, stringLS) == 0) {
      lsPressed = true;
      rsPressed = false; // Ensure RB is not pressed
    } else if (strcmp(comparisonString, stringRS2) == 0) {
      rsPressed = false;
    } else if (strcmp(comparisonString, stringLS2) == 0) {
      lsPressed = false;
    }

    //Servo 3 Logic (claw)
    //May need to change starting position
    if (strcmp(comparisonString, stringA) == 0) {
      if (isServoAt180) {
        // If servo is at 180, move it to 0
        servo3Value = 0;
        isServoAt180 = false; // Update state
      } else {
        // If servo is not at 180, move it to 180
        servo3Value = 180;
        isServoAt180 = true; // Update state
      }
    Serial.println("Servo3Value:");
    Serial.println(servo3Value);
  }

  if (strcmp(comparisonString, stringRT) == 0) {
    for (int i = 16; i <= packetSize; i++) {
      valueString[(i - 16)] = packetBuffer[i];
      }
    valueString[5] = 0;
    valueRt = atoi(valueString);
    Serial.println("RT Value is:");
    Serial.println(valueRt);
  }
  if (strcmp(comparisonString, stringLT) == 0) {
    for (int i = 16; i <= packetSize; i++) {
      valueString[(i - 16)] = packetBuffer[i];
    }
    valueString[5] = 0;
    valueLt = atoi(valueString);
    Serial.println("LT Value is:");
    Serial.println(valueLt);
  }

  //   //Turning
  //   if (valueRx > 0) {
  //   // Turning right
  //   int speedLeft = map(valueRx, 0, 255, 0, 255); // Scale speed based on stick position
  //   motor1.drive(speedLeft); // Left motor moves forward
  //   motor2.drive(-speedLeft); // Right motor moves backward
  // } else if (valueRx < 0) {
  //   // Turning left
  //   int speedRight = map(valueRx, -255, 0, -255, 0); // Scale speed based on stick position
  //   motor1.drive(-speedRight); // Left motor moves backward
  //   motor2.drive(speedRight); // Right motor moves forward
  // } else {
  //   // Stick is in the center, stop turning
  //   motor1.drive(0);
  //   motor2.drive(0);
  // }

    //Wheels forward
    // if (strcmp(comparisonString, stringRT) == 0) {
    //   for (int i = 16; i <= packetSize; i++) {
    //     valueString[(i - 16)] = packetBuffer[i];
    //   }
    //   valueString[5] = 0;
    //   valueRt = atoi(valueString);
    //   Serial.println("RT ");
    //   Serial.println(valueRt);
    //   int motorPos = valueRt;
    //   int motorPos1 = valueRt;
    //   motor1.drive(motorPos);
    //   motor2.drive(motorPos);
    // }
    
    //Wheels backwards
    // if (strcmp(comparisonString, stringLT) == 0) {
    //   for (int i = 16; i <= packetSize; i++) {
    //     valueString[(i - 16)] = packetBuffer[i];
    //   }
    //   valueString[5] = 0;
    //   valueLt = atoi(valueString);
    //   Serial.println("LT ");
    //   Serial.println(valueLt);
    //       int motorPos = -valueLt;
    //   int motorPos1 = -valueLt;
    //   motor1.drive(motorPos);
    //   motor2.drive(motorPos);
    // }

    // if (strcmp(comparisonString, stringLS) == 0) {
    //   Serial.println("Servo3Value:");
    //   Serial.println(servo3Value);
    //   servo3Value = servo3Value - 20;
    // }

    if (strcmp(comparisonString, stringLX) == 0) {
      for (int i = 16; i <= packetSize; i++) {
        valueString[(i - 16)] = packetBuffer[i];
      }
      valueString[5] = 0;
      valueLx = atoi(valueString);
      Serial.println("LX Value is:");
      Serial.println(valueLx);
    }
    if (strcmp(comparisonString, stringLY) == 0) {
      for (int i = 16; i <= packetSize; i++) {
        valueString[(i - 16)] = packetBuffer[i];
      }
      valueString[5] = 0;
      valueLy = atoi(valueString);
      Serial.println("LY Value is:");
      Serial.println(valueLy);
    }

    if (strcmp(comparisonString, stringRX) == 0) {
      for (int i = 16; i <= packetSize; i++) {
        valueString[(i - 16)] = packetBuffer[i];
      }
      valueString[5] = 0;
      valueRx = atoi(valueString);
      Serial.println("RX Value is:");
      Serial.println(valueRx);
    }
    if (strcmp(comparisonString, stringRY) == 0) {
      for (int i = 16; i <= packetSize; i++) {
        valueString[(i - 16)] = packetBuffer[i];
      }
      valueString[5] = 0;
      valueRy = atoi(valueString);
      Serial.println("RY Value is:");
      Serial.println(valueRy);
    }


    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}

void loop1() {  //This Runs on Core 2 and performs all inputs and outputs
  if (ledOn) {
    digitalWrite(LED_BUILTIN, 1);
  } else {
    digitalWrite(LED_BUILTIN, 0);
  }

  // Motor 2 Data Recevial
  int motorPos = valueLt;
  if (motorPos > 50) {
    motorPos = map(valueLt, 50, 255, 0, 255);
    motor1.drive(motorPos);
  } else if (motorPos < -50) {
    motorPos = map(valueLt, -50, -255, 0, -255);
    motor1.drive(motorPos);
  }

  // Motor 1 Data Recevial
  int motorPos1 = valueRt;
  if (motorPos1 > 50) {
    motorPos1 = map(valueRt, 50, 255, 0, 255);
    motor2.drive(motorPos1);
  } else if (motorPos1 < -50) {
    motorPos1 = map(valueRt, -50, -255, 0, -255);
    motor2.drive(motorPos1);
  }

  // Servo 1 Data Recevial
  if (rbPressed) {
    servo1Value++;
    delay(8);
    if (servo1Value > 180) {
      servo1Value = 180; // limit to max
    }
  }
  if (lbPressed) {
    servo1Value--;
    delay(8);
    if (servo1Value < 0) {
      servo1Value = 0; // limit to min
    }
  }
  servo1.write(servo1Value);

  // Servo 2 Data Recevial
  if (rsPressed) {
    servo2Value++;
    //delay(1);
    if (servo2Value > 180) {
      servo2Value = 180; // limit to max
    }
  }
  if (lsPressed) {
    servo2Value--;
    //delay(1);
    if (servo2Value < 0) {
      servo2Value = 0; // limit to min
    }
  }
  servo2.write(servo2Value);

  // Servo 3 Data Recevial
  if (servo3Value > 180) {
    servo3Value = 180;
  } else if (servo3Value < 0) {
    servo3Value = 0;
  }
  servo3.write(servo3Value);
}