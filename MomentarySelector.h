#ifndef H_MOMENTARYSELECTOR
#define H_MOMENTARYSELECTOR

#include <Bounce2.h>

class MomentarySelector {
  // Declare class member variables initialied via constructor
  int joystickButtonId; 

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  MomentarySelector(int joystickButtonId);
  void update();
  void begin(Bounce* buttonDebouncer);
};

#endif // H_MOMENTARYSELECTOR
