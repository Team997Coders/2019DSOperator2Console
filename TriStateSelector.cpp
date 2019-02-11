#include <Arduino.h>
#include "TriStateSelector.h"

// Constructor
TriStateSelector::TriStateSelector(int leftLEDPin,
    int leftJoystickButtonId,
    int rightLEDPin,
    int rightJoystickButtonId) {
  // Initialize member variables
  this->leftLEDPin = leftLEDPin;
  this->leftJoystickButtonId = leftJoystickButtonId;
  this->rightLEDPin = rightLEDPin;
  this->rightJoystickButtonId = rightJoystickButtonId;
}

// Must call in setup to wire up pins and debouncer
void TriStateSelector::begin(Bounce* buttonDebouncer) {
  this->buttonDebouncer = buttonDebouncer;
  
  // Wire up pins
  pinMode(leftLEDPin, OUTPUT);
  pinMode(rightLEDPin, OUTPUT);

  // Set initial default states
  digitalWrite(leftLEDPin, LOW);
  digitalWrite(rightLEDPin, LOW);
}

// Call this function every loop to poll debouncer
void TriStateSelector::update() {
  // Take care of the selector button
  if (buttonDebouncer->update()) {
    // Button is clicked
    if (buttonDebouncer->fallingEdge()) {
      // Left is first reading left to right, so that state goes first when in the 'none' state.
      // If 'None' state...
      if (digitalRead(leftLEDPin) == LOW && digitalRead(rightLEDPin) == LOW) {
        // Left goes first
        digitalWrite(leftLEDPin, HIGH);
      } else {
        // Otherwise toggle leds
        digitalWrite(leftLEDPin, !digitalRead(leftLEDPin));
        digitalWrite(rightLEDPin, !digitalRead(rightLEDPin));
      }
      
      // Simulate pressing Joystick buttons
      if (digitalRead(leftLEDPin)) {
        Joystick.button(leftJoystickButtonId, HIGH);
      } else if (digitalRead(rightLEDPin)) {
        Joystick.button(rightJoystickButtonId, HIGH);
      }
    // Button is released
    } else if (buttonDebouncer->risingEdge()) {
      // Simulate releasing Joystick buttons
      if (digitalRead(leftLEDPin)) {
        Joystick.button(leftJoystickButtonId, LOW);
      } else if (digitalRead(rightLEDPin)) {
        Joystick.button(rightJoystickButtonId, LOW);        
      }      
    }
  }  
}
