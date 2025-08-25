#include "encoder.hpp"

Encoder::Encoder(uint8_t pin): pin(pin), ticks(0) {
  pinMode(pin, INPUT_PULLUP);
}

void Encoder::update() {
  /*
   * Update the encoder ticks. This function should be called inside an interrupt service routine (ISR).
   * It increments the ticks count when the encoder pin state changes.
   */

  // No debounce:
  // ticks ++;

  // Debounce:
  unsigned long now = micros();
  if (now - lastTickMicros > _debounceMicros) {
    ticks++;
    lastTickMicros = now;
  }
}

long Encoder::getTicks() {
  return ticks;
}

void Encoder::reset() {
  ticks = 0;
}

void Encoder::setDebounceMicros(unsigned long debounceMicros) {
  _debounceMicros = debounceMicros;
}
