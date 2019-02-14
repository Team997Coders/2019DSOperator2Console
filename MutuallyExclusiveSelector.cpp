#include <Arduino.h>
#include "MutuallyExclusiveSelector.h"

// Constructor and call the selector constructor as well
MutuallyExclusiveSelector::MutuallyExclusiveSelector(int ledPin,
    int joystickButtonId): Selector() {
  // Initialize member variables
  this->ledPin = ledPin;
  this->joystickButtonId = joystickButtonId;
}

// Must call in setup to wire up pins and debouncer
void MutuallyExclusiveSelector::begin(Bounce* buttonDebouncer) {
  this->buttonDebouncer = buttonDebouncer;
  
  // Wire up pins
  pinMode(ledPin, OUTPUT);

  // Set initial default states
  digitalWrite(ledPin, LOW);
}

// Call this function every loop to poll debouncer
void MutuallyExclusiveSelector::update() {
  clickedFlag = false;
  // Take care of the selector button
  if (buttonDebouncer->update()) {
    if (buttonDebouncer->fallingEdge()) {
      didFall = true;
      if (canValidate() && isValid()) {
        // set LED to high always if this button is pushed
        digitalWrite(ledPin, HIGH);
        // Simulate pressing Joystick button
        Joystick.button(joystickButtonId, HIGH);
      }
    } else if (buttonDebouncer->risingEdge()) {
      if (canValidate() && isValid()) {
        // Simulate releasing Joystick button
        Joystick.button(joystickButtonId, LOW);
        if (didFall) {
          clickedFlag = true;
        }
      }
    }
  }  
}

// Turn the state off by offing LED
void MutuallyExclusiveSelector::off() {
  digitalWrite(ledPin, LOW);
}
