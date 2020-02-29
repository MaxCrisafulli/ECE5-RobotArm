 //MAKE SURE TO SET POWER SUPPLY FOR EACH MOTOR AT 12V, 2AMP
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "10101";


  //RADIO SETUP
  radio.begin();
  radio.openReadingPipe(0, address);   //Setting the address at which we will receive the data
  radio.setPALevel(RF24_PA_MIN);       //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening();              //This sets the module as receiver
}

void loop() {

  //RF RECEIVER CODE
  if (millis() >= next_rec) {
    if (radio.available()) {
      int val1;                         
      int val2;
      int val3;
      int val4;
      int val5;
      //RECEIVING VALUES FROM TRANSMITTER/CONTROLLER   
      radio.read(&val1, sizeof(val1));    //Reading the data (Pot #1)
      radio.read(&val2, sizeof(val2));    //Reading the data (Pot #2)
      radio.read(&val3, sizeof(val3));    //Reading the data (Pot #3)
      radio.read(&val4, sizeof(val4));    //Reading the data (Left Button)
      radio.read(&val5, sizeof(val5));    //Reading the data (Right Button)
      //SET GLOBAL VARIABLES TO RECEIVED VALUES
      pos1 = val1/10;
      pos2 = val2/10;
      pos3 = val3/10;
      left = val4;
      right = val5;
      //PRINT RECEIVED VALUES
      Serial.println(val1);
      Serial.println(val2);
      Serial.println(val3);
      Serial.println(val4);
      Serial.println(val5);
    }
    
    next_rec += T_rec;
  }
  
}
