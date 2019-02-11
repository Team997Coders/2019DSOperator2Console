#include "MomentarySelector.h"
#include "MutuallyExclusiveSelector.h"
#include "MutuallyExclusiveSelectorGroup.h"
#include "TriStateSelector.h"

/*
 *  This is firmware for the Spartan Robotics 2019 Deepspace driver 2 operator console. 
 *  
 *  Note that the Teensy 3.5 USB HID firmware supports up to 32 joystick buttons per joystick
 *  HID device, however the FRC driver station only supports up to 16 joystick buttons per USB device.
 *  The Teensy 3.5 has up to 57 (yes fifty-seven!) DIO pins, so it has more than enough to accomodate
 *  the number of physical LEDs and buttons we can imagine.
 *  
 *  Further, note that the Freescale chip recommended max current draw for output pins (the LEDS)
 *  is a skimpy 9mA and absolute max of 25mA. We need to use red LEDs since their voltage requirement
 *  is the lowest (~1.8V) and we need to put the largest current limiting resistor we can to make it
 *  reasonable visible enough. To calculate, use ohms law: V = IR. The Teensy is a 3.3V device. So,
 *  (3.3V - 1.8V) = 0.009A * R. R = 166 ohm resistor so maybe round up to next largest of 180 ohms. On
 *  my demo, I used 330 ohm and they were visible looking straight on but kinda dim from an angle.
 *  Somewhere in between would probably work great.
 *  
 */
 
// Debounce settings
const int debounceTimeInMs = 10;

// Define Teensy pins
const int iAmAliveLEDPin = 13;
const int lowHeightLEDPin = 28;
const int lowHeightButtonPin = 29;
const int activateButtonPin = 30;
const int mediumHeightLEDPin = 31;
const int mediumHeightButtonPin = 32;
const int ballLEDPin = 33;
const int hatchLEDPin = 34;
const int scoringArtifactButtonPin = 35;

// Define joystick ids for joystick HID events sent to host
const int hatchJoystickButtonId = 1;
const int ballJoystickButtonId = 2; 
const int mediumHeightJoystickButtonId = 3;
const int activateJoystickButtonId = 4;
const int lowHeightJoystickButtonId = 5;

elapsedMillis iAmAliveLastBlinked;
int iAmAliveBlinkEveryInMs = 200;

// Scoring artifact selector and dependent class definitions
TriStateSelector scoringArtifactSelector = TriStateSelector(ballLEDPin, 
  ballJoystickButtonId, 
  hatchLEDPin, 
  hatchJoystickButtonId);
Bounce scoringArtifactButtonDebouncer;

// Medium height selector and dependent class definitions
MutuallyExclusiveSelector mediumHeightSelector = MutuallyExclusiveSelector(mediumHeightLEDPin,
  mediumHeightJoystickButtonId);
Bounce mediumHeightPushButtonDebouncer;

// Low height selector and dependent class definitions
MutuallyExclusiveSelector lowHeightSelector = MutuallyExclusiveSelector(lowHeightLEDPin,
  lowHeightJoystickButtonId);
Bounce lowHeightPushButtonDebouncer;

// Define height selector group
MutuallyExclusiveSelector* heightSelectors[] = {&mediumHeightSelector, &lowHeightSelector};
MutuallyExclusiveSelectorGroup heightSelectorGroup;

// Activate selector and dependent class definitions
MomentarySelector activateSelector = MomentarySelector(activateJoystickButtonId);
Bounce activatePushButtonDebouncer;

// This is run once at device startup
void setup() {
  pinMode(iAmAliveLEDPin, OUTPUT);

  // Scoring artifact selector setup
  scoringArtifactButtonDebouncer.attach(scoringArtifactButtonPin, INPUT_PULLUP);
  scoringArtifactButtonDebouncer.interval(debounceTimeInMs);
  scoringArtifactSelector.begin(&scoringArtifactButtonDebouncer);

  // Medium height selector setup
  mediumHeightPushButtonDebouncer.attach(mediumHeightButtonPin, INPUT_PULLUP);
  mediumHeightPushButtonDebouncer.interval(debounceTimeInMs);
  mediumHeightSelector.begin(&mediumHeightPushButtonDebouncer);

  // Low height selector setup
  lowHeightPushButtonDebouncer.attach(lowHeightButtonPin, INPUT_PULLUP);
  lowHeightPushButtonDebouncer.interval(debounceTimeInMs);
  lowHeightSelector.begin(&lowHeightPushButtonDebouncer);

  // Activate selector setup
  activatePushButtonDebouncer.attach(activateButtonPin, INPUT_PULLUP);
  activatePushButtonDebouncer.interval(debounceTimeInMs);
  activateSelector.begin(&activatePushButtonDebouncer);

  // Height selector group setup (for radio-button like control)
  heightSelectorGroup.begin(heightSelectors, 2);
}

// This runs forever
void loop() {
  // Update must be called periodically on all the selectors in order to pump the debouncers.
  scoringArtifactSelector.update();
  mediumHeightSelector.update();
  lowHeightSelector.update();
  activateSelector.update();
  heightSelectorGroup.update();
  if (iAmAliveLastBlinked > iAmAliveBlinkEveryInMs) {
    iAmAliveLastBlinked = 0;
    digitalWrite(iAmAliveLEDPin, !digitalRead(iAmAliveLEDPin));    
  }
}
