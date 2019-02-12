#ifndef H_TOGGLESELECTOR
#define H_TOGGLESELECTOR

#include <Bounce2.h>
#include "Selector.h"

class ToggleSelector: public Selector {
  // Declare class member variables initialied via constructor
  int ledPin;
  int joystickButtonId;

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  ToggleSelector(int ledPin,
    int joystickButtonId
  );
  void begin(Bounce* buttonDebouncer);
  void update();
};

#endif // H_TOGGLESELECTOR
