#ifndef H_MOMENTARYSELECTORPOV
#define H_MOMENTARYSELECTORPOV

#include <Bounce2.h>

class MomentarySelectorPOV {
  // Declare class member variables initialied via constructor
  int joystickHatAngle; 

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  MomentarySelectorPOV(int joystickHatAngle);
  void update();
  void begin(Bounce* buttonDebouncer);
};

#endif // H_MOMENTARYSELECTORPOV
