#ifndef H_MUTUALLYEXCLUSIVESELECTORGROUP
#define H_MUTUALLYEXCLUSIVESELECTORGROUP

#include <Bounce2.h>

class MutuallyExclusiveSelectorGroup {
  // Declare class member variables initialied via constructor

  // Declare working member variables
  MutuallyExclusiveSelector** selectors;
  size_t selectorsCount;
  
  public:
  MutuallyExclusiveSelectorGroup();
  void allOthersOff(MutuallyExclusiveSelector* selector);
  void begin(MutuallyExclusiveSelector** selectors, size_t selectorsCount);
  void update();
};

#endif // H_MUTUALLYEXCLUSIVESELECTORGROUP
