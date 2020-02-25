#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.

//POTENTIOMETER PINS
int pot_pin1 = A2;
int potval1 = 0;
int pot_pin2 = A3;
int potval2 = 0;
int pot_pin3 = A4;
int potval3 = 0;

//TIME VARIABLES
const unsigned long T_trans = 10;
long next_trans = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  radio.begin();                  //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MIN);  //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening();          //This sets the module as transmitter
}


void loop()
{
  //RF TRANSMITTER CODE
  if (millis() >= next_trans) {
    potval1 = analogRead(pot_pin1);
    potval2 = analogRead(pot_pin2);
    potval3 = analogRead(pot_pin3);
    radio.write(&potval1, sizeof(potval1));
    radio.write(&potval2, sizeof(potval2));
    radio.write(&potval3, sizeof(potval3));
    next_trans += T_trans;
  }
 }
