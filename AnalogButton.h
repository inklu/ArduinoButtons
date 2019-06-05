#ifndef ANALOGBUTTON_H
#define ANALOGBUTTON_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "DigitalButton.h"
#define BUTTON_ANALOG_SIGNAL_TRESHOLD (10)

//для аналогового пина - реализация нескольких кнопок на одном пине
class AnalogButton: public DigitalButton {
//    static const int BUTTON_ANALOG_SIGNAL_TRESHOLD = 10; //диапазон уровня аналогового сигнала от кнопки 
    uint16_t sigValMin; //минимальное значение сигнала
    uint16_t sigValMax; //максимальное значение сигнала
  public:
    AnalogButton(){};
    AnalogButton(byte pin,uint16_t sigVal,uint8_t tresh=BUTTON_ANALOG_SIGNAL_TRESHOLD,int pm=INPUT_PULLUP):DigitalButton(pin,pm){
      sigValMin = sigVal - tresh / 2;
      if(sigValMin > 1023) sigValMin = 0;
      sigValMax = sigVal + tresh / 2;
      if(sigValMax > 1023) sigValMax = 1023;
    }
	//настройка кнопки: пин, уровень сигнала, [режим пина]
    void setup(byte pin,uint16_t sigVal,uint8_t tresh=BUTTON_ANALOG_SIGNAL_TRESHOLD,int pm=INPUT_PULLUP){
      sigValMin = sigVal - tresh / 2;
      sigValMax = sigVal + tresh / 2;
      btPin = pin;
      btPinMode = pm;
      pinMode(btPin,btPinMode);
    }
    void run(unsigned long mls=0); //обработка сигналов кнопки с чтением пина
    void run(unsigned long mls, int ar); //обработка сигналов кнопки по уровню сигнала ar
    //void onClick() {Serial.print(sigValMin);Serial.print("\t");Serial.print(id);Serial.println(" onClick");};
};


#endif
