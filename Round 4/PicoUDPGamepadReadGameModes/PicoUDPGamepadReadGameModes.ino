// MREN 303 Pico W Wifi Gamepad Read and Switch Modes
// Written For MREN 303 

#include <WiFi.h>
#include <WiFiUdp.h>
#include <Servo.h>
#include <Wire.h>

Servo myservo; 

#ifndef STASSID
#define STASSID "MREN303"
#define STAPSK "picoplease"
#endif

//motor pins
#define STBY 14
#define PWMA 13
#define AIN1 12
#define AIN2 11
#define PWMB 10
#define BIN1 9
#define BIN2 8

unsigned int localPort = 8888;  // local port to listen on

// buffers for receiving and sending data
char packetBuffer[UDP_TX_PACKET_MAX_SIZE + 1];  // buffer to hold incoming packet,
char ReplyBuffer[] = "acknowledged\r\n";        // a string to send back
// char Arrays to match commands from gamepad 
char stringA[17] =    "A Button Press";
char stringB[17] =    "B Button Press";
char stringY[17] =    "Y Button Press";
char stringX[17] =    "X Button Press";
char stringLB[17] =   "LB Button Press";
char stringRB[17] =   "RB Button Press";
char stringLS[17] =   "L Stick Press";
char stringRS[17] =   "R Stick Press";
char stringBack[17]=  "Back Press";
char stringStart[17]= "Start Press";
char stringUp[17] =   "Up Dpad Press";
char stringDown[17] = "Down Dpad Press";
char stringLeft[17] = "Left Dpad Press";
char stringRight[17]= "Right Dpad Press";
char stringLX[17] =   "L Stick X Value ";
char stringLY[17] =   "L Stick Y Value ";
char stringRX[17] =   "R Stick X Value ";
char stringRY[17] =   "R Stick Y Value ";
char stringLT[17] =   "L Trigger Value ";
char stringRT[17] =   "R Trigger Value ";

int valueLx = 0;
int valueLy = 0;
int valueRx = 0;
int valueRy = 0;
int valueLt = 0;
int valueRt = 0; 

//game modes
const int IDLE_MODE = 0;
const int AUTO_MODE = 1;
const int MANUAL_MODE = 2;
int current_mode = IDLE_MODE; // Variable to store the current mode. Starts in idle mode

unsigned long startTime = 0;  // Variable to store the start time
unsigned long currentTime = 0; // Variable to store the current time

WiFiUDP Udp;

void setup() { //This handles network function and runs on core 1
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
void setup1(){ //This handles all inputs and outputs and runs on core 2
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,0);
  myservo.attach(15);

  // Initialize motor driver pins as outputs
  pinMode(STBY, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);
}

void loop() { //This loop executes on Core 1 of the Pico, handles networking and recieves commands
  // if there's data available, read a packet
  int packetSize = Udp.parsePacket();
  if (packetSize) {
    Serial.printf("Received packet of size %d from %s:%d\n    (to %s:%d)\n", packetSize, Udp.remoteIP().toString().c_str(), Udp.remotePort(), Udp.destinationIP().toString().c_str(), Udp.localPort());

    // read the packet into packetBufffer
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;

    char comparisonString[17] = "";
    char valueString[5] = "";

    for (int i=0; i<16 ; i++){
      comparisonString[i]=packetBuffer[i];
    }
    comparisonString[16] = 0;
    
    Serial.println("Comp String:");
    Serial.println(comparisonString);

    if (strcmp(comparisonString,stringA) == 0){
      if (current_mode == IDLE_MODE){ // You can only go to auto mode from idle mode
        Serial.println("Setting mode to auto");//this line may be removed for final version
        current_mode = AUTO_MODE; // Change to auto mode
        startTime = millis();  // Start recording the time
      }           
    }
    if (strcmp(comparisonString,stringB) == 0){
      Serial.println("Setting mode to manual");//this line may be removed for final version
      current_mode = MANUAL_MODE; // Change to manual mode
    }
    if (strcmp(comparisonString,stringY) == 0){
      Serial.println("Setting mode to idle");//this line may be removed for final version
      current_mode = IDLE_MODE; // Change to idle mode
    }   
    if (strcmp(comparisonString,stringLX) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueLx = atoi(valueString);
      Serial.println("LX Value is:");
      Serial.println(valueLx);
    }
    if (strcmp(comparisonString,stringLY) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueLy = atoi(valueString);
      Serial.println("LY Value is:");
      Serial.println(valueLy);
    }
    if (strcmp(comparisonString,stringRX) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueRx = atoi(valueString);
      Serial.println("RX Value is:");
      Serial.println(valueRx);
    }
    if (strcmp(comparisonString,stringRY) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueRy = atoi(valueString);
      Serial.println("RY Value is:");
      Serial.println(valueRy);
    }
    if (strcmp(comparisonString,stringRT) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
      valueString[5] = 0;
      valueRt = atoi(valueString);
      Serial.println("RT Value is:");
      Serial.println(valueRt);
    }
    if (strcmp(comparisonString,stringLT) == 0){
      for(int i=16; i<=packetSize ; i++){
        valueString[(i-16)] = packetBuffer[i];}
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

void loop1(){ //This Runs on Core 2 and performs all inputs and outputs

currentTime = millis();

// After spending more than 30 s in auto mode:
if ((current_mode == AUTO_MODE) && (currentTime - startTime) >= 30000) {
  Serial.println("TIME OUT: changing to manual mode");//this line may be removed for final version
  current_mode = MANUAL_MODE; // Change to manual mode
  }
studentCode(current_mode);
delay(1000); //this line may be removed for final version
}

// YOUR CODING GOES HERE
void studentCode(int current_mode){ 
  if(current_mode == IDLE_MODE){
   Serial.println("You are in idle mode");//this line may be removed for final version
   digitalWrite(LED_BUILTIN, LOW); // LED is off for idle mode
   // Initialize motors state as off
    digitalWrite(STBY, HIGH);
    digitalWrite(AIN1, LOW);
    digitalWrite(AIN2, LOW);
    digitalWrite(PWMA, HIGH);
    digitalWrite(BIN1, LOW);
    digitalWrite(BIN2, LOW);
    digitalWrite(PWMB, HIGH);
    // No further action required
  }
  else if (current_mode == AUTO_MODE){
    Serial.println("You are in auto mode");//this line may be removed for final version
    digitalWrite(LED_BUILTIN, LOW); // LED is off for auto mode
    // Write additional commands for autonomous mode
    //CAUTION: YOU CANNOT PRESS ANY BUTTONS WHILE IN AUTO MODE UNLESS YOU PASS THE GATE (in this case, press B to go to manual mode)
  }
  else if (current_mode == MANUAL_MODE){
    Serial.println("You are in manual mode");//this line may be removed for final version
    digitalWrite(LED_BUILTIN, HIGH); // LED is on for manual mode
    // Write additional commands for manual mode
  }
  return;
}




