#ifndef H_MUTUALLYEXCLUSIVESELECTOR
#define H_MUTUALLYEXCLUSIVESELECTOR

#include <Bounce2.h>

class MutuallyExclusiveSelector {
  // Declare class member variables initialied via constructor
  int ledPin;
  int joystickButtonId;
  bool clickedFlag;

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  MutuallyExclusiveSelector(int ledPin,
    int joystickButtonId
  );
  void update();
  void begin(Bounce* buttonDebouncer);
  void off();
  bool clicked();
};

#endif // H_MUTUALLYEXCLUSIVESELECTOR
