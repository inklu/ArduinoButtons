#include "DigitalButton.h"

byte DigitalButton::sid;

void DigitalButton::run(unsigned long mls){
  if (!mls) mls = millis();
  int btRead = digitalRead(btPin);

  //Serial.print("S");
  
  if (btRead == HIGH && btPinMode != INPUT_PULLUP || btRead == LOW && btPinMode == INPUT_PULLUP) DoAction(biPress,mls);
  else DoAction(biRelease,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_DEBOUNCE) DoAction(biWaitDebounce,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_HOLD) DoAction(biWaitHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_LONG) DoAction(biWaitLongHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_IDLE) DoAction(biWaitIdle,mls);
}

void DigitalButton::DoAction(enum input in,unsigned long mls){
  enum state st = btState;
  switch(in) {
    case biRelease:
      btState = bsIdle;
      switch(st) {
        case bsClick:
          bitSet(btEvent,beOffClick);
          offClick();
          break;
        case bsHold:
          bitSet(btEvent,beOffHold);
          offHold();
          break;
        case bsLongHold:
          bitSet(btEvent,beOffLongHold);
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
          btState=bsClick;
          bitSet(btEvent,beOnClick);
          onClick();
          break;
      }
      break;
    case biWaitHold:
      switch(st) {
        case bsClick:
          btState = bsHold;
          bitSet(btEvent,beOnHold);
          onHold();
          break;
      }
      break;
    case biWaitLongHold:
      switch(st) {
        case bsHold:
          btState = bsLongHold;
          bitSet(btEvent,beOnLongHold);
          onLongHold();
          break;
      }
      break;
    case biWaitIdle:
      switch(st) {
        case bsLongHold:
          btState=bsForcedIdle;
          break;
      }
      break;
    case biPress:
      switch(st) {
        case bsIdle:
          pressTimeStamp = mls;
          btState = bsPreClick;
          break;
      }
      break;
  }
}

