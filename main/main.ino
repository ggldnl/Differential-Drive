#include "config.hpp"
#include "encoder.hpp"
#include "motor.hpp"
#include "driveunit.hpp"


// Motors, Encoders and DriveUnits
Encoder leftEncoder(leftEncoderA);
Motor leftMotor(leftMotorIn1, leftMotorIn2, enable);
DriveUnit leftDriveUnit(leftMotor, leftEncoder, ticksPerRevolution, maxSpeedRPM);

Encoder rightEncoder(rightEncoderA);
Motor rightMotor(rightMotorIn1, rightMotorIn2, enable);
DriveUnit rightDriveUnit(rightMotor, rightEncoder, ticksPerRevolution, maxSpeedRPM);

// Left and right encoder Interrupt Service Routines (increment tick count)
void leftEncoderISR() {
  leftEncoder.update();
}

void rightEncoderISR() {
  rightEncoder.update();
}


void setup() {

  Serial.begin(115200);

  // Encoders setup
  attachInterrupt(digitalPinToInterrupt(leftEncoderA), leftEncoderISR, RISING);
  attachInterrupt(digitalPinToInterrupt(rightEncoderA), rightEncoderISR, RISING);

  // Flip the left motor such that both motors spin on the same direction going forward and backward
  rightMotor.flip();

  // Test the hardware
  // selfTest();
  //leftDriveUnit.disablePID();
  //rightDriveUnit.disablePID();

  // Wait 10 seconds before driving forward
  delay(5000);

  // Set the gains
  float Kp = 2.0;
  float Ki = 2.0;
  float Kd = 0.2;
  leftDriveUnit.setGains(Kp, Ki, Kd);
  rightDriveUnit.setGains(Kp, Ki, Kd);

  float targetRPM = 20;

  leftDriveUnit.enable();
  leftDriveUnit.setTargetRPM(targetRPM);

  rightDriveUnit.enable();
  rightDriveUnit.setTargetRPM(targetRPM);
}

void loop() {


  leftDriveUnit.update();
  rightDriveUnit.update();

  /*
  Serial.print("YMin:");
  Serial.print(0);
  Serial.print(",");
  Serial.print("YMax:");
  Serial.print(maxSpeedRPM);
  Serial.print(",");

  Serial.print("Left:");
  Serial.print(leftDriveUnit.getCurrentRPM());
  Serial.print(",");
  Serial.print("Right:");
  Serial.println(rightDriveUnit.getCurrentRPM());
  */

  delay(50);
}

void selfTest() {
  /**
   * Perform a basic hardware test
   */

  // Enable the motors
  leftMotor.enable();
  rightMotor.enable();

  // Reset just in case
  leftEncoder.reset();
  rightEncoder.reset();

  Serial.print("Left encoder ticks: ");
  Serial.println(leftEncoder.getTicks());

  // Test left motor spinning forward with increasing speed
  Serial.println("Spinning left motor forward...");
  for (int i = 0; i < 255; i++) {
    leftMotor.drive(i / 255.0);
    delay(50);
  }

  // Test left encoder registered a change
  Serial.print("Left encoder ticks: ");
  Serial.println(leftEncoder.getTicks());

  // Test left motor spinning in the opposite direction
  Serial.println("Spinning left motor backward...");
  leftMotor.flip();
  for (int i = 0; i < 255; i++) {
    leftMotor.drive(i / 255.0);
    delay(50);
  }

  // Test left encoder is more or less doubled (we are using a single channel, the encoder will simply increment the counter)
  Serial.print("Left encoder ticks: ");
  Serial.println(leftEncoder.getTicks());

  // Stop the motor
  leftMotor.brake();

  // Repeat the tests for the right motor

  Serial.print("Right encoder ticks: ");
  Serial.println(rightEncoder.getTicks());

  Serial.println("Spinning right motor forward...");
  for (int i = 0; i < 255; i++) {
    rightMotor.drive(i / 255.0);
    delay(50);
  }

  Serial.print("Right encoder ticks: ");
  Serial.println(rightEncoder.getTicks());

  Serial.println("Spinning right motor backward...");
  rightMotor.flip();
  for (int i = 0; i < 255; i++) {
    rightMotor.drive(i / 255.0);
    delay(50);
  }

  Serial.print("Right encoder ticks: ");
  Serial.println(rightEncoder.getTicks());

  // Stop the motor
  rightMotor.brake();

  // Reset
  leftMotor.flip();
  rightMotor.flip();
  leftEncoder.reset();
  rightEncoder.reset();

}