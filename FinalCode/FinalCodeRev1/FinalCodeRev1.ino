// MREN 303 Pico W Wifi Gamepad Read and Switch Modes
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

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY); // Left motor
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY); // Roght motor


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
char stringLX[17] = "L Stick X Value";
char stringLY[17] = "L Stick Y Value ";
char stringRX[17] = "R Stick X Value ";
char stringRY[17] = "R Stick Y Value ";
char stringLT[17] = "L Trigger Value ";
char stringRT[17] = "R Trigger Value ";

int valueLt = 0;
int valueRt = 0;

// SERVO VARIABLES ------------------------------------
int servo1Value = 0;
int servo2Value = 0;
int servo3Value = 0;

bool ledOn = false;

bool APressed = false;
bool BPressed = false;

bool lbPressed = false;
bool rbPressed = false;

bool ltPressed = false;
bool rtPressed = false;

bool XPressed = false;
bool YPressed = false;
// ----------------------------------------------------

// MOTOR VARIABLES ------------------------------------
int valueLx = 0;
int valueLy = 0;
int valueRx = 0;
int valueRy = 0;
// ----------------------------------------------------

//game modes
const int IDLE_MODE = 0;
const int AUTO_MODE = 1;
const int MANUAL_MODE = 2;
int current_mode = IDLE_MODE;  // Variable to store the current mode. Starts in idle mode
int manualModePrint = 0;
int idleModePrint = 0;
int autoModePrint = 0;

unsigned long startTime = 0;    // Variable to store the start time
unsigned long currentTime = 0;  // Variable to store the current time

WiFiUDP Udp;

void setup() {  //This handles network function and runs on core 1
  Serial.begin(115200);
  WiFi.begin(STASSID, STAPSK);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(500);
  }
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
}
void setup1() {  //This handles all inputs and outputs and runs on core 2

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

  // Servo Setup
  servo1.attach(servo1Pin, 600, 2500);
  servo2.attach(servo2Pin, 600, 2500);
  servo3.attach(servo3Pin, 600, 2500);

  //Initial Servo Positions
  servo1Value = 180; //og val 45
  servo1.write(servo1Value);

  servo2Value = 80;
  servo2.write(servo2Value);

  servo3Value = 90;
  servo3.write(servo3Value);
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

    // Mode Switching Buttons
    if (strcmp(comparisonString, stringStart) == 0) {
      if (current_mode == IDLE_MODE) {           // You can only go to auto mode from idle mode
        Serial.println("Setting mode to auto");  //this line may be removed for final version
        current_mode = AUTO_MODE;                // Change to auto mode
        startTime = millis();                    // Start recording the time
      }
    }
    if (strcmp(comparisonString, stringBack) == 0) {
      Serial.println("Setting mode to manual");  //this line may be removed for final version
      current_mode = MANUAL_MODE;                // Change to manual mode
    }
    if (strcmp(comparisonString, stringRS) == 0) {
      Serial.println("Setting mode to idle");  //this line may be removed for final version
      current_mode = IDLE_MODE;                // Change to idle mode
    }



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

    // Servo Button Logic
    //Servo 1 Logic
    if (strcmp(comparisonString, stringB) == 0) {
      BPressed = true;
      APressed = false;  // Ensure LB is not pressed
    } else if (strcmp(comparisonString, stringA) == 0) {
      APressed = true;
      BPressed = false;  // Ensure RB is not pressed
    } else if (strcmp(comparisonString, stringB2) == 0) {
      BPressed = false;
    } else if (strcmp(comparisonString, stringA2) == 0) {
      APressed = false;
    }

    // //Servo 2 Logic
    if (strcmp(comparisonString, stringRB) == 0) {
      rbPressed = true;
      lbPressed = false;  // Ensure LB is not pressed
    } else if (strcmp(comparisonString, stringLB) == 0) {
      lbPressed = true;
      rbPressed = false;  // Ensure RB is not pressed
    } else if (strcmp(comparisonString, stringRB2) == 0) {
      rbPressed = false;
    } else if (strcmp(comparisonString, stringLB2) == 0) {
      lbPressed = false;
    }

    // //Servo 3 Logic (claw)
    // if (valueRt > 5) {
    //   rtPressed = true;
    //   ltPressed = false;
    // } else if (valueLt > 5) {
    //   ltPressed = true;
    //   rtPressed = false;
    // } else if (valueRt < 5) {
    //   rtPressed = false;
    // } else if (valueLt < 5) {
    //   ltPressed = false;
    // }

    if (strcmp(comparisonString, stringY) == 0) {
      YPressed = true;
      XPressed = false;  // Ensure LB is not pressed
    } else if (strcmp(comparisonString, stringX) == 0) {
      XPressed = true;
      YPressed = false;  // Ensure RB is not pressed
    } else if (strcmp(comparisonString, stringY2) == 0) {
      YPressed = false;
    } else if (strcmp(comparisonString, stringX2) == 0) {
      XPressed = false;
    }

  // Motor Logic ----------------------------------------

int speedLeft = 0;
int speedRight = 0;

// Turning
if (valueRx > 0) {
  // Right
  //speedLeft += map(valueRx, 0, 255, 0, 255);
  speedLeft += valueRx;
  speedRight -= map(valueRx, 0, 255, 0, 255);
} else if (valueRx < 0) {
  // Left
  int mappedValue = map(-valueRx, 0, 255, 0, 255);
  speedLeft -= mappedValue;
  speedRight += mappedValue;
}

// Driving
if (valueLy > 0) {
  // Forward
  int speedFwd = map(valueLy, 0, 255, 0, 255);
  speedLeft += speedFwd;
  speedRight += speedFwd;
} else if (valueLy < 0) {
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


    // // Wheels forward
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
    
    // // Wheels backwards
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
  // ----------------------------------------------------

    //----------------------
    // send a reply, to the IP address and port that sent us the packet we received
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(ReplyBuffer);
    Udp.endPacket();
  }
}

