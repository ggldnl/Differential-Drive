#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>


class Encoder {

  public:

    Encoder(uint8_t pin);

    void setDebounceMicros(unsigned long debounceMicros);
    long getTicks();
    void reset();
    void update();

  private:

    volatile long ticks;
    uint8_t pin;

    // Software debouncing
    volatile unsigned long lastTickMicros;
    unsigned long _debounceMicros = 2000;  // 2ms debounce

};

#endif
