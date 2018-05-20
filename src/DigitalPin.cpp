#include <Arduino.h>
#include "DigitalPin.h"

void DigitalPin::configure(byte pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
    off();
}

void DigitalPin::on() {
    set(HIGH);
}

void DigitalPin::off() {
    set(LOW);
}

void DigitalPin::set(byte val) {
    if (_state != val)
    {
        digitalWrite(_pin, val);
        _state = val;
    }
}
