#ifndef H_SELECTOR
#define H_SELECTOR

// Declare a function pointer type must return a bool
typedef bool (* function_pointer_t) ();

bool alwaysValid();

class Selector {
  private:
  
  // Declare class member variables initialied via constructor
  protected:
  bool clickedFlag;
  bool didFall;

  // Callback function returing bool indicating it is ok to click
  // Set with SetValidator
  function_pointer_t isValid;
  bool canValidate();
    
  public:
  Selector();
  bool clicked();
  void setValidator(function_pointer_t validatorCallback);
  // It always seemed silly to me that you have to define an implementation to
  // a virtual function in C++. Why? If not, you get a 'undefined reference to vtable for class'
  // compile error. And the error is flagged in the constructor. How the hell are you supposed
  // to know what function does not have an implementation based on that message?
  // Note the two squiggle brackets below...
  virtual void update() {};
};

#endif // H_SELECTOR
