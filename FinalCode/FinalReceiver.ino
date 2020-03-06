 //MAKE SURE TO SET POWER SUPPLY FOR EACH MOTOR AT 12V, 2AMP
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(9, 10); // CE, CSN
Servo claw;
const byte address[6] = "00001";

//MOTOR PINS
const int dirPin1 = 2;  
const int stepPin1 = 3; 
const int dirPin2 = 4;  
const int stepPin2 = 5; 
const int dirPin3 = 6;  
const int stepPin3 = 7; 

//POSITION VARIABLES
int pos1  =  0;
int curpos1 = 0;
int pos2  =  0;
int curpos2 = 0;
int pos3  =  0;
int curpos3 = 0;

//CLAW PINS
int clawpos = 100;   
const int bPinL = 2;
const int bPinR = 4;
int left;
int right;
 
void setup() {
  Serial.begin(9600);
  
  //STEPPER SETUP
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(stepPin3,OUTPUT); 
  pinMode(dirPin3,OUTPUT);
  
  //CLAW SETUP
  claw.attach(1); 
  claw.write(clawpos);
  
  //RADIO SETUP
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop() {

  //RF RECEIVER CODE
    if (radio.available()) {
      int datarr[5];
      //RECEIVING VALUES FROM TRANSMITTER/CONTROLLER   
      radio.read(&datarr, sizeof(datarr));    //Reading the data (Pot #1)
      //PRINT RECEIVED VALUES
      for (int i = 0; i < 5; i++) {
        Serial.println(datarr[i]);
      }
      pos1 = datarr[0];
      pos2 = datarr[1]; 
      pos3 = datarr[2]; 
      left = datarr[3]; 
      right = datarr[4]; 
    }
    
  //CLAW CODE
  if (left || right) {
    if (clawpos >= 110) {
      clawpos = 109;
    }
    if (clawpos <= 0) {
      clawpos = 1;
    }
    if (left && clawpos >= 0 && clawpos <= 110) {
      clawpos -= 1;
      claw.write(clawpos);              // tell servo to go to position in variable 'pos'
    }

    if (right && clawpos >= 0 && clawpos <= 110) {
      clawpos += 1;
      claw.write(clawpos);              // tell servo to go to position in variable 'pos'
    }
  }

  //MOTOR 1 LOOP 
  if (curpos1 != pos1) {
    //LOCAL LOOP VARIABLES
    int DIFF_STEPS = 0;
    int DELTASTEP = pos1-curpos1;
    DIFF_STEPS = 2 * abs(DELTASTEP);

    //DIRECTION CHECKS
    if (curpos1 > pos1) {
      digitalWrite(dirPin1,HIGH);
      //SETS DIRECTION AS FORWARD
    }
    
    else if (curpos1 < pos1){
      digitalWrite(dirPin1,LOW);
      //SETS DIRECTION AS BACK
    }

    //MOVEMENT COMMANDS
    for (int x = 0; x < DIFF_STEPS; x++) {
      digitalWrite(stepPin1,HIGH);
      delay(5);  
      digitalWrite(stepPin1,LOW);
      delay(5);
      curpos1 += 1;
    }
    
    curpos1 = pos1;
    DIFF_STEPS = 0;
  }

  //MOTOR 2 LOOP 
  if (curpos2 != pos2) {
    //LOCAL LOOP VARIABLES
    int DIFF_STEPS = 0;
    int DELTASTEP = pos2-curpos2;
    DIFF_STEPS = 2 * abs(DELTASTEP);

    //DIRECTION CHECKS
    if (curpos2 > pos2) {
      digitalWrite(dirPin2,HIGH);
      //SETS DIRECTION AS FORWARD
    }
    
    else if (curpos2 < pos2){
      digitalWrite(dirPin2,LOW);
      //SETS DIRECTION AS BACK
    }

    //MOVEMENT COMMANDS
    for (int x = 0; x < DIFF_STEPS; x++) {
      digitalWrite(stepPin2,HIGH);
      delay(5);  
      digitalWrite(stepPin2,LOW);
      delay(5);
      curpos2 += 1;
    }
    
    curpos2 = pos2;
    DIFF_STEPS = 0;
  }

  //MOTOR 3 LOOP 
  if (curpos3 != pos3) {
    //LOCAL LOOP VARIABLES
    int DIFF_STEPS = 0;
    int DELTASTEP = pos3-curpos3;
    DIFF_STEPS = 2 * abs(DELTASTEP);

    //DIRECTION CHECKS
    if (curpos3 > pos3) {
      digitalWrite(dirPin3,HIGH);
      //SETS DIRECTION AS FORWARD
    }
    
    else if (curpos3 < pos3){
      digitalWrite(dirPin3,LOW);
      //SETS DIRECTION AS BACK
    }

    //MOVEMENT COMMANDS
    for (int x = 0; x < DIFF_STEPS; x++) {
      digitalWrite(stepPin3,HIGH);
      delay(5);  
      digitalWrite(stepPin3,LOW);
      delay(5);
      curpos3 += 1;
    }
    
    curpos3 = pos3;
    DIFF_STEPS = 0;
  }
  
}
