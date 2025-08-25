#ifndef DRIVEUNIT_H
#define DRIVEUNIT_H

#include "motor.hpp"
#include "encoder.hpp"


class DriveUnit {

  public:

    DriveUnit(Motor& motor, Encoder& encoder, float ticksPerRevolution, float maxRPM);

    void enable();
    void disable();
    void enablePID();
    void disablePID();

    void setTargetRPM(float rpm);
    void setTargetAngularVelocity(float w);
    void update();  // To be called regularly in the loop

    float getTargetRPM() const;
    float getTargetAngularVelocity() const;

    float getCurrentRPM() const;
    float getCurrentAngularVelocity() const;

    float getMaxRPM() const;
    float getMaxAngularVelocity() const;

    void setGains(float kp, float ki, float kd);

  private:

    Motor& _motor;
    Encoder& _encoder;

    // Encoder
    float _ticksPerRev;
    long _lastTicks = 0;

    // Timing
    unsigned long _lastTime;

    // PID controller
    bool _pidenabled = true;
    float _Kp = 2.0;
    float _Ki = 0.05;
    float _Kd = 0.0;

    float _target = 0.0;
    float _output = 0.0;

    float _integral = 0.0;
    float _lastError = 0.0;

    float _maxRPM;
};

#endif
