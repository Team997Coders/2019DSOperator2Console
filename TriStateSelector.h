#ifndef H_TRISTATESELECTOR
#define H_TRISTATESELECTOR

#include <Bounce2.h>
#include "Selector.h"

class TriStateSelector: public Selector {
  // Declare class member variables initialied via constructor
  int leftLEDPin;
  int leftJoystickButtonId; 
  int rightLEDPin;
  int rightJoystickButtonId;
  int debounceTimeInMs;

  // Declare working member variables
  Bounce* buttonDebouncer;
  
  public:
  TriStateSelector(int leftLEDPin,
    int leftJoystickButtonId,
    int rightLEDPin,
    int rightJoystickButtonId
   );
   void update();
   void begin(Bounce* buttonDebouncer);
};

#endif // H_TRISTATESELECTOR
