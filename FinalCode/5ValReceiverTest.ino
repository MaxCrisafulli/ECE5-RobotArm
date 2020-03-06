 //MAKE SURE TO SET POWER SUPPLY FOR EACH MOTOR AT 12V, 2AMP
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(9, 10); // CE, CSN
Servo claw;
const byte address[6] = "00001";
 
void setup() {
  Serial.begin(9600);
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
    }
}
