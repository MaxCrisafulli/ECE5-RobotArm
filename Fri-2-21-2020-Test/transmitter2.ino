#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN         
const byte address[6] = "00001";     //Byte of array representing the address. This is the address where we will send the data. This should be same on the receiving side.
int pot_pin = A2;
int potval = 0;
const unsigned long T_trans = 10;
long next_trans = 0;
/*
const unsigned long T_blink = 500;
long next_blink = 0;
*/

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
  if (millis() >= next_trans) {
    potval = analogRead(pot_pin);
    Serial.println(potval);
    radio.write(&potval, sizeof(potval));
    next_trans += T_trans;
  }
  /*
  if (millis() >= next_blink) {
     digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on 
     delay(100);                        // wait for half a second
     digitalWrite(LED_BUILTIN, LOW);    // turn the LED off 
     next_blink += T_blink;
  }
  */
  
 }
