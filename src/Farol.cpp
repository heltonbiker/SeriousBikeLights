#include <Arduino.h>
#include "PwmPin.h"

typedef enum {
    OFF   = 0,
    ON    = 1,
    BLINK = 2
};

class Farol
{
	PwmPin _pino_farol;

    bool _lightState;

    byte _mode = OFF;

	long _timeReference = 0;

    const int PERIOD = 100;

	public : void configure(byte pino)
	{
		_pino_farol.configure(pino);
	}


    public : void toggle()
    {
        _mode = (_mode + 1) % 3;
    }

    public : void on()
    {
        _mode = ON;
    }

    public : void off()
    {
        _mode = OFF;
    }

    public : void flash()
    {
        _mode = BLINK;
    }

	public : void run()
	{
        switch (_mode)
        {
            case OFF:
                _lightState = false;
                break;
            case ON:
                _lightState = true;
                break;
            case BLINK:
                evaluateBlink();
                break;
        };
        performBlink();
	}


	void evaluateBlink()
	{
        long currentMillis = millis();
        if (currentMillis - _timeReference > PERIOD) {
            _timeReference = currentMillis;
            _lightState = !_lightState;
        }		
	}

    void performBlink()
    {
        if (_lightState)
        {
            _pino_farol.on();
        }
        else
        {
            _pino_farol.off();
        }        
    }
};
