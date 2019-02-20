#include "MomentarySelector.h"
#include "MomentarySelectorPOV.h"
#include "MutuallyExclusiveSelector.h"
#include "MutuallyExclusiveSelectorGroup.h"
#include "ToggleSelector.h"
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

// Pins marked with done were re-mapped when button board was assembled

// Define Teensy pins
const int iAmAliveLEDPin = 13;
const int AButtonPin = 25;                  // done
const int BButtonPin = 26;                  // done
const int XButtonPin = 27;                  // done
const int leftButtonPin = 30;               // done
const int centerButtonPin = 28;             // done
const int rightButtonPin = 29;              // done
const int intakeLEDPin = 14;                // done - 3.3v blue led @3mA on button
const int intakeButtonPin = 31;             // done
const int cancelButtonPin = 32;             // done
const int highHeightLEDPin = 23;            // done
const int highHeightButtonPin = 39;         // done
const int scoringDestinationButtonPin = 35; // done
const int cargoShipLEDPin = 17;             // done
const int rocketLEDPin = 15;                // done
const int lowHeightLEDPin = 18;             // done
const int lowHeightButtonPin = 34;          // done
const int activateButtonPin = 33;           // done
const int mediumHeightLEDPin = 20;          // done
const int mediumHeightButtonPin = 37;       // done
const int ballLEDPin = 16;                  // done
const int hatchLEDPin = 22;                 // done
const int scoringArtifactButtonPin = 36;    // done
const int scoringDirectionButtonPin = 38;   // done
const int frontLEDPin = 21;                 // done
const int backLEDPin = 19;                  // done

// Define joystick ids for joystick HID events sent to host
const int hatchJoystickButtonId = 1;
const int ballJoystickButtonId = 2; 
const int mediumHeightJoystickButtonId = 3;
const int activateJoystickButtonId = 4;
const int lowHeightJoystickButtonId = 5;
const int frontJoystickButtonId = 6;
const int backJoystickButtonId = 7;
const int rocketJoystickButtonId = 8;
const int cargoShipJoystickButtonId = 9;
const int highHeightJoystickButtonId = 10;
const int cancelJoystickButtonId = 11;
const int intakeJoystickButtonId = 12;
const int AJoystickButtonId = 13;
const int BJoystickButtonId = 14;
const int XJoystickButtonId = 15;
const int leftJoystickHatAngle = 315;
const int centerJoystickHatAngle = 0;
const int rightJoystickHatAngle = 45;

// Make onboard LED blink definitions
elapsedMillis iAmAliveLastBlinked;
uint iAmAliveBlinkEveryInMs = 200;

// Scoring direction selector and dependent class definitions
TriStateSelector scoringDirectionSelector = TriStateSelector(frontLEDPin, 
  frontJoystickButtonId, 
  backLEDPin, 
  backJoystickButtonId);
Bounce scoringDirectionButtonDebouncer;

// Scoring artifact selector and dependent class definitions
TriStateSelector scoringArtifactSelector = TriStateSelector(ballLEDPin, 
  ballJoystickButtonId, 
  hatchLEDPin, 
  hatchJoystickButtonId);
Bounce scoringArtifactButtonDebouncer;

// Scoring destination selector and dependent class definitions
TriStateSelector scoringDestinationSelector = TriStateSelector(rocketLEDPin, 
  rocketJoystickButtonId, 
  cargoShipLEDPin, 
  cargoShipJoystickButtonId);
Bounce scoringDestinationButtonDebouncer;

// Activate selector and dependent class definitions
MomentarySelector activateSelector = MomentarySelector(activateJoystickButtonId);
Bounce activatePushButtonDebouncer;

// High height selector and dependent class definitions
MutuallyExclusiveSelector highHeightSelector = MutuallyExclusiveSelector(highHeightLEDPin,
  highHeightJoystickButtonId);
Bounce highHeightPushButtonDebouncer;

// Medium height selector and dependent class definitions
MutuallyExclusiveSelector mediumHeightSelector = MutuallyExclusiveSelector(mediumHeightLEDPin,
  mediumHeightJoystickButtonId);
Bounce mediumHeightPushButtonDebouncer;

// Low height selector and dependent class definitions
MutuallyExclusiveSelector lowHeightSelector = MutuallyExclusiveSelector(lowHeightLEDPin,
  lowHeightJoystickButtonId);
Bounce lowHeightPushButtonDebouncer;

