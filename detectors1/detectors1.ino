#include <NewPing.h>

#define TRIGGER_R_PIN  13
#define ECHO_R_PIN     12

#define TRIGGER_C_PIN  11
#define ECHO_C_PIN     10

#define TRIGGER_L_PIN  9
#define ECHO_L_PIN     8

#define MOTION_DETECTOR_PIN  7

#define MAX_DISTANCE 500


//NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing sonarL(TRIGGER_L_PIN, ECHO_L_PIN, MAX_DISTANCE);
NewPing sonarC(TRIGGER_C_PIN, ECHO_C_PIN, MAX_DISTANCE);
NewPing sonarR(TRIGGER_R_PIN, ECHO_R_PIN, MAX_DISTANCE);


int isMotionDetected = 0;

void setup() {
  Serial.begin(9600);

  pinMode(MOTION_DETECTOR_PIN, INPUT);
}

void loop() {
  Serial.print("Sonar-> Left:");
  Serial.print(sonarL.ping_cm());

  Serial.print("  Center:");
  Serial.print(sonarC.ping_cm());

  Serial.print("  Right:");
  Serial.print(sonarR.ping_cm());

  Serial.println(" cm");

  isMotionDetected = digitalRead(MOTION_DETECTOR_PIN);
  Serial.print("Motion detection:");
  Serial.println(isMotionDetected);

  delay(1000);
}



