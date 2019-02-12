#ifndef H_MUTUALLYEXCLUSIVESELECTOR
#define H_MUTUALLYEXCLUSIVESELECTOR

#include <Bounce2.h>

typedef bool (* function_pointer_t) ();

class MutuallyExclusiveSelector {
  // Declare class member variables initialied via constructor
  int ledPin;
  int joystickButtonId;
  bool clickedFlag;
  // Must return a bool indicating whether validation succeeded
  function_pointer_t isValid;

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
  void setValidator(function_pointer_t validatorCallback);
  bool canValidate();
};

#endif // H_MUTUALLYEXCLUSIVESELECTOR
