#include "AnalogButton.h"

void AnalogButton::run(unsigned long mls){
  //Serial.print("A");
  if (!mls) mls = millis();
  word ar = analogRead(btPin);
#ifdef DEBUG
  Serial.println(ar);
#endif
  run(mls,ar);  
}
void AnalogButton::run(unsigned long mls,word ar){
  if (ar >= sigValMin && ar <= sigValMax) DoAction(biPress,mls);
  else DoAction(biRelease,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_DEBOUNCE) DoAction(biWaitDebounce,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_HOLD) DoAction(biWaitHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_LONG) DoAction(biWaitLongHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_IDLE) DoAction(biWaitIdle,mls);
}
