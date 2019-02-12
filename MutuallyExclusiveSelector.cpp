#include <Arduino.h>
#include "MutuallyExclusiveSelector.h"

// Constructor
MutuallyExclusiveSelector::MutuallyExclusiveSelector(int ledPin,
    int joystickButtonId) {
  // Initialize member variables
  this->ledPin = ledPin;
  this->joystickButtonId = joystickButtonId;
  this->clickedFlag = false;
  this->isValid = NULL;
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
        clickedFlag = true;
      }
    }
  }  
}

void MutuallyExclusiveSelector::off() {
  digitalWrite(ledPin, LOW);
}

bool MutuallyExclusiveSelector::clicked() {
  return clickedFlag;
}

void MutuallyExclusiveSelector::setValidator(function_pointer_t validatorCallback) {
  isValid = validatorCallback;
}

bool MutuallyExclusiveSelector::canValidate() {
  return !(isValid == NULL);
}

