#include <Arduino.h>

class Botao
{
    byte _pino;

    const int DEBOUNCE_DELAY = 30;

    byte lastState = HIGH;

    public :
    byte
        buttonState;
    bool
        wasPressed = false,
        wasReleased = false,
        isPressed = false;

    int lastDebounceTime;

    public : void configure(byte pino)
    {
        _pino = pino;
        pinMode(pino, INPUT_PULLUP);
    }

    public : void run()
    {
        debounce();
    }

    public : void debounce()
    {        
        byte reading = digitalRead(_pino);

        isPressed = (reading == LOW);
        wasPressed = false;
        wasReleased = false;

        if (reading != lastState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > DEBOUNCE_DELAY) {
            if (reading != buttonState) {
                buttonState = reading;

                if (buttonState == LOW) {
                    wasPressed = true;
                }
                else
                {
                    wasReleased = true;
                }
            }
        }

        lastState = reading;
    }    
};