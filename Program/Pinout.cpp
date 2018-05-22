#include <Arduino.h>

/*
OPEN QUESTIONS:
  - What to trade for the ability to use siren? (tone interferes with pwm on pins 3 and 11)
    - Do I need PWM in EVERY pin ALL the time? (most probably not for turn signals?)
*/

class Pinout
{
  public:
    // Interrupts
    static const uint8_t SpeedSensorPin = 2;


    // I2C outputs
    static const uint8_t SDA = A4;
    static const uint8_t SCL = A5;


    // PWM Outs (Lights)
    static const uint8_t HeadLightPin = 3; // pwm suffers interference from tone()

    static const uint8_t LeftSignalPin = 5;
    static const uint8_t RightSignalPin = 6;

    static const uint8_t TailRedLeftPin = 9;
    static const uint8_t TailRedRightPin = 11; // pwm suffers interference from tone()
    static const uint8_t TailBluePin = 10;


    // Analog Ins
    static const uint8_t LightSensorPin = A1;


    // Digital Ins
    static const uint8_t LeftTurnButtonPin = 1;
    static const uint8_t RightTurnButtonPin = 4;

    static const uint8_t BrakeSensorPin = A2;

    static const uint8_t ModeButtonPin = 12;
    static const uint8_t HornButtonPin = A3;


    // Digital Outs
    static const uint8_t SirenPin = 7;
    static const uint8_t BuzzerPin = 8;
    static const uint8_t StatusLedPin = 13;
};