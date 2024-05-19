// MREN 303 Pico W Wifi Gamepad Read
// Written For MREN 303

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <Wire.h>
#include <SparkFun_TB6612.h>

Servo servo;

#ifndef STASSID
#define STASSID "MREN203"     //MREN303
#define STAPSK "MREN203wifi"  //picoplease
#endif

#define AIN1 2
#define AIN2 3
#define PWMA 6

#define BIN1 4
#define BIN2 5
#define PWMB 7

#define motor1EncoderA 11
#define motor1EncoderB 12
#define STBY 15

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);

unsigned int localPort = 8888;  // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged\r\n";        // a string to send back
// char Arrays to match commands from gamepad
char stringA[17] = "A1";
char stringB[17] = "B1";
char stringY[17] = "Y1";
char stringX[17] = "X1";
char stringLB[17] = "LB1";
char stringRB[17] = "RB1";
char stringLS[17] = "LS1";
char stringRS[17] = "RS1";
char stringBack[17] = "Back1";
char stringStart[17] = "Start1";
char stringUp[17] = "U-DPad1";
char stringDown[17] = "D-DPad1";
char stringLeft[17] = "L-DPad1";
char stringRight[17] = "R-DPad1";
char stringLX[17] = "LS-X";
char stringLY[17] = "LS-Y";
char stringRX[17] = "RS-X";
char stringRY[17] = "RS-Y";
char stringLT[17] = "LT";
char stringRT[17] = "RT";

int valueLx = 0;
int valueLy = 0;
int valueRx = 0;
int valueRy = 0;
int valueLt = 0;
int valueRt = 0;

bool ledOn = false;

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

  servo.attach(0, 600, 2500);  // not supposed to be here
}
void setup1() {  //This handles all inputs and outputs and runs on core 2

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, 0);
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

    if (strcmp(comparisonString, stringA) == 0) {
      Serial.println("Turning On LED");
      ledOn = true;
    }
    if (strcmp(comparisonString, stringB) == 0) {
      Serial.println("Turning Off LED");
      ledOn = false;
    }

    //----------Rotating servo Milestone----------
    if (strcmp(comparisonString, stringLB) == 0) {
      Serial.println("Turning Servo to 0 deg");
      servo.write(0);
    }
    if (strcmp(comparisonString, stringY) == 0) {
      Serial.println("Turning Servo to 90 deg");
      servo.write(90);
    }
    if (strcmp(comparisonString, stringRB) == 0) {
      Serial.println("Turning Servo to 180 deg");
      servo.write(180);
    }
    //----------Rotating DC Motor Milestone----------
    if (strcmp(comparisonString, stringX) == 0) {
      Serial.println("Starting DC-Motor Loop");
      motor1.drive(255, 3000);
      motor1.brake();
        delay(1000);
      motor1.drive(-255, 3000);
      motor1.brake();
        delay(1000);
    }
    //----------Rotating DC Motor Milestone----------

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
  int servoPos = map(valueLx, -255, 255, 0, 180);
  //servo.write(servoPos);
}