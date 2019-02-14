#include <Arduino.h>
#include "Selector.h"

bool alwaysValid() {return true;}

// Constructor
Selector::Selector() {
  // Initialize member variables
  this->clickedFlag = false;
  this->didFall = false;
  this->isValid = alwaysValid;
}

// Indicates whether validator callback function has been set and is thus callable.
bool Selector::canValidate() {
  return !(isValid == NULL);
}

// Indicates if selector was successfully clicked during latest
// update cycle. Note that the clicking flag should get reset
// after every cycle.
bool Selector::clicked() {
  return clickedFlag;
}

// Sets the callback function to run to validate whether clicking is allowed.
void Selector::setValidator(function_pointer_t validatorCallback) {
  isValid = validatorCallback;
}
