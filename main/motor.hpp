#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor {
  
  public:
  
    Motor(uint8_t in1Pin, uint8_t in2Pin, uint8_t enablePin, float maxSpeedRPM);

    void enable();              // enable the whole board
    void disable();             // disable the whole board

    void drive(float speed);    // speed in RPM (range: [-maxSpeedRPM, maxSpeedRPM])
    void brake();               // short brake
    void coast();               // spin freely

    float getMaxSpeedRPM();
    void setMaxSpeedRPM(float maxSpeedRPM);

  private:
  
    uint8_t _in1;
    uint8_t _in2;
    uint8_t _en;
    float _maxSpeedRPM;         // max speed in RPM

    static constexpr int _maxPWM = 255;
};

#endif
