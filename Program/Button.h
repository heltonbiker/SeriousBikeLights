#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class Button
{
    public:
        bool isPressed;
        bool isLongPressed;
        bool wasPressed;
        bool wasReleased;
        bool wasLongPressed;
        bool wasLongReleased;
        void configure(uint8_t pin);
        virtual void run();
    protected:
        uint8_t _state;
        uint8_t _pin;
        uint8_t _previous_state;
        long _lastWasOff;
};

#endif