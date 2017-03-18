#include <Servo.h>

Servo leftDriveOne;  // create servo object to control a Jag
Servo rightDriveOne;
Servo leftDriveTwo;
Servo rightDriveTwo;
//Servo lift;

int leftJoystick = 0;  // analog pin used to connect the left joystick
int leftVal;    // variable to read the value from the analog pin
int rightJoystick = 2;
int rightVal;
int safetySwitch = 7;
int buttonState = 0;

int leftMax = 903;
int rightMax = 1023;
int leftMin = 0;
int rightMin = 0;
int leftMid = 521;
int rightMid = 508;

void setup() {
  leftDriveOne.attach(9);  // attaches the left drive motor on pin 9 to the servo object
  rightDriveOne.attach(8);
  leftDriveTwo.attach(11);
  rightDriveTwo.attach(10);
  pinMode(safetySwitch, INPUT);
//  lift.attach(14);
  
  //Serial.begin(9800);
}

void loop() {
  buttonState = digitalRead(safetySwitch);
  if (buttonState == LOW) {
    leftVal = analogRead(leftJoystick); // reads the value of the left joystick (value between 0 and 1023)
    //Serial.println(leftVal);
    if (leftVal > leftMid) {
      leftVal = map(leftVal, leftMid, leftMax, 1500, 2000);  
    } else {
      leftVal = map(leftVal, leftMin, 1023, 1000, 2000);  // scale it to use it with the writeMicroseconds function (value between 1000 and 2000)
    }
    leftDriveOne.writeMicroseconds(leftVal);      // tells Jag to output based on the scaled value
    leftDriveTwo.writeMicroseconds(leftVal);
    rightVal = analogRead(rightJoystick);
    //Serial.println(rightVal);
    rightVal = map(rightVal, rightMin, 1023, 2000, 1000);
    rightDriveOne.writeMicroseconds(rightVal);
    rightDriveTwo.writeMicroseconds(rightVal);
    delay(50);
    //Serial.println(leftVal);
    //Serial.println(" ");
    //Serial.println(rightVal);
  }
}
