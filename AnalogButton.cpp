#include "AnalogButton.h"

//void AnalogButton::run(unsigned long mls,int ar){
//Обработка событий аналоговой кнопки с чтением сигнала с пина
void AnalogButton::run(unsigned long mls){
  //Serial.print("A");
  if (!mls) mls = millis();
  int ar = analogRead(btPin);
  run(mls,ar);  
}
//Обработка событий аналоговой кнопки по уровню сигнала ar
void AnalogButton::run(unsigned long mls,int ar){

  //Serial.print("B");
  
  if (ar >= sigValMin && ar <= sigValMax) DoAction(biPress,mls);
  else DoAction(biRelease,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_DEBOUNCE) DoAction(biWaitDebounce,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_HOLD) DoAction(biWaitHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_LONG) DoAction(biWaitLongHold,mls);
  if (mls - pressTimeStamp > DIGITAL_BUTTON_IDLE) DoAction(biWaitIdle,mls);
}