void loop1() {  //This Runs on Core 2 and performs all inputs and outputs

  currentTime = millis();

  // After spending more than 30 s in auto mode:
  if ((current_mode == AUTO_MODE) && (currentTime - startTime) >= 30000) {
    Serial.println("TIME OUT: changing to manual mode");  //this line may be removed for final version
    current_mode = MANUAL_MODE;                           // Change to manual mode
  }
  studentCode(current_mode);
}

// YOUR CODING GOES HERE
void studentCode(int current_mode) {
  if (current_mode == IDLE_MODE) {
    if (idleModePrint == 0) {
      Serial.println("You are in manual mode");
      idleModePrint = 1;
    }
    digitalWrite(LED_BUILTIN, LOW);  // LED is off for idle mode
                                     // Initialize motors state as off
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(PWMA, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    digitalWrite(PWMB, HIGH);
    // No further action required
  } else if (current_mode == AUTO_MODE) {
    if (autoModePrint == 0) {
      Serial.println("You are in manual mode");
      autoModePrint = 1;
    }
    digitalWrite(LED_BUILTIN, LOW);  // LED is off for auto mode
    // Write additional commands for autonomous mode
    //CAUTION: YOU CANNOT PRESS ANY BUTTONS WHILE IN AUTO MODE UNLESS YOU PASS THE GATE (in this case, press B to go to manual mode)
  } else if (current_mode == MANUAL_MODE) {
    if (manualModePrint == 0) {
      Serial.println("You are in manual mode");
      manualModePrint = 1;
    }
    //this line may be removed for final version
    digitalWrite(LED_BUILTIN, HIGH);  // LED is on for manual mode
    // Write additional commands for manual mode'

    // MOTOR CODE START  -------------------------------------------------------

    // Motor 1 Logic
  // int motorPos1 = valueRt;
  // if (motorPos1 > 50) {
  //   motorPos1 = map(valueRt, 50, 255, 0, 255);
  //   motor2.drive(motorPos1);
  // } else if (motorPos1 < -50) {
  //   motorPos1 = map(valueRt, -50, -255, 0, -255);
  //   motor2.drive(motorPos1);
  // }
  
  // // Motor 2 Logic
  // int motorPos = valueLt;
  // if (motorPos > 50) {
  //   motorPos = map(valueLt, 50, 255, 0, 255);
  //   motor1.drive(motorPos);
  // } else if (motorPos < -50) {
  //   motorPos = map(valueLt, -50, -255, 0, -255);-
  //   motor1.drive(motorPos);
  // }
    // MOTOR CODE END  ---------------------------------------------------------

    // SERVO CODE START --------------------------------------------------------------
    // Servo 1 Logic (GRIPPER)
    // if (BPressed) {
    //   servo1Value++;
    //   delay(8);

    //   if (servo1Value > 115) {
    //     servo1Value = 115;  // limit to max
    //   }
    //   Serial.print("servo1Value: ");
    //   Serial.println(servo1Value);

    // } else if (APressed) {
    //   servo1Value--;
    //   delay(8);

    //   if (servo1Value < 45) {
    //     servo1Value = 45;  // limit to max
    //   }
    //   Serial.print("servo1Value: ");
    //   Serial.println(servo1Value);
    // }
    // servo1.write(servo1Value);
        if (BPressed) {
      servo1Value++;
      delay(8);
      Serial.print("servo1Value: ");
      Serial.println(servo1Value);

    } else if (APressed) {
      servo1Value--;
      delay(8);
      Serial.print("servo1Value: ");
      Serial.println(servo1Value);
    }
    servo1.write(servo1Value);

    // Servo 2 Logic (SCOOP)
    if (rbPressed) {
      servo2Value++;
      delay(4);

      if (servo2Value > 80) {
        servo2Value = 80;  // limit to max
      }
      Serial.print("servo2Value: ");
      Serial.println(servo2Value);
    } else if (lbPressed) {
      servo2Value--;
      delay(4);

      if (servo2Value < 0) {
        servo2Value = 0;  // limit to max
      }
      Serial.print("servo2Value: ");
      Serial.println(servo2Value);
    }
    servo2.write(servo2Value);

    // Servo 3 Logic (CRANE)
    if (YPressed) {
      servo3Value++;
      delay(8);

      if (servo3Value > 135) {
        servo3Value = 135;  // limit to max
      }
      Serial.print("servo3Value: ");
      Serial.println(servo3Value);
    } else if (XPressed) {
      servo3Value--;
      delay(8);

      if (servo3Value < 60) {
        servo3Value = 60;  // limit to max
      }
      Serial.print("servo3Value: ");
      Serial.println(servo3Value);
    }
    servo3.write(servo3Value);
  }
  return;
}