// Define height selector group
MutuallyExclusiveSelector* heightSelectors[] = {&highHeightSelector, &mediumHeightSelector, &lowHeightSelector};
MutuallyExclusiveSelectorGroup heightSelectorGroup;

// Cancel selector and dependent class definitions
MomentarySelector cancelSelector = MomentarySelector(cancelJoystickButtonId);
Bounce cancelPushButtonDebouncer;

// Intake selector and dependent class definitions
ToggleSelector intakeSelector = ToggleSelector(intakeLEDPin, intakeJoystickButtonId);
Bounce intakePushButtonDebouncer;

// A selector and dependent class definitions
MomentarySelector ASelector = MomentarySelector(AJoystickButtonId);
Bounce APushButtonDebouncer;

// B selector and dependent class definitions
MomentarySelector BSelector = MomentarySelector(BJoystickButtonId);
Bounce BPushButtonDebouncer;

// X selector and dependent class definitions
MomentarySelector XSelector = MomentarySelector(XJoystickButtonId);
Bounce XPushButtonDebouncer;

// Left selector and dependent class definitions
MomentarySelectorPOV leftSelector = MomentarySelectorPOV(leftJoystickHatAngle);
Bounce leftPushButtonDebouncer;

// Center selector and dependent class definitions
MomentarySelectorPOV centerSelector = MomentarySelectorPOV(centerJoystickHatAngle);
Bounce centerPushButtonDebouncer;

// Right selector and dependent class definitions
MomentarySelectorPOV rightSelector = MomentarySelectorPOV(rightJoystickHatAngle);
Bounce rightPushButtonDebouncer;

// Returns true if height selectors can be set
// Height settings are not applicable when scoring
// on the cargo ship.
bool heightValidator() {
  if (digitalRead(cargoShipLEDPin)) {
    return false;
  } else {
    return true;
  }
}

// This is run once at device startup
void setup() {
  pinMode(iAmAliveLEDPin, OUTPUT);

  // Scoring direction selector setup
  scoringDirectionButtonDebouncer.attach(scoringDirectionButtonPin, INPUT_PULLUP);
  scoringDirectionButtonDebouncer.interval(debounceTimeInMs);
  scoringDirectionSelector.begin(&scoringDirectionButtonDebouncer);
  
  // Scoring artifact selector setup
  scoringArtifactButtonDebouncer.attach(scoringArtifactButtonPin, INPUT_PULLUP);
  scoringArtifactButtonDebouncer.interval(debounceTimeInMs);
  scoringArtifactSelector.begin(&scoringArtifactButtonDebouncer);

  // Scoring destination selector setup
  scoringDestinationButtonDebouncer.attach(scoringDestinationButtonPin, INPUT_PULLUP);
  scoringDestinationButtonDebouncer.interval(debounceTimeInMs);
  scoringDestinationSelector.begin(&scoringDestinationButtonDebouncer);

  // Activate selector setup
  activatePushButtonDebouncer.attach(activateButtonPin, INPUT_PULLUP);
  activatePushButtonDebouncer.interval(debounceTimeInMs);
  activateSelector.begin(&activatePushButtonDebouncer);

  // High height selector setup
  highHeightPushButtonDebouncer.attach(highHeightButtonPin, INPUT_PULLUP);
  highHeightPushButtonDebouncer.interval(debounceTimeInMs);
  highHeightSelector.begin(&highHeightPushButtonDebouncer);
  highHeightSelector.setValidator(heightValidator);

  // Medium height selector setup
  mediumHeightPushButtonDebouncer.attach(mediumHeightButtonPin, INPUT_PULLUP);
  mediumHeightPushButtonDebouncer.interval(debounceTimeInMs);
  mediumHeightSelector.begin(&mediumHeightPushButtonDebouncer);
  mediumHeightSelector.setValidator(heightValidator);

  // Low height selector setup
  lowHeightPushButtonDebouncer.attach(lowHeightButtonPin, INPUT_PULLUP);
  lowHeightPushButtonDebouncer.interval(debounceTimeInMs);
  lowHeightSelector.begin(&lowHeightPushButtonDebouncer);
  lowHeightSelector.setValidator(heightValidator);

  // Height selector group setup (for radio-button like control)
  heightSelectorGroup.begin(heightSelectors, 3);

  // Cancel selector setup
  cancelPushButtonDebouncer.attach(cancelButtonPin, INPUT_PULLUP);
  cancelPushButtonDebouncer.interval(debounceTimeInMs);
  cancelSelector.begin(&cancelPushButtonDebouncer);

  // Intake selector setup
  intakePushButtonDebouncer.attach(intakeButtonPin, INPUT_PULLUP);
  intakePushButtonDebouncer.interval(debounceTimeInMs);
  intakeSelector.begin(&intakePushButtonDebouncer);

  // A selector setup
  APushButtonDebouncer.attach(AButtonPin, INPUT_PULLUP);
  APushButtonDebouncer.interval(debounceTimeInMs);
  ASelector.begin(&APushButtonDebouncer);

  // B selector setup
  BPushButtonDebouncer.attach(BButtonPin, INPUT_PULLUP);
  BPushButtonDebouncer.interval(debounceTimeInMs);
  BSelector.begin(&BPushButtonDebouncer);

  // X selector setup
  XPushButtonDebouncer.attach(XButtonPin, INPUT_PULLUP);
  XPushButtonDebouncer.interval(debounceTimeInMs);
  XSelector.begin(&XPushButtonDebouncer);

  // Left selector setup
  leftPushButtonDebouncer.attach(leftButtonPin, INPUT_PULLUP);
  leftPushButtonDebouncer.interval(debounceTimeInMs);
  leftSelector.begin(&leftPushButtonDebouncer);

  // Center selector setup
  centerPushButtonDebouncer.attach(centerButtonPin, INPUT_PULLUP);
  centerPushButtonDebouncer.interval(debounceTimeInMs);
  centerSelector.begin(&centerPushButtonDebouncer);

  // Right selector setup
  rightPushButtonDebouncer.attach(rightButtonPin, INPUT_PULLUP);
  rightPushButtonDebouncer.interval(debounceTimeInMs);
  rightSelector.begin(&rightPushButtonDebouncer);

  // Back is enabled at first power on
  digitalWrite(backLEDPin, HIGH);
}

