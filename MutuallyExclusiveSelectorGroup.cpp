#include <Arduino.h>
#include "MutuallyExclusiveSelector.h"
#include "MutuallyExclusiveSelectorGroup.h"

// Constructor
MutuallyExclusiveSelectorGroup::MutuallyExclusiveSelectorGroup() {
}

// Must call in setup to initialize selectors that will be treated as a group
void MutuallyExclusiveSelectorGroup::begin(MutuallyExclusiveSelector** selectors, size_t selectorsCount) {
  this->selectors = selectors;
  this->selectorsCount = selectorsCount;
}

// Call turn all other selectors off
void MutuallyExclusiveSelectorGroup::allOthersOff(MutuallyExclusiveSelector* selector) {
  // Loop over all selectors turning off all but the one passed in.
  for( uint i = 0; i < selectorsCount; i++) {
    if (selectors[i] != selector) {
      selectors[i]->off();
    }
  }
}

// Scan the selectors to see if any clicked and if so, turn all others off
void MutuallyExclusiveSelectorGroup::update() {
  for( uint i = 0; i < selectorsCount; i++) {
    if (selectors[i]->clicked()) {
      allOthersOff(selectors[i]);
    }
  }  
}

// Call turn all other selectors off
void MutuallyExclusiveSelectorGroup::allOff() {
  // Loop over all selectors turning off all but the one passed in.
  for( uint i = 0; i < selectorsCount; i++) {
    selectors[i]->off();
  }
}

