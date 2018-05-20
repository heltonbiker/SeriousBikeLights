#include <Arduino.h>
#include "TriggeredButton.h"

float TriggeredButton::_factor = 0.7;
float TriggeredButton::_margin = 0.1;
long TriggeredButton::_longPressInterval = 1000;

typedef enum {
    BUTTON_OFF = 0,
    BUTTON_ON = 1,
    BUTTON_LONG = 2
};


TriggeredButton::TriggeredButton()
{
    _previous_state = _state = BUTTON_OFF;
    _trigger_state = HIGH;
    _current_value = 1;
}


void TriggeredButton::run()
{
    long currentTime = millis();

    // initialize variables for this call
    wasPressed = wasReleased = wasLongPressed = wasLongReleased = isPressed = isLongPressed = false;


    // read and filter value
    int reading = digitalRead(_pin);
    _current_value = _current_value * _factor + reading * (1 - _factor);


    // check if button changed state
    if (_trigger_state == HIGH && _current_value < _margin)
    {
        _trigger_state = LOW;
    }
    else
    if (_trigger_state == LOW && _current_value > (1 - _margin))
    {
        _trigger_state = HIGH;
    }


    // was it a long press?
    bool longPressed = false;
    if (currentTime - _lastWasOff > _longPressInterval)
        longPressed = true;


    // set state and state-change event flags
    if (_trigger_state == LOW)  // button is pressed now
    {
        isPressed = true;

        if (longPressed)  // ...and for long enough
        {
            isLongPressed = true;

            if (_previous_state == BUTTON_ON)
            {
                wasLongPressed = true;
                _state = BUTTON_LONG;
            }
        }
        else
        if (_previous_state == BUTTON_OFF)
        {           
            wasPressed = true;
            _state = BUTTON_ON;
        }
    }    
    else
    if (_trigger_state == HIGH)  // button not pressed
    {
        if (_previous_state == BUTTON_ON)  // just released
        {
            wasReleased = true;
        }
        else
        if (_previous_state == BUTTON_LONG)  // released from long
        {
            wasLongReleased = true;
        }
        
        _state = BUTTON_OFF;       
        _lastWasOff = currentTime;
    }

    _previous_state = _state;      
}

