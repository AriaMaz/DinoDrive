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
#define STASSID "MREN203"
#define STAPSK "MREN203wifi"
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
char stringA[17] = "A Button Press";
char stringB[17] = "B Button Press";
char stringY[17] = "Y Button Press";
char stringX[17] = "X Button Press";
char stringLB[17] = "LB Button Press";
char stringRB[17] = "RB Button Press";
char stringLS[17] = "L Stick Press";
char stringRS[17] = "R Stick Press";
char stringBack[17] = "Back Press";
char stringStart[17] = "Start Press";
char stringUp[17] = "Up Dpad Press";
char stringDown[17] = "Down Dpad Press";
char stringLeft[17] = "Left Dpad Press";
char stringRight[17] = "Right Dpad Press";
char stringLX[17] = "L Stick X Value ";
char stringLY[17] = "L Stick Y Value ";
char stringRX[17] = "R Stick X Value ";
char stringRY[17] = "R Stick Y Value ";
char stringLT[17] = "L Trigger Value ";
char stringRT[17] = "R Trigger Value ";

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
      Serial.println(packetBuffer[i]);
    }
    comparisonString[16] = 0;

    Serial.println("Comp String:");
    Serial.println(comparisonString);

    //Servo 1 Logic
    if (strcmp(comparisonString, stringRB) == 0) {
      Serial.println("Servo1Value:");
      Serial.println(servo1Value);
      servo1Value = servo1Value + 30;
    }
    if (strcmp(comparisonString, stringLB) == 0) {
      Serial.println("Servo1Value:");
      Serial.println(servo1Value);
      servo1Value = servo1Value - 30;
    }
    //Servo 2 Logic
    if (strcmp(comparisonString, stringB) == 0) {
      Serial.println("Servo2Value:");
      Serial.println(servo2Value);
      servo2Value = servo2Value + 20;
    }
    if (strcmp(comparisonString, stringA) == 0) {
      Serial.println("Servo2Value:");
      Serial.println(servo2Value);
      servo2Value = servo2Value - 20;
    }
    //Servo 3 Logic
    if (strcmp(comparisonString, stringY) == 0) {
      Serial.println("Servo3Value:");
      Serial.println(servo3Value);
      servo3Value = servo3Value + 20;
    }
    if (strcmp(comparisonString, stringX) == 0) {
      Serial.println("Servo3Value:");
      Serial.println(servo3Value);
      servo3Value = servo3Value - 20;
    }

    if (strcmp(comparisonString, stringLX) == 0) {
      for (int i = 16; i <= packetSize; i++) {
        valueString[(i - 16)] = packetBuffer[i];
      }
      valueString[5] = 0;

      valueLx = atoi(valueString);
      Serial.println("LX Value is:");
      Serial.println(valueLx);
    } else if (strcmp(comparisonString, stringLY) == 0) {
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


  //Motor 1 Data Receival
  int motorPositionY = valueLy;
  if (motorPositionY < 200 && motorPositionY > 0 || motorPositionY > -200 && motorPositionY < 0) {
    motorPositionY = 0;
  } else {
    forward(motor1, motor2, motorPositionY);
  }

  int motorPositionX = valueLx;
  if (motorPositionX < 50) {
    if (motorPositionX > -200 && motorPositionX < 0) {
      motorPositionX = 0;
    } else {
      left(motor1, motor2, motorPositionX);
    }
  } else if (motorPositionX > 50) {
    motorPositionX = abs(motorPositionX);
    if (motorPositionX < 200 && motorPositionX > 0) {
      motorPositionX = 0;
    }else{
      right(motor1, motor2, motorPositionX);
    }
  }



  // Servo 1 Data Recevial
  if (servo1Value > 180) {
    servo1Value = 180;
  } else if (servo1Value < 0) {
    servo1Value = 0;
  } else {
    servo1.write(servo1Value);
  }

  // Servo 2 Data Recevial
  if (servo2Value > 180) {
    servo2Value = 180;
  } else if (servo2Value < 0) {
    servo2Value = 0;
  } else {
    servo2.write(servo2Value);
  }

  // Servo 3 Data Recevial

  if (servo3Value > 180) {
    servo3Value = 180;
  } else if (servo3Value < 0) {
    servo3Value = 0;
  }
  servo3.write(servo3Value);
}
