#include <Arduino.h>

class BlinkBeeper
{
	byte _pin;

	const int
        inFreq = 600,
        outFreq = 500,
        duration = 15;


	public :
		void configure(byte pin)
		{
			_pin = pin;
			pinMode(_pin, OUTPUT);
		}


		void beepIn() {
			tone(_pin, inFreq, duration);
		}

		void beepOut() {
			tone(_pin, outFreq, duration);
		}
};