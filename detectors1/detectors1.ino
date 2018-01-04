#include <NewPing.h>

#include <Wire.h>

#define TRIGGER_R_PIN  13
#define ECHO_R_PIN     12

#define TRIGGER_C_PIN  11
#define ECHO_C_PIN     10

//#define TRIGGER_CD_PIN  6
//#define ECHO_CD_PIN     5

#define TRIGGER_L_PIN  9
#define ECHO_L_PIN     8

#define MOTION_DETECTOR_PIN  7

#define MAX_DISTANCE 400

#define MOTOR_I2C_ID 9
#define DISPLAY_I2C_ID 10


//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarL(TRIGGER_L_PIN, ECHO_L_PIN, MAX_DISTANCE);
NewPing sonarC(TRIGGER_C_PIN, ECHO_C_PIN, MAX_DISTANCE);
//NewPing sonarCD(TRIGGER_R_PIN, ECHO_R_PIN, MAX_DISTANCE);
NewPing sonarR(TRIGGER_R_PIN, ECHO_R_PIN, MAX_DISTANCE);

int isMotionDetected = 0;
int commandForMotor = 0;

int distanceL = 0;
int distanceC = 0;
int distanceR = 0;
//int distanceCD = 0;

#define MAX_I2C_MESSAGE_LENGTH 30
char bufferI2CMessage[MAX_I2C_MESSAGE_LENGTH + 1];

void setup() {
  Serial.begin(9600);

  pinMode(MOTION_DETECTOR_PIN, INPUT);

  Wire.begin();
}

void loop() {
  distanceL = sonarL.ping_cm();
  distanceC = sonarC.ping_cm();
  //distanceCD = sonarCD.ping_cm();
  distanceR = sonarR.ping_cm();

  Serial.print("Sonar-> Left:");
  Serial.print(distanceL);

  Serial.print("  Center:");
  Serial.print(distanceC);

  //Serial.print("  Center down:");
  //Serial.print(distanceCD);

  Serial.print("  Right:");
  Serial.print(distanceR);

  Serial.println(" cm");

  isMotionDetected = digitalRead(MOTION_DETECTOR_PIN);
  Serial.print("Motion detection:");
  Serial.println(isMotionDetected);

  if (distanceC < 10) {
    commandForMotor = 0;
  } else if (distanceC > 70) {
    commandForMotor = 1;
  } else if (distanceC <= 70 && distanceC > 40 ) {
    commandForMotor = 0;
  } else if (distanceC <= 40 && distanceC >= 10) {
    commandForMotor = 2;
    delay(2000);
  } else if (distanceL == 0 && distanceR == 0 && distanceC == 0) {
    commandForMotor = 2;
    delay(3000);
    commandForMotor = 5;
    delay(1000);
  }
  //  if (distanceL > 10 && distanceL < 20) {
  //    commandForMotor = 0;
  //  }
  //
  //  if (distanceR > 10 && distanceR < 20) {
  //    commandForMotor = 0;
  //  }


  sendToMotor();
  sendToDisplay();

  delay(300);

}

void sendToDisplay() {
  Wire.beginTransmission(DISPLAY_I2C_ID);
  sprintf(bufferI2CMessage, "L:%d C:%d R:%d MF:%d M:%d", distanceL, distanceC, distanceR, isMotionDetected, commandForMotor);
  Wire.write(bufferI2CMessage);
  Wire.endTransmission();
}

void sendToMotor() {
  Wire.beginTransmission(MOTOR_I2C_ID);
  Wire.write(commandForMotor);
  Wire.endTransmission();
}

