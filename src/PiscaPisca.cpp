#include <Arduino.h>
#include "PwmPin.h"
#include "Beeper.cpp"

typedef enum {
    NONE        = 0,
    RIGHT_LIGHT = 1,
    LEFT_LIGHT  = 2,
    BOTH        = 3
};

class PiscaPisca
{
    PwmPin _left;
    PwmPin _right;

    Beeper _beeper;

    long _timeReference = 0;

    const int PERIOD = 350;

    boolean
        _running = false,
        _lightState = false;

    byte _mode = NONE;

    public : void configure(byte leftPin, byte rightPin, byte buzzerPin)
    {
        _left.configure(leftPin);
        _right.configure(rightPin);
        _beeper.configure(buzzerPin);
    }

    public : void run() 
    {        
        evaluateBlink();
    }


    public : void toggleLeft()
    {
        checkModeChange(LEFT_LIGHT);
    }

    public : void toggleRight()
    {
        checkModeChange(RIGHT_LIGHT);
    }

    public : void toggleBoth()
    {
        checkModeChange(BOTH);
    }


    void checkModeChange(byte lightSide)
    {
        if (lightSide == BOTH)
        {
            if (_mode == BOTH)
                _mode = NONE;
            else
                _mode = BOTH;
        }
        else
        {    
            if (_mode == lightSide)
                _mode = NONE;
            else
                _mode = lightSide;
        }
   
              
        if (_mode > 0)
        {
            _running = true;
        }
        else
        {
            lightsOff();
            _running = false;
            _lightState = false;      
        }
    }



    void evaluateBlink() 
    {
        if (!_running)
        {
            return;
        }
        else
        {
            long currentMillis = millis();
            if (currentMillis - _timeReference > PERIOD) {
                _timeReference = currentMillis;
                _lightState = !_lightState;
                performBlink();
            }
        }
    }

    void performBlink()
    {
        if (_lightState)
        {
            _beeper.beepIn();
            lightsOn();
        }
        else
        {
            _beeper.beepOut();
            lightsOff();
        }        
    }

    void lightsOn()
    {
        if (isLightSet(LEFT_LIGHT))
        {
            _left.on();
        }
        if (isLightSet(RIGHT_LIGHT))
        {
            _right.on();
        }        
    }

    boolean isLightSet(int lightSide)
    {
        return (_mode & lightSide) == lightSide;
    }

    void lightsOff()
    {
        _left.off();
        _right.off();
    }



};