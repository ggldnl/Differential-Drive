#include "driveunit.hpp"

DriveUnit::DriveUnit(Motor& motor, Encoder& encoder, float ticksPerRevolution, float maxRPM)
  : _motor(motor), _encoder(encoder), _ticksPerRev(ticksPerRevolution), _maxRPM(maxRPM){

}

void DriveUnit::enable() {
  _motor.enable();
}

void DriveUnit::disable() {
  _motor.disable();
}

void DriveUnit::enablePID() {
  _pidenabled = true;
}

void DriveUnit::disablePID() {
  _pidenabled = false;
}

void DriveUnit::setTargetRPM(float rpm) {
  if (rpm > _maxRPM) rpm = _maxRPM;
  if (rpm < -_maxRPM) rpm = -_maxRPM;
  _target = rpm;
}

void DriveUnit::setTargetAngularVelocity(float w) {
  float rpm = w * 60.0f / (2.0f * PI);
  setTargetRPM(rpm);
}

float DriveUnit::getCurrentRPM() const {
  return _output;
}

float DriveUnit::getCurrentAngularVelocity() const {
  return _output * 2.0f * PI / 60.0f;
}

float DriveUnit::getTargetRPM() const {
  return _target;
}

float DriveUnit::getTargetAngularVelocity() const {
  return _target * 2.0f * PI / 60.0f;
}

void DriveUnit::update() {

  unsigned long now = millis();
  float dt = (now - _lastTime) / 1000.0f;

  // Skip loop iteration if too soon or bad update
  if (dt <= 0.0001f || isnan(dt) || isinf(dt)) return;
  _lastTime = now;

  // Measure actual RPM from encoder
  long currentTicks = _encoder.getTicks();
  long tickDelta = currentTicks - _lastTicks;
  _lastTicks = currentTicks;

  float direction = (_target >= 0) ? 1.0f : -1.0f;
  float rawRPM = direction * (tickDelta / _ticksPerRev) * (60.0f / dt);

  // Skip bad RPM measurements
  if (isnan(rawRPM) || isinf(rawRPM)) return;

  // _output = measuredRPM;

  // Apply exponential smoothing (low-pass filter)
  float alpha = 0.1f;
  _output = alpha * rawRPM + (1.0f - alpha) * _output;

  if (_pidenabled) {
    
    // PID control
    float error = _target - _output;
    _integral += error * dt;
    float derivative = (error - _lastError) / dt;
    _lastError = error;

    // Maybe we can add a feedforward term
    float control = _Kp * error + _Ki * _integral + _Kd * derivative;
    float normalized = control / _maxRPM;

    _motor.drive(normalized);
  } else {
    _motor.drive(_target / _maxRPM);
  }
}


float DriveUnit::getMaxRPM() const {
  return _maxRPM;
}

float DriveUnit::getMaxAngularVelocity() const {
  return _maxRPM * 2.0f * PI / 60.0f;
}

void DriveUnit::setGains(float Kp, float Ki, float Kd) {
  _Kp = Kp;
  _Ki = Ki;
  _Kd = Kd;
}
