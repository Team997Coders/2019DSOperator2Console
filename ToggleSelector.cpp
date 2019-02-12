#include <Arduino.h>
#include "ToggleSelector.h"

// Constructor
ToggleSelector::ToggleSelector(int ledPin,
    int joystickButtonId) {
  // Initialize member variables
  this->ledPin = ledPin;
  this->joystickButtonId = joystickButtonId;
  this->clickedFlag = false;
}

// Must call in setup to wire up pins and debouncer
void ToggleSelector::begin(Bounce* buttonDebouncer) {
  this->buttonDebouncer = buttonDebouncer;
  
  // Wire up pins
  pinMode(ledPin, OUTPUT);

  // Set initial default states
  digitalWrite(ledPin, LOW);
}

// Call this function every loop to poll debouncer
void ToggleSelector::update() {
  clickedFlag = false;
  // Take care of the selector button
  if (buttonDebouncer->update()) {
    if (buttonDebouncer->fallingEdge()) {
      // toggle LED
      digitalWrite(ledPin, !digitalRead(ledPin));
      // Simulate pressing Joystick button
      Joystick.button(joystickButtonId, HIGH);
    } else if (buttonDebouncer->risingEdge()) {
      // Simulate releasing Joystick button
      Joystick.button(joystickButtonId, LOW);
      clickedFlag = true;
    }
  }  
}

bool ToggleSelector::clicked() {
  return clickedFlag;
}
