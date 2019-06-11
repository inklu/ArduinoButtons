#include "RotEnc.h"


RotEnc::RotEnc(const byte _clkPin, const byte _dtPin, const byte _swPin, const byte _swMode): DigitalButton(_swPin,_swMode),
                                                                                              clkPin(_clkPin),
                                                                                              dtPin(_dtPin),
                                                                                              swPin(_swPin),
                                                                                              swMode(_swMode) {
  pinMode(_clkPin,INPUT);
  pinMode(_dtPin,INPUT);
  pinMode(_swPin,_swMode);
  oldSig = readSig();
}

void RotEnc::run(unsigned long _mls){
  if(!_mls) _mls = millis();
  //Rotary encoder
  byte newSig = readSig();
  if (getPinSig(newSig,epDT)!=getPinSig(oldSig,epDT) && getPinSig(newSig,epCLK)==getPinSig(oldSig,epCLK)) { 
    if (getPinSig(newSig,epCLK)==getPinSig(newSig,epDT)) onClockwise();
#ifdef __DEBUG__
    PRINTDEBUG
#endif    
  }
  else if (getPinSig(newSig,epCLK)!=getPinSig(oldSig,epCLK) && getPinSig(newSig,epDT)==getPinSig(oldSig,epDT)) { 
    if (getPinSig(newSig,epCLK)==getPinSig(newSig,epDT)) onCounterclockwise();
#ifdef __DEBUG__
    PRINTDEBUG
#endif    
  }
  oldSig = newSig;
  //Encoder button
  DigitalButton::run(_mls);
}
