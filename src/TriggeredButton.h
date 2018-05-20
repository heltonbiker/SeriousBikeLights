#ifndef TRIGGEREDBUTTON_H
#define TRIGGEREDBUTTON_H

#include "Button.h"

class TriggeredButton : public Button
{ 
    public:
        TriggeredButton();
        void run();
    private:
        float _current_value;
        uint8_t _trigger_state;
        static float _factor;
        static float _margin;
        static long _longPressInterval;
};

#endif