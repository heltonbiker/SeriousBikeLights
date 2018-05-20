#include "TriggeredButton.h"

#include "PiscaPisca.cpp"
#include "PoliciaFreio.cpp"

#include "Farol.cpp"

class Pinos
{
  public:
    static const byte LeftSignButton = 1;
    static const byte SpeedSensor = 2;
    static const byte HeadLight = 3;
    static const byte RightSignButton = 4;
    static const byte LeftSign = 5;
    static const byte RightSign = 6;
    static const byte Siren = 7;
    static const byte Buzzer = 8;
    static const byte LeftRed = 9;
    static const byte Blue = 10;
    static const byte RightRed = 11;
    static const byte ModeButton = 12;
    static const byte StatusLED = 13;

    static const byte LightSensor = A1;
    static const byte LeftActionButton = A2;
    static const byte RightActionButton = A3;
};

typedef enum {
  FAROL_OFF = 0,
  LANTERN = 1,
  LIGHTS = 2,
  POLICE = 3
};

byte _mode = 0;

PiscaPisca pisca;

PoliciaFreio policiafreio;

TriggeredButton LeftSignButton;
TriggeredButton RightSignButton;
TriggeredButton LeftActionButton;
TriggeredButton RightActionButton;

Farol farol;

void setup() {

  LeftSignButton.configure(Pinos::LeftSignButton);
  RightSignButton.configure(Pinos::RightSignButton);
  LeftActionButton.configure(Pinos::LeftActionButton);
  RightActionButton.configure(Pinos::RightActionButton);

  policiafreio.configure(Pinos::LeftRed, Pinos::Blue, Pinos::RightRed);
  farol.configure(Pinos::HeadLight);
  pisca.configure(Pinos::LeftSign, Pinos::RightSign, Pinos::Buzzer);


  //Serial.begin(9600);

  //policiafreio.policeOn();
}



void loop() 
{
  input();
  process();
  output();
}




void input()
{
  LeftSignButton.run();
  RightSignButton.run();
  LeftActionButton.run();
  RightActionButton.run();
}

void process()
{
  processaFarolPoliciaFreio();
  processaPisca();	
}

void output()
{
  pisca.run();
  farol.run();
  policiafreio.run();
}




void processaFarolPoliciaFreio() {

  if (LeftSignButton.isPressed)
    policiafreio.brake();
  else {
    processaFarolPolicia();
  }
}

void processaPisca() {
  if (RightSignButton.wasPressed) {
    if (RightActionButton.isPressed) {
      pisca.toggleBoth();
    }
    else {
      pisca.toggleLeft();
    }
  }

  if (RightActionButton.wasPressed) {
    if (RightSignButton.isPressed) {
      pisca.toggleBoth();
    }
    else {
      pisca.toggleRight();
    }
  }  
}

void processaFarolPolicia() {
  if (LeftActionButton.wasLongPressed) {
    switch (_mode) {
      case LIGHTS:
        policeMode();
        break;
    }
  }
  else if (LeftActionButton.wasReleased) {
    switch (_mode) {
      case FAROL_OFF:
        lightsMode();
        break;
      case LIGHTS:
        offMode();
        break;
      case POLICE:
        lightsMode();
        break;        
    }
  }
}

void policeMode() {
  _mode = POLICE;
  farol.flash();
  policiafreio.policeOn();
}

void lightsMode() {
  _mode = LIGHTS;
  farol.on();
  policiafreio.tailOn();
}

void offMode() {
  _mode = FAROL_OFF;
  farol.off();
  policiafreio.off();  
}