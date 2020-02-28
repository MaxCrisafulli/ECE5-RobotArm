#include <Servo.h>
 
Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
 
int pos = 100;    // variable to store the servo position
const int bPinL = 2;
const int bPinR = 4;
int left = 0;
int right = 0;

 
void setup() {
  Serial.begin(9600);
  myservo.attach(6);  // attaches the servo on pin 6 to the servo object
  myservo.write(pos);
  pinMode(bPinL, INPUT);
  pinMode(bPinR, INPUT);
  
}
 
void loop() {
  Serial.println(pos);
  left = digitalRead(bPinL);
  right = digitalRead(bPinR);
  Serial.println(left);
  Serial.println(right);

  if (pos >= 110) {
    pos = 109;
  }
  if (pos <= 0) {
    pos = 1;
  }

  if (left && pos >= 0 && pos <= 110) {
    pos -= 1;
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
  }

  if (right && pos >= 0 && pos <= 110) {
    pos += 1;
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
  }

 /*
  if (digitalRead(bPinL) == HIGH && pos > 0 && pos < 110) {
    pos -= 1;
    for (pos = 0; pos <= 110; pos += 1) { // goes from 0 degrees to 110 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
     } 
  }

  if (digitalRead(bPinR) == HIGH && pos > 0 && pos < 110) {
    pos -= 1;
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  */
}
