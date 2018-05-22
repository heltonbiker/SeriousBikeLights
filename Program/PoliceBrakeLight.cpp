#include <Arduino.h>
#include "PwmPin.h"


class PoliceBrakeLight
{
    PwmPin _leftRedPin;
    PwmPin _bluePin;
    PwmPin _rightRedPin;

    uint8_t _brake_state = LOW;
    uint8_t _police_state = LOW;
    uint8_t _tail_state = LOW;

    public : void configure(byte leftRedPin, byte bluePin, byte rightRedPin)
    {
        _leftRedPin.configure(leftRedPin);
        _bluePin.configure(bluePin);
        _rightRedPin.configure(rightRedPin);
    }

    public : void brake()
    {
        _brake_state = HIGH;
    }

    public : void policeOn()
    {
        _police_state = HIGH;
    }

    public : void toggleTail()
    {
        _tail_state = !_tail_state;
    }

    public : void tailOn()
    {
        _tail_state = HIGH;
        _police_state = LOW;
    }

    public : void off()
    {
        _tail_state = LOW;
        _police_state = LOW;
    }    

    ///////////////////////////////


    public : void run()
    {

        if (_brake_state) 
        {
            runBrake();
        }
        else if (_police_state)
        {
            runPolice();
        }
        else if (_tail_state)
        {
            runTail();
        }
        else
        {
            allOff();
        }
    }

    void runBrake()
    {
        _leftRedPin.on();
        _bluePin.off();   
        _brake_state = LOW;
    }

    void runPolice()
    {
        static unsigned long unitInterval = 50;
        static unsigned long previousMillis = 0;
        static unsigned long currentInterval = unitInterval;

        static int level = 255;

        static uint8_t blinksPerColor = 5;
        static uint8_t remainingBlinks = blinksPerColor;
        static uint8_t pauseFactor = 3;

        static uint8_t color = 0;
        static uint8_t phase = 0;
         
        if (millis() - previousMillis > currentInterval) {

            previousMillis = millis();
            
            if (phase == 0)
            {
                if (color == 0)
                {
                    _leftRedPin.set(level);
                }
                else
                {
                    _bluePin.set(level);
                }
            }
            else 
            {
                _leftRedPin.off();
                _bluePin.off();
                remainingBlinks--;                    
            }

            phase = 1 - phase; 

            if (remainingBlinks == 0)
            {
                remainingBlinks = blinksPerColor;
                color = 1 - color;
                currentInterval = pauseFactor * unitInterval;
            }
            else
            {
                currentInterval = unitInterval;
            }
        }                      
    }    

    void runTail()
    {
        _leftRedPin.set(40);
        _bluePin.off();
    }

    void allOff()
    {
        _bluePin.off();
        _leftRedPin.off();
    }
};
