#ifndef ROTENC_H
#define ROTENC_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#ifndef PRINTDEBUG
#define PRINTDEBUG  { Serial.print("CLK "); \
                      Serial.print(getPinSig(newSig,epCLK)); \
                      Serial.print(" DT "); \
                      Serial.println(getPinSig(newSig,epDT)); }
#endif

#include <DigitalButton.h>

//Rotary Encoder
class RotEnc:public DigitalButton{
  public:
    RotEnc(const byte _clkPin, const byte _dtPin, const byte _swPin, const byte _swMode=INPUT_PULLUP);
    inline virtual void onClockwise(){}        //Rotate clockwise
    inline virtual void onCounterclockwise(){} //Rotate counterclockwise
    virtual void run(unsigned long _mls=0);    //Process signals
  private:
    enum encPins {epDT,epCLK};
    byte oldSig;
    byte clkPin;
    byte dtPin;
    byte swPin;
    byte swMode;
  protected:
    virtual byte readSig(){ return bit(epDT)*digitalRead(dtPin)+bit(epCLK)*digitalRead(clkPin); }; //read signals from CLK & DT
    virtual void setPinSig(byte &sig, const enum encPins ep){ bitSet(sig,ep); };
    virtual bool getPinSig(const byte sig, const enum encPins ep){ return bitRead(sig,ep); }; //get CLK or DT singal
};

#endif
