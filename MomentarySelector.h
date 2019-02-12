#ifndef H_MOMENTARYSELECTOR
#define H_MOMENTARYSELECTOR

#include <Bounce2.h>
#include "Selector.h"

class MomentarySelector: public Selector {
  // Declare class member variables initialied via constructor
  int joystickButtonId; 

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  MomentarySelector(int joystickButtonId);
  void begin(Bounce* buttonDebouncer);
  void update();
};

#endif // H_MOMENTARYSELECTOR
