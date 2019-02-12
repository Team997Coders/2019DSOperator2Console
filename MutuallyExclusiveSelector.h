#ifndef H_MUTUALLYEXCLUSIVESELECTOR
#define H_MUTUALLYEXCLUSIVESELECTOR

#include <Bounce2.h>
#include "Selector.h"

class MutuallyExclusiveSelector: public Selector {
  // Declare class member variables initialied via constructor
  int ledPin;
  int joystickButtonId;
  
  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  MutuallyExclusiveSelector(int ledPin,
    int joystickButtonId
  );
  void begin(Bounce* buttonDebouncer);
  void off();
  void update();
};

#endif // H_MUTUALLYEXCLUSIVESELECTOR
