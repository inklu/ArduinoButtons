#ifndef ANALOGBUTTON_H
#define ANALOGBUTTON_H

/*#ifndef DEBUG
#define DEBUG
#endif*/

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "DigitalButton.h"
#define BUTTON_ANALOG_SIGNAL_TRESHOLD (10) //analog signal treshold for state definition

//Analog signal button - implementation some buttons on a single pin
class AnalogButton: public DigitalButton {
//    static const int BUTTON_ANALOG_SIGNAL_TRESHOLD = 10; 
    uint16_t sigValMin; //minimum level of signal
    uint16_t sigValMax; //maximum level of signal
  public:
    AnalogButton(){};
    AnalogButton(byte pin,uint16_t sigVal,uint8_t tresh=BUTTON_ANALOG_SIGNAL_TRESHOLD,int pm=INPUT_PULLUP):DigitalButton(pin,pm){
      sigValMin = sigVal - tresh / 2;
      if(sigValMin > 1023) sigValMin = 0;
      sigValMax = sigVal + tresh / 2;
      if(sigValMax > 1023) sigValMax = 1023;
    }
    //setup button: analog pin, medium level of signal, [pin mode] = INPUT_PULLUP by default
    void setup(byte pin,uint16_t sigVal,uint8_t tresh=BUTTON_ANALOG_SIGNAL_TRESHOLD,int pm=INPUT_PULLUP){
      sigValMin = sigVal - tresh / 2;
      if(sigValMin > 1023) sigValMin = 0;
      sigValMax = sigVal + tresh / 2;
      if(sigValMax > 1023) sigValMax = 1023;
      btPin = pin;
      btPinMode = pm;
      pinMode(btPin,btPinMode);
    }
    void run(unsigned long mls=0); //processing of button pin signals with pin reading
    void run(unsigned long mls, word ar); //processing of the level of signal in ar parameter
    //void onClick() {Serial.print(sigValMin);Serial.print("\t");Serial.print(id);Serial.println(" onClick");};
};


#endif
