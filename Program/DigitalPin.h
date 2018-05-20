#ifndef PIN_H
#define PIN_H

class DigitalPin
{
    public:
        void configure(byte pin);
        void on();
        void off();
        void set(byte val);        
    private:
        byte _pin;
        byte _state;
};

#endif