// This runs forever
void loop() {
  // Update must be called periodically on all the selectors in order to pump the debouncers.
  scoringDirectionSelector.update();
  scoringArtifactSelector.update();
  scoringDestinationSelector.update();
  // The height updaters must run AFTER the destination updater
  highHeightSelector.update();
  mediumHeightSelector.update();
  lowHeightSelector.update();
  heightSelectorGroup.update();
  intakeSelector.update();
  activateSelector.update();
  cancelSelector.update();
  ASelector.update();
  BSelector.update();
  XSelector.update();
  leftSelector.update();
  centerSelector.update();
  rightSelector.update();

  // We can get to this condition from direction or artifact selections
  // so if we get here, flip the display to cargo ship. Back/Hatch/Rocket is not valid.
  // DeepspaceOperator2Console.java will set the state on its side to deal with this condition
  // to keep state in sync.
  if (scoringDirectionSelector.clicked() || scoringDestinationSelector.clicked() || scoringArtifactSelector.clicked()) {
    if (digitalRead(backLEDPin) && digitalRead(hatchLEDPin) && digitalRead(rocketLEDPin)) {
      digitalWrite(rocketLEDPin, LOW);
      digitalWrite(cargoShipLEDPin, HIGH);
      heightSelectorGroup.allOff();
    }
  }

  // Scoring on cargo ship has no height setting, so clear the height selector group
  // if the cargo ship led is lit. This needs to be AFTER the back/hatch/rocket check.
  if (scoringDestinationSelector.clicked() && digitalRead(cargoShipLEDPin)) {
    heightSelectorGroup.allOff();
  }
  
  // Clear LEDs when cancel clicked
  if (cancelSelector.clicked()) {
    digitalWrite(frontLEDPin, LOW);
    digitalWrite(backLEDPin, LOW);
    digitalWrite(ballLEDPin, LOW);
    digitalWrite(hatchLEDPin, LOW);
    digitalWrite(rocketLEDPin, LOW);
    digitalWrite(cargoShipLEDPin, LOW);
    digitalWrite(highHeightLEDPin, LOW);
    digitalWrite(mediumHeightLEDPin, LOW);
    digitalWrite(lowHeightLEDPin, LOW);
    digitalWrite(intakeLEDPin, LOW);
  }

  // Give observer hope that we are alive and kicking...onboard Teensy LED will flash
  if (iAmAliveLastBlinked > iAmAliveBlinkEveryInMs) {
    iAmAliveLastBlinked = 0;
    toggleIAmAlive();
  }
}

void toggleIAmAlive() {
  digitalWrite(iAmAliveLEDPin, !digitalRead(iAmAliveLEDPin));
}
