#ifndef PWMPIN_H
#define PWMPIN_H

class PwmPin
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
