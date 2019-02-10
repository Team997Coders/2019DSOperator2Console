# 2019DSOperator2Console
Arduino sketch for [Teensyduino 3.5](https://www.pjrc.com/store/teensy35.html) implementation of operator 2 custom console.

## To Update Firmware
1. Download and install [Arduino](https://www.arduino.cc/en/Main/Software) for your development platform
2. Download and install [Teensyduino](https://www.pjrc.com/teensy/td_download.html) for your development platform
3. Load 2019DSOperator2Console.ino in Arduino IDE.
4. From the Tools menu, make sure Board/Teensyduino/Teensy 3.5 is selected.
5. From the Tools menu, make sure USB Type/Keyboard+Mouse+Joystick is selected.
6. Click the upload button on IDE.

## To Use
Teensy should automatically enumerate on workstation as a HID (Human Interface Device) supporting
simulating a keyboard, mouse, and joystick as three different devices. You can see how to use the
Joystick emulation [here](https://www.pjrc.com/teensy/td_joystick.html). Note that switches will need 
to be "debounced" to reliably transmit one click when the user expects one click. 
You can see how to use the Bounce library [here](https://www.pjrc.com/teensy/td_libs_Bounce.html).
