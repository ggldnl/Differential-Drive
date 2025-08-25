// Pinout
const uint8_t leftEncoderA = 2;
const uint8_t leftEncoderB = 7;
const uint8_t leftMotorIn1 = 5;
const uint8_t leftMotorIn2 = 6;

const uint8_t rightEncoderA = 3;
const uint8_t rightEncoderB = 8;
const uint8_t rightMotorIn1 = 10;
const uint8_t rightMotorIn2 = 11;

const uint8_t enable = 4;

// Motor parameters
const int gearRatio = 210;
const int encoderSlots = 3;
const int ticksPerRevolution = encoderSlots * gearRatio;  // Each time the encoder registers 1 tick, the wheel made 1/3 revolution 
const int maxSpeedRPM = 70;