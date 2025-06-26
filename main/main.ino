#include "encoder.hpp"
#include "motor.hpp"
#include "driveunit.hpp"

uint8_t leftEncoderPin = 2;
uint8_t leftMotorIn1Pin = 5;
uint8_t leftMotorIn2Pin = 9;

uint8_t rightEncoderPin = 3;
uint8_t rightMotorIn1Pin = 10;
uint8_t rightMotorIn2Pin = 11;

uint8_t enablePin = 8;

const int ticksPerRevolution = 20;
const int maxSpeedRPM = 250;

Encoder leftEncoder(leftEncoderPin);
Motor leftMotor(leftMotorIn1Pin, leftMotorIn2Pin, enablePin, maxSpeedRPM);
DriveUnit leftDriveUnit(leftMotor, leftEncoder, ticksPerRevolution);

Encoder rightEncoder(rightEncoderPin);
Motor rightMotor(rightMotorIn1Pin, rightMotorIn2Pin, enablePin, maxSpeedRPM);
DriveUnit rightDriveUnit(rightMotor, rightEncoder, ticksPerRevolution);

void leftEncoderISR() {
  leftEncoder.update();
}

void rightEncoderISR() {
  rightEncoder.update();
}

// Variables for RPM calculation
unsigned long lastTime = 0;
long lastTickCount = 0;
const unsigned long interval = 500;  // ms

void setup() {

  Serial.begin(115200);

  // Encoders setup
  attachInterrupt(digitalPinToInterrupt(leftEncoderPin), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoderPin), rightEncoderISR, RISING);

  // Set the gains
  float Kp = 3.0;
  float Ki = 1.0;
  float Kd = 0.5;
  leftDriveUnit.setGains(Kp, Ki, Kd);
  rightDriveUnit.setGains(Kp, Ki, Kd);

  float targetRPM = 100;

  leftDriveUnit.enable();
  leftDriveUnit.setTargetRPM(targetRPM);

  rightDriveUnit.enable();
  rightDriveUnit.setTargetRPM(targetRPM);
}

void loop() {

  leftDriveUnit.update();
  rightDriveUnit.update();

  Serial.print("Left:");
  Serial.print(leftDriveUnit.getCurrentRPM());
  Serial.print(",");
  Serial.print("Right:");
  Serial.println(rightDriveUnit.getCurrentRPM());

  delay(500);
}
