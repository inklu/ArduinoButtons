#ifndef JOYSTICK_H
#define JOYSTICK_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "AnalogButton.h"

#ifndef JSTK_LOW_SIG
#define JSTK_LOW_SIG (40)
#endif

#ifndef JSTK_LOW_TRESHOLD
#define JSTK_LOW_TRESHOLD (80)
#endif

#ifndef JSTK_HIGH_SIG
#define JSTK_HIGH_SIG (1000)
#endif

#ifndef JSTK_HIGH_TRESHOLD
#define JSTK_HIGH_TRESHOLD (46)
#endif

#ifndef JSTK_POSITIONS
#define JSTK_POSITIONS 4
#endif

#ifndef JSTK_EVENT_MAPPING(BE,JP_YPLUS,JP_XMINUS,JP_YMINUS,JP_XPLUS)
#define JSTK_EVENT_MAPPING(BE,JP_YPLUS,JP_XMINUS,JP_YMINUS,JP_XPLUS) { \
      onEvent[Y_PLUS][be##BE] = (void*)&BE##_##JP_YPLUS ; \
      onEvent[X_MINUS][be##BE] = (void*)&BE##_##JP_XMINUS ; \
      onEvent[Y_MINUS][be##BE] = (void*)&BE##_##JP_YMINUS ; \
      onEvent[X_PLUS][be##BE] = (void*)&BE##_##JP_XPLUS ; }
#endif


class Joystick {
    typedef void (*EventHandler)(); //тип обработчика событий
    enum jsPositions {X_PLUS,X_MINUS,Y_PLUS,Y_MINUS} jspUp = Y_MINUS; //Верхнее положение джойстика
    DigitalButton bt; //кнопка джойстика
    AnalogButton js[JSTK_POSITIONS];  //4 аналоговых кнопки для всех положений джойстика
    //,x_plus,x_minus,y_plus,y_minus;
    uint8_t x_pin, y_pin; //аналоговые пины координат x и y
    void DoAction(); //вызов обработчиков событий
    EventHandler onEvent[JSTK_POSITIONS][BTNS_EVENTS];//массив ссылок функций - обработчиков событий. первое измерение - положение джойстика, второе - событие кнопки

  public:
    explicit Joystick(){};
    /*констркутор джойстика: 
     * _x_pin - аналоговый пин координаты X, режим INPUT
     * _y_pin - аналоговый пин координаты Y, режим INPUT
     * _bt_pin - цифровой пин кнопки джойстика, режим INPUT_PULLUP
     * _sig_high - средний уровень сигнала аналоговых пинов для положений X+ и Y+, по умолчанию JSTK_HIGH_SIG
     * _sig_low - средний уровень сигнала аналоговых пинов для положений X- и Y-, по умолчанию JSTK_LOW_SIG
     * _sig_high_ts - диапазон отклонения сигнала аналоговых пинов для положений X+ и Y+, по умолчанию JSTK_HIGH_TRESHOLD
     * _sig_los_ts - диапазон отклонения сигнала аналоговых пинов для положений X- и Y-, по умолчанию JSTK_LOW_TRESHOLD
     */
    explicit Joystick(const uint8_t &_x_pin, 
                      const uint8_t &_y_pin, 
                      const uint8_t &_bt_pin, 
                      const uint16_t &_sig_high=JSTK_HIGH_SIG,
                      const uint16_t &_sig_low=JSTK_LOW_SIG,
                      const uint16_t &_sig_high_ts=JSTK_HIGH_TRESHOLD,
                      const uint16_t &_sig_low_ts=JSTK_LOW_TRESHOLD);
    void run(uint32_t mls=0); //обработка сигналов от джойстика
    void setTopPos(); //установка верхней позиции джойстика по умолчанию Y+
    void setTopPos(const byte &_pin,const bool &_mode=HIGH); //установка верхней позиции джойстика
    virtual void OnClick_UP() { } //Serial.println("onclick UP"); }
    virtual void OnClick_DOWN() { } //Serial.println("onclick DOWN"); }
    virtual void OnClick_LEFT() { } //Serial.println("onclick LEFT"); }
    virtual void OnClick_RIGHT() { } //Serial.println("onclick RIGHT"); }
    virtual void OnClick_BUTTON() { } //Serial.println("onclick BUTTON"); }
    virtual void OffClick_UP() { } //Serial.println("offclick UP"); }
    virtual void OffClick_DOWN() { } //Serial.println("offclick DOWN"); }
    virtual void OffClick_LEFT() { } //Serial.println("offclick LEFT"); }
    virtual void OffClick_RIGHT() { } //Serial.println("offclick RIGHT"); }
    virtual void OffClick_BUTTON() { } //Serial.println("offclick BUTTON"); }
    virtual void OnHold_UP() { } //Serial.println("onhold UP"); }
    virtual void OnHold_DOWN() { } //Serial.println("onhold DOWN"); }
    virtual void OnHold_LEFT() { } //Serial.println("onhold LEFT"); }
    virtual void OnHold_RIGHT() { } //Serial.println("onhold RIGHT"); }
    virtual void OnHold_BUTTON() { } //Serial.println("onhold BUTTON"); }
    virtual void OffHold_UP() { } //Serial.println("offhold UP"); }
    virtual void OffHold_DOWN() { } //Serial.println("offhold DOWN"); }
    virtual void OffHold_LEFT() { } //Serial.println("offhold LEFT"); }
    virtual void OffHold_RIGHT() { } //Serial.println("offhold RIGHT"); }
    virtual void OffHold_BUTTON() { } //Serial.println("offhold BUTTON"); }
    virtual void OnLongHold_UP() { } //Serial.println("onlonghold UP"); }
    virtual void OnLongHold_DOWN() { } //Serial.println("onlonghold DOWN"); }
    virtual void OnLongHold_LEFT() { } //Serial.println("onlonghold LEFT"); }
    virtual void OnLongHold_RIGHT() { } //Serial.println("onlonghold RIGHT"); }
    virtual void OnLongHold_BUTTON() { } //Serial.println("onlonghold BUTTON"); }
    virtual void OffLongHold_UP() { } //Serial.println("offlonghold UP"); }
    virtual void OffLongHold_DOWN() { } //Serial.println("offlonghold DOWN"); }
    virtual void OffLongHold_LEFT() { } //Serial.println("offlonghold LEFT"); }
    virtual void OffLongHold_RIGHT() { } //Serial.println("offlonghold RIGHT"); }
    virtual void OffLongHold_BUTTON() { } //Serial.println("offlonghold BUTTON"); }
};

#endif
