//MAKE SURE TO SET POWER SUPPLY FOR EACH MOTOR AT 12V, 2AMP
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

//TIME VARIABLES
const unsigned long T_rec = 5;
long next_rec = 0;
const unsigned long T_spin = 1000;
long next_spin = 0;


//MOTOR PINS
const int dirPin1 = 2;  // Direction
const int stepPin1 = 3; // Step
const int dirPin2 = 4;  
const int stepPin2 = 5; 
const int dirPi3 = 6;  
const int stepPin3 = 7; 

//POSITION VARIABLES
int pos1  =  0;
int curpos1 = 0;
int pos2  =  0;
int curpos2 = 0;
int pos3  =  0;
int curpos3 = 0;
 
void setup() {
  pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(stepPin3,OUTPUT); 
  pinMode(dirPin3,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop() {

  //RF RECEIVER CODE
  if (millis() >= next_rec) {
    if (radio.available())              //Looking for the data.
    {
      int val1;                         //Saving the incoming data
      int val2;
      int val3;   
      radio.read(&val1, sizeof(val1));    //Reading the data
      radio.read(&val2, sizeof(val2));    //Reading the data
      radio.read(&val3, sizeof(val3));    //Reading the data
      pos1 = val1/10;
      pos2 = val2/10;
      pos3 = val3/10;
    }
    next_rec += T_rec;
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
      delay(10);  
      digitalWrite(stepPin1,LOW);
      delay(10);
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
      delay(10);  
      digitalWrite(stepPin2,LOW);
      delay(10);
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
      delay(10);  
      digitalWrite(stepPin3,LOW);
      delay(10);
      curpos3 += 1;
    }
    
    curpos3 = pos3;
    DIFF_STEPS = 0;
  }
  
}
