// Adafruit Motor shield library
// copyright Adafruit Industries LLC, 2009
// this code is public domain, enjoy!
// https://github.com/adafruit/Adafruit-Motor-Shield-library

#include <AFMotor.h>

#include <Wire.h>

#define MAX_SPEED 190

#define MOTOR_I2C_ID 9

AF_DCMotor motorFR(1);
AF_DCMotor motorFL(2);
AF_DCMotor motorRR(3);
AF_DCMotor motorRL(4);

uint8_t i;
int receivedDataFromI2C = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Motor test!");

  motor_Stop();

  Wire.begin(MOTOR_I2C_ID);
  Wire.onReceive(receiveEvent);

  delay(10000);
}

void loop() {
  //motor_All(FORWARD, MAX_SPEED);
  //delay(5000);

  //motor_Stop();
  //delay(5000);

  //  motorTest(motorFR);
  //  motorTest(motorFL);
  //  motorTest(motorRL);
  //  motorTest(motorRR);
  delay(500);
}

void motorTest(AF_DCMotor motor) {
  motor.run(FORWARD);
  for (i = 0; i < MAX_SPEED; i++) {
    motor.setSpeed(i);
    delay(10);
  }

  for (i = MAX_SPEED; i != 0; i--) {
    motor.setSpeed(i);
    delay(10);
  }

  motor.run(BACKWARD);
  for (i = 0; i < MAX_SPEED; i++) {
    motor.setSpeed(i);
    delay(10);
  }

  for (i = MAX_SPEED; i != 0; i--) {
    motor.setSpeed(i);
    delay(10);
  }

  Serial.print("tech");
  motor.run(RELEASE);
  delay(1000);
}

void motor_All(uint8_t command, int speed) {
  motorFR.run(command);
  motorFL.run(command);
  motorRL.run(command);
  motorRR.run(command);

  motorFR.setSpeed(speed);
  motorFL.setSpeed(speed);
  motorRL.setSpeed(speed);
  motorRR.setSpeed(speed);

  Serial.print("motor: command: ");
  Serial.print(command);
  Serial.print(". Speed: ");
  Serial.print(speed);
  Serial.println();
}


void motor_Stop() {
  motorFR.run(RELEASE);
  motorFL.run(RELEASE);
  motorRL.run(RELEASE);
  motorRR.run(RELEASE);

  Serial.println("motor: full stop");
}

void receiveEvent(int bytes) {
  receivedDataFromI2C = Wire.read();

  if (0 == receivedDataFromI2C) {
    //stop
    motor_Stop();
  } else if (1 == receivedDataFromI2C) {
    //forward
    motor_All(FORWARD, MAX_SPEED);
  } else if (2 == receivedDataFromI2C) {
    //backward
    motor_All(BACKWARD, MAX_SPEED / 2);
  } else if (5 == receivedDataFromI2C) {
    // rotate right
    motorFR.run(BACKWARD);
    motorFL.run(FORWARD);
    motorRL.run(FORWARD);
    motorRR.run(BACKWARD);

    motorFR.setSpeed(MAX_SPEED);
    motorFL.setSpeed(MAX_SPEED);
    motorRL.setSpeed(MAX_SPEED);
    motorRR.setSpeed(MAX_SPEED);
  }
}

