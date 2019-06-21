# ArduinoButtons
Processing digital &amp; analog signals from buttons and joystick on arduino platform

This project consist of three classes for processing buttons, joystick, rotary encoder manipulators signals on arduino platform.

Virtual class DigitalButton is designed for processing digital signals of buttons. DigitalButton is based on the SmartButton class by Sergei Keler https://github.com/nw-wind/SmartButton.

Virtual class AnalogButton is derived from DigitalButton and designed for processing analog signals of buttons. For instance it can be used for processing many buttons connected to single analog pin through resistors.

Virtual class Joystick consists of one DigitalButton for button and two JoystickAxis derived from AnalogButton for joystick axes. Each axis is like a two analog buttons, one of which is defined for low level of a signal and another for the high one.

Virtual class RotEnc is inherited from DigitalButton and modeled for processing digital signals CLK, DT, SW from rotary encoder.
