#include "TriggeredButton.h"

#include "TurnSignals.cpp"
#include "PoliceBrakeLight.cpp"

#include "HeadLight.cpp"

#include "Pinout.cpp"


typedef enum {
  LIGHTS_OFF = 0,
  LANTERN = 1,
  LIGHTS = 2,
  POLICE = 3
};

byte _mode = 0;

TurnSignals turnSignals;

PoliceBrakeLight policeBrakeLight;

TriggeredButton LeftSignalButton;
TriggeredButton RightSignalButton;
TriggeredButton ModeButton;
TriggeredButton BrakeSensor;
TriggeredButton HornButton;

HeadLight headLight;


// SpeedSensor (2)
// SDA/SCL (A4, A5)
// LightSensor (A1)
// Horn (A3)
// Siren (7)
// StatusLedPin (13)


void setup() {

  LeftSignalButton.configure(Pinout::LeftTurnButtonPin);
  RightSignalButton.configure(Pinout::RightTurnButtonPin);
  ModeButton.configure(Pinout::ModeButtonPin);
  BrakeSensor.configure(Pinout::BrakeSensorPin);
  HornButton.configure(Pinout::HornButtonPin);

  policeBrakeLight.configure(Pinout::TailRedLeftPin, Pinout::TailBluePin, Pinout::TailRedRightPin);
  headLight.configure(Pinout::HeadLightPin);
  turnSignals.configure(Pinout::LeftSignalPin, Pinout::RightSignalPin, Pinout::BuzzerPin);
}





void loop() 
{
  input();
  process();
  output();
}




void input()
{
  LeftSignalButton.run();
  RightSignalButton.run();
  ModeButton.run();
  BrakeSensor.run();
  HornButton.run();
}

void process()
{
  processHeadLightPoliceBrake();
  processTurnSignals();	
}

void output()
{
  turnSignals.run();
  headLight.run();
  policeBrakeLight.run();
}


void processTurnSignals() {
  if (RightSignalButton.wasPressed) {
    if (LeftSignalButton.isPressed) {
      turnSignals.toggleBoth();
    }
    else {
      turnSignals.toggleLeft();
    }
  }

  if (LeftSignalButton.wasPressed) {
    if (RightSignalButton.isPressed) {
      turnSignals.toggleBoth();
    }
    else {
      turnSignals.toggleRight();
    }
  }  
}


void processHeadLightPoliceBrake() {
  if (BrakeSensor.isPressed)
    policeBrakeLight.brake();
  else {
    processHeadlightPolice();
  }
}

void processHeadlightPolice() {
  if (ModeButton.wasLongPressed) {
    switch (_mode) {
      case LIGHTS:
        policeMode();
        break;
    }
  }
  else if (ModeButton.wasReleased) {
    switch (_mode) {
      case POLICE:
      case LIGHTS_OFF:
        lightsMode();
        break;        
      case LIGHTS:
        offMode();
        break;
    }
  }
}

void policeMode() {
  _mode = POLICE;
  headLight.flash();
  policeBrakeLight.policeOn();
}

void lightsMode() {
  _mode = LIGHTS;
  headLight.on();
  policeBrakeLight.tailOn();
}

void offMode() {
  _mode = LIGHTS_OFF;
  headLight.off();
  policeBrakeLight.off();  
}
