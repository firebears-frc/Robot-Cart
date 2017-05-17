#include <Servo.h>

Servo leftDriveOne;  // create servo object to control a Jag
Servo rightDriveOne;
Servo leftDriveTwo;
Servo rightDriveTwo;
Servo liftMotor;

int leftJoystick = 0;  // analog pin used to connect the left joystick
int leftVal;    // variable to read the value from the analog pin
int rightJoystick = 2;
int rightVal;
int safetySwitch = 7;
int buttonState = 0;
int liftUp = 2;
int liftDown = 3;
int liftLimitUp = 5;
int liftLimitDown = 4;

int leftMax = 1023;
int rightMax = 1023;
int leftMin = 0;
int rightMin = 0;
int leftMid = 525;
int rightMid = 508;

void setup() {
  liftMotor.attach(6);
  leftDriveOne.attach(8);  // attaches the left drive motor on pin 9 to the servo object
  rightDriveOne.attach(9);
  leftDriveTwo.attach(10);
  rightDriveTwo.attach(11);
  pinMode(safetySwitch, INPUT);
  pinMode(liftUp, INPUT);
  pinMode(liftDown, INPUT);
  pinMode(liftLimitUp, INPUT_PULLUP);
  pinMode(liftLimitDown, INPUT_PULLUP);
  
  Serial.begin(9800);
}

void loop() {
  buttonState = digitalRead(safetySwitch);
  if (buttonState == LOW) {
    leftVal = analogRead(leftJoystick); // reads the value of the left joystick (value between 0 and 1023)
    leftVal = map(leftVal, leftMin, 1023, 1000, 2000);
    if (digitalRead(liftDown) == HIGH && digitalRead(liftUp) == HIGH) {
      leftDriveOne.writeMicroseconds(leftVal);      // tells Jag to output based on the scaled value
      leftDriveTwo.writeMicroseconds(leftVal);
    }
    rightVal = analogRead(rightJoystick);
    rightVal = map(rightVal, rightMin, 1023, 2000, 1000);
    if (digitalRead(liftDown) == HIGH && digitalRead(liftUp) == HIGH) {
      rightDriveOne.writeMicroseconds(rightVal);
      rightDriveTwo.writeMicroseconds(rightVal);
    }
    delay(50);

    leftVal = analogRead(leftJoystick);
    rightVal = analogRead(rightJoystick);
    if (digitalRead(liftUp) == LOW) {
      liftMotor.writeMicroseconds(1000);
      if (digitalRead(liftLimitUp) == LOW) {
        liftMotor.writeMicroseconds(1500);
      }
    }
    if (digitalRead(liftDown) == LOW) {
      liftMotor.writeMicroseconds(2000);
      if (digitalRead(liftLimitDown) == LOW) {
          liftMotor.writeMicroseconds(1500);
      }
    } 
    if (digitalRead(liftDown) == HIGH && digitalRead(liftUp) == HIGH || leftVal > (leftMid + 10) || leftVal < (leftMid - 10) || rightVal > (rightMid + 10) || rightVal < (rightMid - 10)) {
        liftMotor.writeMicroseconds(1500);
    }
  }
}
