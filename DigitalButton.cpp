#include "DigitalButton.h"

byte DigitalButton::sid;

void DigitalButton::run(unsigned long mls){
  if (!mls) mls = millis();
  byte btRead = digitalRead(btPin);
#ifdef DEBUG
  Serial.print(id);Serial.print(" ");Serial.println(btRead);
#endif

  if (btRead == HIGH && btPinMode != INPUT_PULLUP || btRead == LOW && btPinMode == INPUT_PULLUP) DoAction(biPress,mls);
  else DoAction(biRelease,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_DEBOUNCE) DoAction(biWaitDebounce,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_HOLD) DoAction(biWaitHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_LONG) DoAction(biWaitLongHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_IDLE) DoAction(biWaitIdle,mls);
}

void DigitalButton::DoAction(enum input in,unsigned long mls){
  DoAction(btState,in,mls);
}

void DigitalButton::DoAction(enum state &_btst, enum input in, unsigned long mls){
  enum state st = _btst;
  switch(in) {
    case biRelease:
      _btst = bsIdle;
      switch(st) {
        case bsClick:
          //bitSet(btEvent,beOffClick);
          offClick();
          break;
        case bsHold:
          //bitSet(btEvent,beOffHold);
          offHold();
          break;
        case bsLongHold:
          //bitSet(btEvent,beOffLongHold);
          offLongHold();
          break;
        case bsForcedIdle:
          offIdle();
          break;
      }
      break;
    case biWaitDebounce:
      switch(st) {
        case bsPreClick:
          _btst=bsClick;
          //bitSet(btEvent,beOnClick);
          onClick();
          break;
      }
      break;
    case biWaitHold:
      switch(st) {
        case bsClick:
          _btst = bsHold;
          //bitSet(btEvent,beOnHold);
          onHold();
          break;
      }
      break;
    case biWaitLongHold:
      switch(st) {
        case bsHold:
          _btst = bsLongHold;
          //bitSet(btEvent,beOnLongHold);
          onLongHold();
          break;
      }
      break;
    case biWaitIdle:
      switch(st) {
        case bsLongHold:
          _btst=bsForcedIdle;
          break;
      }
      break;
    case biPress:
      switch(st) {
        case bsIdle:
          pressTimeStamp = mls;
          _btst = bsPreClick;
          break;
      }
      break;
  }
}

