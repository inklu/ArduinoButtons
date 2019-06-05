# SmartButton
Processing digital &amp; analog signals from buttons and joystick on arduino platform

This project consist of three classes for processing buttons & joystick manipulators signals on arduino platform.

Virtual class SmartButton is designed for processing digital signals of buttons.

Virtual class AnalogButton is derived from SmartButton and designed for processing analog signals of buttons. For instance it can be used for processing many buttons connected to single analog pin through resistors.

Virtual class Joystick consists of one SmartButton for button and four AnalogButtons for all of joystick postitions.
