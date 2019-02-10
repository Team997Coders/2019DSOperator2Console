#include <Bounce.h>

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

// Ball/Hatch pin and helper class definitions
const int ballHatchButtonPin = 35;
const int ballLEDPin = 33;
const int ballJoystickButton = 2; 
const int hatchLEDPin = 34;
const int hatchJoystickButton = 1;
Bounce ballHatchPushButton = Bounce(ballHatchButtonPin, debounceTimeInMs);

// Medium height pin and helper class definitions
const int mediumHeightButtonPin = 32;
const int mediumHeightLEDPin = 31;
const int mediumHeightJoystickButton = 3;
Bounce mediumHeightPushButton = Bounce(mediumHeightButtonPin, debounceTimeInMs);

// Active pin and helper class definitions
const int activateButtonPin = 30;
const int activateJoystickButton = 4;
Bounce activatePushButton = Bounce(activateButtonPin, debounceTimeInMs);

// This is run once at device startup
void setup() {
  // Setup pins for ball/hatch button control
  // Note that we start out the hatch pin HIGH just
  // for demonstration purposes, but this control is 
  // actually a tri-state control - Ball, Hatch, or nothing,
  // so this should probably change to make none of these LEDs
  // on at startup.
  pinMode(ballLEDPin, OUTPUT);
  pinMode(hatchLEDPin, OUTPUT);
  pinMode(ballHatchButtonPin, INPUT_PULLUP);      // Note that this makes the UNPRESSED state HIGH.
  digitalWrite(hatchLEDPin, LOW);
  digitalWrite(ballLEDPin, LOW);

  // Setup pins for medium height control
  pinMode(mediumHeightLEDPin, OUTPUT);
  pinMode(mediumHeightButtonPin, INPUT_PULLUP);   // Note that this makes the UNPRESSED state HIGH.
  digitalWrite(mediumHeightLEDPin, LOW);          // The default is low, but this is good form.

  // Setup pins for activate control
  pinMode(activateButtonPin, INPUT_PULLUP);
}

// This runs forever
void loop() {
  
  // Take care of the ball/hatch button
  if (ballHatchPushButton.update()) {
    if (ballHatchPushButton.fallingEdge()) {
      // Ball was the first LED on the whiteboard, so if we are in the
      // 'None' state, then make the ball LED turn on.
      if (digitalRead(hatchLEDPin) == LOW && digitalRead(ballLEDPin) == LOW) {
        digitalWrite(ballLEDPin, HIGH);
      } else {
        // toggle leds
        digitalWrite(hatchLEDPin, !digitalRead(hatchLEDPin));
        digitalWrite(ballLEDPin, !digitalRead(ballLEDPin));
      }
      
      // Simulate pressing Joystick buttons
      if (digitalRead(hatchLEDPin)) {
        Joystick.button(hatchJoystickButton, HIGH);
      } else if (digitalRead(ballLEDPin)) {
        Joystick.button(ballJoystickButton, HIGH);
      }
    } else if (ballHatchPushButton.risingEdge()) {
      // Simulate releasing Joystick buttons
      if (digitalRead(hatchLEDPin)) {
        Joystick.button(hatchJoystickButton, LOW);
      } else if (digitalRead(ballLEDPin)) {
        Joystick.button(ballJoystickButton, LOW);        
      }      
    }
  }

  // Take care of the medium height button
  if (mediumHeightPushButton.update()) {
    if (mediumHeightPushButton.fallingEdge()) {
      // set LED to high always if this button is pushed
      digitalWrite(mediumHeightLEDPin, HIGH);
      // Simulate pressing Joystick button
      Joystick.button(mediumHeightJoystickButton, HIGH);
    } else if (mediumHeightPushButton.risingEdge()) {
      // Simulate releasing Joystick button
      Joystick.button(mediumHeightJoystickButton, LOW);
    }
  }

  // Take care of the activate button
  if (activatePushButton.update()) {
    if (activatePushButton.fallingEdge()) {
      // Simulate pressing Joystick button
      Joystick.button(activateJoystickButton, HIGH);
    } else if (activatePushButton.risingEdge()) {
      // Simulate pressing Joystick button
      Joystick.button(activateJoystickButton, LOW);      
    }
  }
}
