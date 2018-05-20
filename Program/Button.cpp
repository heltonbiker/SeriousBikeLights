#include <Arduino.h>
#include "Button.h"

//uint8_t Button::_pin;

void Button::configure(uint8_t pin)
{
    _pin = pin;
    pinMode(_pin, INPUT_PULLUP);    
}

// void Button::run()
// {
    
// }