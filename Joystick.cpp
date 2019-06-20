#include "Joystick.h"

/*#ifndef DEBUG
#define DEBUG
#endif*/

////Joystick button
void Joystick::JoystickButton::onClick() {
  jstk->onClick(jpBUTTON);
}
void Joystick::JoystickButton::onHold() {
  jstk->onHold(jpBUTTON);
}
void Joystick::JoystickButton::onLongHold() {
  jstk->onLongHold(jpBUTTON);
}
void Joystick::JoystickButton::onIdle() {
  jstk->onIdle(jpBUTTON);
}
void Joystick::JoystickButton::offClick() {
  jstk->offClick(jpBUTTON);
}
void Joystick::JoystickButton::offHold() {
  jstk->offHold(jpBUTTON);
}
void Joystick::JoystickButton::offLongHold() {
  jstk->offLongHold(jpBUTTON);
}
void Joystick::JoystickButton::offIdle() {
  jstk->offIdle(jpBUTTON);
}
////Joystick axis
Joystick::JoystickAxis::JoystickAxis(Joystick *_jstk,
                           const byte &_pin,
                           const uint16_t &_sigVal=JSTK_LOW_SIG,
                           const uint16_t &_sigVal2=JSTK_HIGH_SIG,
                           const uint8_t &_tresh=JSTK_LOW_TRESHOLD,
                           const uint8_t &_tresh2=JSTK_HIGH_TRESHOLD,
                           const int &_pm=INPUT_PULLUP):jstk(_jstk),AnalogButton(_pin,_sigVal,_tresh,_pm) {
      sigVal2Min = _sigVal2 - _tresh2 / 2;
      if(sigVal2Min > 1023) sigVal2Min = 0;
      sigVal2Max = _sigVal2 + _tresh2 / 2;
      if(sigVal2Max > 1023) sigVal2Max = 1023;
#ifdef DEBUG
      Serial.print("SigVal2Min ");
      Serial.println(sigVal2Min);
      Serial.print("SigVal2Max ");
      Serial.println(sigVal2Max);
#endif
    }

void Joystick::JoystickAxis::run(unsigned long mls,int ar){
  AnalogButton::run(mls,ar); //processing of a low level of a signal, positions X-\Y-
  //processing of a high level of a signal, positions X+\Y+
  if (ar >= sigVal2Min && ar <= sigVal2Max) DoAction(biPress,mls);
  else DoAction(biRelease,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_DEBOUNCE) DoAction(biWaitDebounce,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_HOLD) DoAction(biWaitHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_LONG) DoAction(biWaitLongHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_IDLE) DoAction(biWaitIdle,mls);
}

void Joystick::JoystickAxis::run(unsigned long mls){
  if (!mls) mls = millis();
  int ar = analogRead(btPin);
  run(mls,ar);
}


void Joystick::JoystickAxis::DoAction(enum input in,unsigned long mls){
  enum state st = btState2;
  switch(in) {
    case biRelease:
      btState2 = bsIdle;
      switch(st) {
        case bsClick:
          offClick(true);
          break;
        case bsHold:
          offHold(true);
          break;
        case bsLongHold:
          offLongHold(true);
          break;
        case bsForcedIdle:
          offIdle(true);
          break;
      }
      break;
    case biWaitDebounce:
      switch(st) {
        case bsPreClick:
          btState2=bsClick;
          onClick(true);
          break;
      }
      break;
    case biWaitHold:
      switch(st) {
        case bsClick:
          btState2 = bsHold;
          onHold(true);
          break;
      }
      break;
    case biWaitLongHold:
      switch(st) {
        case bsHold:
          btState2 = bsLongHold;
          onLongHold(true);
          break;
      }
      break;
    case biWaitIdle:
      switch(st) {
        case bsLongHold:
          btState2=bsForcedIdle;
          break;
      }
      break;
    case biPress:
      switch(st) {
        case bsIdle:
          pressTimeStamp = mls;
          btState2 = bsPreClick;
          break;
      }
      break;
  }
}

void Joystick::JoystickAxis::onClick(const bool plus) {
  jstk->onClick(jstk->getAxisPosition(*this,plus));
}
void Joystick::JoystickAxis::onHold(const bool plus) {
  jstk->onHold(jstk->getAxisPosition(*this,plus));
}
void Joystick::JoystickAxis::onLongHold(const bool plus) {
  jstk->onLongHold(jstk->getAxisPosition(*this,plus));
}
void Joystick::JoystickAxis::onIdle(const bool plus) {
  jstk->onIdle(jstk->getAxisPosition(*this,plus));
}
void Joystick::JoystickAxis::offClick(const bool plus) {
  jstk->offClick(jstk->getAxisPosition(*this,plus));
}
void Joystick::JoystickAxis::offHold(const bool plus) {
  jstk->offHold(jstk->getAxisPosition(*this,plus));
}
void Joystick::JoystickAxis::offLongHold(const bool plus) {
  jstk->offLongHold(jstk->getAxisPosition(*this,plus));
}
void Joystick::JoystickAxis::offIdle(const bool plus) {
  jstk->offIdle(jstk->getAxisPosition(*this,plus));
}


////Joystick
Joystick::Joystick(const uint8_t &_x_pin, 
                     const uint8_t &_y_pin,
                     const uint8_t &_bt_pin,
                     const uint16_t &_sig_high=JSTK_HIGH_SIG,
                     const uint16_t &_sig_low=JSTK_LOW_SIG,
                     const uint16_t &_sig_high_ts=JSTK_HIGH_TRESHOLD,
                     const uint16_t &_sig_low_ts=JSTK_LOW_TRESHOLD ): bt(this,_bt_pin),
                                                                      x_pin(_x_pin),
                                                                      y_pin(_y_pin),
                                                                      jsAxisX(this,_x_pin,_sig_low,_sig_high,_sig_low_ts,_sig_high_ts,INPUT),
                                                                      jsAxisY(this,_y_pin,_sig_low,_sig_high,_sig_low_ts,_sig_high_ts,INPUT) {

}

jsPos Joystick::getAxisPosition(const JoystickAxis &ja, const bool plus){  
  //Top position Y+(0),X-(1),Y-(2),X+(3)
  jsPos jpDef;
  //for position Y+
  if(&ja==&jsAxisY && plus==HIGH) jpDef = jpUP; //0 3 2 1
  //for position X-
  if(&ja==&jsAxisX && plus==LOW) jpDef = jpRIGHT; //1 0 3 2
  //for position Y-
  if(&ja==&jsAxisY && plus==LOW) jpDef = jpDOWN; //2 1 0 3
  //for position X+
  if(&ja==&jsAxisX && plus==HIGH) jpDef = jpLEFT; //3 2 1 0

  //adjust of a required position according to the top position
  short int pos = jpDef - jhpTop;
  return (pos<0)?(pos+4):(pos);
}

void Joystick::run(uint32_t mls=0){
  if (!mls) mls = millis();
  bt.run(mls);
  jsAxisX.run(mls);
  jsAxisY.run(mls);
}

void Joystick::setTopPos(const byte pin,const bool plus){
  if(pin==x_pin){
    if(plus) jhpTop = jhpX_PLUS;
    else jhpTop = jhpX_MINUS; }
  else if(pin==y_pin){
    if(plus) jhpTop = jhpY_PLUS;
    else jhpTop = jhpY_MINUS; }
}
