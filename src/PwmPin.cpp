#include <Arduino.h>
#include "PwmPin.h"

void PwmPin::configure(byte pin) {
    _pin = pin;
    pinMode(_pin, OUTPUT);
    off();
}

void PwmPin::on() {
    set(255);
}

void PwmPin::off() {
    set(0);
}

void PwmPin::set(byte val) {
    if (_state != val)
    {
        analogWrite(_pin, val);
        _state = val;
    }
}
