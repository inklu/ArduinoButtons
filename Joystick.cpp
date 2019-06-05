#include "Joystick.h"

Joystick::Joystick(const uint8_t &_x_pin, 
                   const uint8_t &_y_pin,
                   const uint8_t &_bt_pin,
                   const uint16_t &_sig_high=JSTK_HIGH_SIG,
                   const uint16_t &_sig_low=JSTK_LOW_SIG,
                   const uint16_t &_sig_high_ts=JSTK_HIGH_TRESHOLD,
                   const uint16_t &_sig_low_ts=JSTK_LOW_TRESHOLD ):bt(_bt_pin),
                                                                   x_pin(_x_pin),
                                                                   y_pin(_y_pin),
                                                                   js{ AnalogButton(_x_pin,_sig_high,_sig_high_ts,INPUT),
                                                                       AnalogButton(_x_pin,_sig_low,_sig_low_ts,INPUT),
                                                                       AnalogButton(_y_pin,_sig_high,_sig_high_ts,INPUT),
                                                                       AnalogButton(_y_pin,_sig_low,_sig_low_ts,INPUT) }
{
  setTopPos(); //по умолчанию верхняя позиция джойстика - это Y+
}

void Joystick::run(uint32_t mls=0){
  if (!mls) mls = millis();
  bt.run(mls);
  uint16_t x_sig = analogRead(x_pin);
  uint16_t y_sig = analogRead(y_pin);
  for(byte i = 0; i<JSTK_POSITIONS;i++) js[i].run(mls);
  DoAction();
}

void Joystick::setTopPos(){
  setTopPos(y_pin);
}

void Joystick::setTopPos(const byte &_pin,const bool &_mode) {
  if(_pin == x_pin && _mode == HIGH) jspUp = X_PLUS;
  else if(_pin == x_pin && _mode == LOW) jspUp = X_MINUS;
  else if(_pin == y_pin && _mode == HIGH) jspUp = Y_PLUS;
  else if(_pin == y_pin && _mode == LOW) jspUp = Y_MINUS;

  switch(jspUp) {
    case X_PLUS:
      JSTK_EVENT_MAPPING(OnClick,RIGHT,DOWN,LEFT,UP)
      JSTK_EVENT_MAPPING(OffClick,RIGHT,DOWN,LEFT,UP)
      JSTK_EVENT_MAPPING(OnHold,RIGHT,DOWN,LEFT,UP)
      JSTK_EVENT_MAPPING(OffHold,RIGHT,DOWN,LEFT,UP)
      break;
    case X_MINUS:
      JSTK_EVENT_MAPPING(OnClick,LEFT,UP,RIGHT,DOWN)
      JSTK_EVENT_MAPPING(OffClick,LEFT,UP,RIGHT,DOWN)
      JSTK_EVENT_MAPPING(OnHold,LEFT,UP,RIGHT,DOWN)
      JSTK_EVENT_MAPPING(OffHold,LEFT,UP,RIGHT,DOWN)
      break;
    case Y_PLUS:
      JSTK_EVENT_MAPPING(OnClick,UP,RIGHT,DOWN,LEFT)
      JSTK_EVENT_MAPPING(OffClick,UP,RIGHT,DOWN,LEFT)
      JSTK_EVENT_MAPPING(OnHold,UP,RIGHT,DOWN,LEFT)
      JSTK_EVENT_MAPPING(OffHold,UP,RIGHT,DOWN,LEFT)
      break;
    case Y_MINUS:
      JSTK_EVENT_MAPPING(OnClick,DOWN,LEFT,UP,RIGHT)
      JSTK_EVENT_MAPPING(OffClick,DOWN,LEFT,UP,RIGHT)
      JSTK_EVENT_MAPPING(OnHold,DOWN,LEFT,UP,RIGHT)
      JSTK_EVENT_MAPPING(OffHold,DOWN,LEFT,UP,RIGHT)
      break;
  }
}

void Joystick::DoAction() {
  if(bt.checkEvent(beOnClick)) { OnClick_BUTTON(); bt.flushEvents(); }
  if(bt.checkEvent(beOffClick)) { OffClick_BUTTON(); bt.flushEvents(); }
  if(bt.checkEvent(beOnHold)) { OnHold_BUTTON(); bt.flushEvents(); }
  if(bt.checkEvent(beOffHold)) { OffHold_BUTTON(); bt.flushEvents(); }

  for(byte jp=0;jp<JSTK_POSITIONS;jp++){
    for(byte be=0;be<BTNS_EVENTS;be++){
      if(js[jp].checkEvent(be)) { onEvent[jp][be](); js[jp].flushEvents(); }
    }
  }
}