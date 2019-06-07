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

enum jsPos {jpUP,jpRIGHT,jpDOWN,jpLEFT,jpBUTTON}; //положения джойстика

////Джойстик новая версия на JoystickAxis
    /*констркутор джойстика: 
     * _x_pin - аналоговый пин координаты X, режим INPUT
     * _y_pin - аналоговый пин координаты Y, режим INPUT
     * _bt_pin - цифровой пин кнопки джойстика, режим INPUT_PULLUP
     * _sig_high - средний уровень сигнала аналоговых пинов для положений X+ и Y+, по умолчанию JSTK_HIGH_SIG
     * _sig_low - средний уровень сигнала аналоговых пинов для положений X- и Y-, по умолчанию JSTK_LOW_SIG
     * _sig_high_ts - диапазон отклонения сигнала аналоговых пинов для положений X+ и Y+, по умолчанию JSTK_HIGH_TRESHOLD
     * _sig_los_ts - диапазон отклонения сигнала аналоговых пинов для положений X- и Y-, по умолчанию JSTK_LOW_TRESHOLD
     */
class Joystick {
  protected:
    enum jsHardPos {jhpY_PLUS,jhpX_MINUS,jhpY_MINUS,jhpX_PLUS};//аппаратные положения джойстика
  public:
////Кнопка джойстика - наследник DigitalButton, jstk-джойстик, к которому привязана кнопка
    class JoystickButton:public DigitalButton {
      public:
        JoystickButton(Joystick *_jstk, byte pin,int pm=INPUT_PULLUP):jstk(_jstk),DigitalButton(pin,pm){}
        void onClick();
        void onHold();
        void onLongHold();
        void onIdle();
        void offClick();
        void offHold();
        void offLongHold();
        void offIdle();
      private:
        Joystick *jstk; //ссылка на джойстик
    };

////Ось джойстика - наследник AnalogButton, сигнал low=положение X-\Y-, сигнал high=положение X+\Y+
    class JoystickAxis:public AnalogButton {
      public:
        JoystickAxis(){};
        JoystickAxis(Joystick *_jstk,const byte &_pin,const uint16_t &_sigVal=JSTK_LOW_SIG,const uint16_t &_sigVal2=JSTK_HIGH_SIG,const uint8_t &_tresh=JSTK_LOW_TRESHOLD,const uint8_t &_tresh2=JSTK_HIGH_TRESHOLD,const int &_pm=INPUT_PULLUP);
        void run(unsigned long mls=0); //обработка сигналов кнопки с чтением пина
        void run(unsigned long mls, int ar); //обработка сигналов кнопки по уровню сигнала ar
        //void onClick() {Serial.print(sigValMin);Serial.print("\t");Serial.print(id);Serial.println(" onClick");};
        void onClick(const bool plus); //plus - направление нажатия по одной оси джойстика true=X+\Y+,false=X-\Y-
        void onClick(){ onClick(false); } //переопределение вызова обработчика в AnalogButton для наклона джойстика в положение low
        void onHold(const bool plus);
        void onHold(){ onHold(false); }
        void onLongHold(const bool plus);
        void onLongHold(){ onLongHold(false); }
        void onIdle(const bool plus);
        void onIdle(){ onIdle(false); }
        void offClick(const bool plus);
        void offClick(){ offClick(false); } 
        void offHold(const bool plus);
        void offHold(){ offHold(false); }
        void offLongHold(const bool plus);
        void offLongHold(){ offLongHold(false); }
        void offIdle(const bool plus);
        void offIdle(){ offIdle(false); }
      private:
        uint16_t sigVal2Min; //минимальное значение сигнала во втором положении джойстика (HIGH)
        uint16_t sigVal2Max; //максимальное значение сигнала во втором положении джойстика (HIGH)
        enum state btState2;
        enum input btInput2;
        Joystick *jstk; //ссылка на джойстик
        void DoAction(enum input in, unsigned long mls); //определить действие и вызвать обработчик
    };

    explicit Joystick(const uint8_t &_x_pin, 
                       const uint8_t &_y_pin, 
                       const uint8_t &_bt_pin, 
                       const uint16_t &_sig_high=JSTK_HIGH_SIG,
                       const uint16_t &_sig_low=JSTK_LOW_SIG,
                       const uint16_t &_sig_high_ts=JSTK_HIGH_TRESHOLD,
                       const uint16_t &_sig_low_ts=JSTK_LOW_TRESHOLD);
    void run(uint32_t mls=0); //обработка сигналов джойстика
    //void setTopPos(const jsHardPos _jhp){ jhpTop=_jhp; }; //установка верхней позиции джойстика
    void setTopPos(const byte pin, const bool plus);//установка позиции по номеру пина и уровня сигнала
    jsPos getAxisPosition(const JoystickAxis &ja, const bool plus);
    inline virtual void onClick(const jsPos jsp){};
    inline virtual void onHold(const jsPos jsp){};
    inline virtual void onLongHold(const jsPos jsp){};
    inline virtual void onIdle(const jsPos jsp){};
    inline virtual void offClick(const jsPos jsp){};
    inline virtual void offHold(const jsPos jsp){};
    inline virtual void offLongHold(const jsPos jsp){};
    inline virtual void offIdle(const jsPos jsp){};
  private:
    JoystickAxis jsAxisX,jsAxisY;
    JoystickButton bt; //кнопка джойстика
    byte x_pin,y_pin; //пины осей
    jsHardPos jhpTop=jhpY_PLUS;//верхнее положение джойстика, по умолчанию Y+
};


#endif
