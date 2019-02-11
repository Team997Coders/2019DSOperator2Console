#include <Arduino.h>
#include "MomentarySelector.h"

// Constructor
MomentarySelector::MomentarySelector(int joystickButtonId) {
  // Initialize member variables
  this->joystickButtonId = joystickButtonId;
}

// Must call in setup to wire up pins and debouncer
void MomentarySelector::begin(Bounce* buttonDebouncer) {
  this->buttonDebouncer = buttonDebouncer;
}

// Call this function every loop to poll debouncer
void MomentarySelector::update() {
  // Take care of the selector button
  if (buttonDebouncer->update()) {
    if (buttonDebouncer->fallingEdge()) {
      // Simulate pressing Joystick button
      Joystick.button(joystickButtonId, HIGH);
    } else if (buttonDebouncer->risingEdge()) {
      // Simulate releasing Joystick button
      Joystick.button(joystickButtonId, LOW);
    }
  }  
}