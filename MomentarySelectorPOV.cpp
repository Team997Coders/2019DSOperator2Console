#include <Arduino.h>
#include "MomentarySelectorPOV.h"

// Constructor
MomentarySelectorPOV::MomentarySelectorPOV(int joystickHatAngle) {
  // Initialize member variables
  this->joystickHatAngle = joystickHatAngle;
}

// Must call in setup to wire up pins and debouncer
void MomentarySelectorPOV::begin(Bounce* buttonDebouncer) {
  this->buttonDebouncer = buttonDebouncer;
}

// Call this function every loop to poll debouncer
void MomentarySelectorPOV::update() {
  // Take care of the selector button
  if (buttonDebouncer->update()) {
    if (buttonDebouncer->fallingEdge()) {
      // Simulate settings POV to angle
      Joystick.hat(joystickHatAngle);
    } else if (buttonDebouncer->risingEdge()) {
      // Nothing to do
    }
  }  
}
