#ifndef H_TOGGLESELECTOR
#define H_TOGGLESELECTOR

#include <Bounce2.h>

class ToggleSelector {
  // Declare class member variables initialied via constructor
  int ledPin;
  int joystickButtonId;
  bool clickedFlag;

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  ToggleSelector(int ledPin,
    int joystickButtonId
  );
  void update();
  void begin(Bounce* buttonDebouncer);
  bool clicked();
};

#endif // H_TOGGLESELECTOR
