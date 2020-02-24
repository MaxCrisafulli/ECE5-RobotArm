#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";

const unsigned long T_rec = 5;
long next_rec = 0;
const unsigned long T_spin = 1000;
long next_spin = 0;

int deltime = 0;
const int dirPin = 2;  // Direction
const int stepPin = 3; // Step
int pos  =  0;
int curpos = 0;
 
void setup() {
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop() {
  if (millis() >= next_rec) {
    if (radio.available())              //Looking for the data.
    {
      int val;                          //Saving the incoming data
      radio.read(&val, sizeof(val));    //Reading the data
      pos = val/10;
    }
    next_rec += T_rec;
  }


 
  if (curpos != pos) {
    int DIFF_STEPS = 0;
    int DELTASTEP = pos-curpos;
    DIFF_STEPS = 2 * abs(DELTASTEP);
    
    Serial.println(curpos);
    Serial.println(pos);
    Serial.println(DIFF_STEPS);
    Serial.println(DELTASTEP);
    Serial.println("");
    
    if (curpos > pos) {
      digitalWrite(dirPin,HIGH);
      Serial.println("Forward");
    }
    
    else if (curpos < pos){
      digitalWrite(dirPin,LOW);
      Serial.println("Back");
    }
    
    for (int x = 0; x < DIFF_STEPS; x++) {
      digitalWrite(stepPin,HIGH);
      delay(10);  
      digitalWrite(stepPin,LOW);
      delay(10);
      curpos += 1;
    }
    
    curpos = pos;
    DIFF_STEPS = 0;
  }
}

//set at 12V 2Amp
