#ifndef H_MOMENTARYSELECTORPOV
#define H_MOMENTARYSELECTORPOV

#include <Bounce2.h>
#include "Selector.h"

class MomentarySelectorPOV: public Selector {
  // Declare class member variables initialied via constructor
  int joystickHatAngle; 

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  MomentarySelectorPOV(int joystickHatAngle);
  void begin(Bounce* buttonDebouncer);
  void update();
};

#endif // H_MOMENTARYSELECTORPOV
