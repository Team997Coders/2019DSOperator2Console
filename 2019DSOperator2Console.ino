#include <Bounce.h>

const int ballHatchButtonPin = 35;
const int ballLEDPin = 33;
const int hatchLEDPin = 34;
Bounce ballHatchPushButton = Bounce(ballHatchButtonPin, 10);  // 10 ms debounce

void setup() {
  // put your setup code here, to run once:
  pinMode(ballLEDPin, OUTPUT);
  pinMode(hatchLEDPin, OUTPUT);
  pinMode(ballHatchButtonPin, INPUT_PULLUP);
  digitalWrite(hatchLEDPin, HIGH);
}

void loop() {
  if (ballHatchPushButton.update()) {
    if (ballHatchPushButton.fallingEdge()) {
      // toggle leds
      digitalWrite(hatchLEDPin, !digitalRead(hatchLEDPin));
      digitalWrite(ballLEDPin, !digitalRead(ballLEDPin));

      // Simulate pressing Joystick buttons
      if (digitalRead(hatchLEDPin)) {
        Joystick.button(1, 1);
      } else if (digitalRead(ballLEDPin)) {
        Joystick.button(2, 1);
      }
    } else if (ballHatchPushButton.risingEdge()) {
      // Simulate releasing Joystick buttons
      if (digitalRead(hatchLEDPin)) {
        Joystick.button(1, 0);
      } else if (digitalRead(ballLEDPin)) {
        Joystick.button(2, 0);        
      }      
    }
  }
}
