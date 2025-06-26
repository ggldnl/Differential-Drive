#include "motor.hpp"

Motor::Motor(uint8_t in1Pin, uint8_t in2Pin, uint8_t enablePin, float maxSpeedRPM)
  : _in1(in1Pin), _in2(in2Pin), _en(enablePin), _maxSpeedRPM(maxSpeedRPM) {
  /*
  in1 and in2 should be PWM capable.
  */
  pinMode(_in1, OUTPUT);
  pinMode(_in2, OUTPUT);
  pinMode(_en, OUTPUT);
  disable(); // default to off

  // Prevent floating pins to make the motor spin if we enable it without issuing a drive velocity
  drive(0);

  // Match 0–255 PWM scale
  // analogWriteRange(_maxPWM);
}

float Motor::getMaxSpeedRPM() {
  return _maxSpeedRPM;
}

void Motor::setMaxSpeedRPM(float maxSpeedRPM) {
  _maxSpeedRPM = maxSpeedRPM;
}

void Motor::enable() {
  digitalWrite(_en, HIGH);
}

void Motor::disable() {
  digitalWrite(_en, LOW);
}

void Motor::drive(float speed) {

  // Clamp input to [-_maxSpeedRPM, maxSpeedRPM]
  if (speed > _maxSpeedRPM) speed = _maxSpeedRPM;
  if (speed < -_maxSpeedRPM) speed = -_maxSpeedRPM;

  // Normalize to [-1, 1]
  float normalized = speed / _maxSpeedRPM;

  // Scale to PWM range
  int pwm = int(fabs(normalized) * _maxPWM);
  
  if (speed > 0) {
    analogWrite(_in1, pwm);
    digitalWrite(_in2, LOW);
  } else if (speed < 0) {
    analogWrite(_in2, pwm);
    digitalWrite(_in1, LOW);
  } else {
    brake(); // stop actively
  }
}

void Motor::brake() {
  /*
  Both motor terminals are connected to HIGH (low impedance staste). 
  This creates a low-resistance path through the H-bridge, 
  rapidly stopping the motor due to back EMF dissipation. 
  Motor "locks" in place.
  */
  digitalWrite(_in1, HIGH);
  digitalWrite(_in2, HIGH);
}

void Motor::coast() {
  /*
  Both terminals are set LOW (high impedance state). 
  The motor spins freely and slows down gradually. 
  No braking force is applied.
  */
  digitalWrite(_in1, LOW);
  digitalWrite(_in2, LOW);
}
