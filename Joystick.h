#ifndef JOYSTICK_H
#define JOYSTICK_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#include "AnalogButton.h"

#ifndef JSTK_LOW_SIG
#define JSTK_LOW_SIG (40) //medium level of low signal of a joystick position
#endif

#ifndef JSTK_LOW_TRESHOLD
#define JSTK_LOW_TRESHOLD (80) //treshold of low signal
#endif

#ifndef JSTK_HIGH_SIG
#define JSTK_HIGH_SIG (1000) //medium level of high signal of a joystick position
#endif

#ifndef JSTK_HIGH_TRESHOLD
#define JSTK_HIGH_TRESHOLD (46) //treshold of high signal
#endif

enum jsPos {jpUP,jpRIGHT,jpDOWN,jpLEFT,jpBUTTON}; //Joystick positions with button

////Joystick class
    /*Joystick constructor: 
     * _x_pin - analog pin of axis X, pin mode INPUT
     * _y_pin - analog pin of axis Y, pin mode INPUT
     * _bt_pin - digital pin of joystick button, pin mode INPUT_PULLUP by default
     * _sig_high - medium level of a high signal for positions X+ & Y+, =JSTK_HIGH_SIG by default
     * _sig_low - medium level of a low signal for positions X- & Y-, =JSTK_LOW_SIG by default
     * _sig_high_ts - treshold of a high signal for positions X+ и Y+, =JSTK_HIGH_TRESHOLD by default
     * _sig_los_ts - treshold of a low signal for positions X- и Y-, =JSTK_LOW_TRESHOLD by default
     */
class Joystick {
  protected:
    enum jsHardPos {jhpY_PLUS,jhpX_MINUS,jhpY_MINUS,jhpX_PLUS};//hardware positions of a joystick
  public:
////Joystick button class - inherited from DigitalButton
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
        Joystick *jstk; //is an address of a linked joystick object
    };

////Joystick axis class - inherited from AnalogButton, low level of a signal is equal to positions X- & Y-, high level of a signal is equal to positions X+ & Y+
    class JoystickAxis:public AnalogButton {
      public:
        JoystickAxis(){};
        JoystickAxis(Joystick *_jstk,const byte &_pin,const uint16_t &_sigVal=JSTK_LOW_SIG,const uint16_t &_sigVal2=JSTK_HIGH_SIG,const uint8_t &_tresh=JSTK_LOW_TRESHOLD,const uint8_t &_tresh2=JSTK_HIGH_TRESHOLD,const int &_pm=INPUT_PULLUP);
        void run(unsigned long mls=0); //processing of "buttons" (from X or Y) signal with pin reading
        void run(unsigned long mls, int ar); //processing of a signal level <ar>
        //void onClick() {Serial.print(sigValMin);Serial.print("\t");Serial.print(id);Serial.println(" onClick");};
        void onClick(const bool plus); //plus is a direction on a single axis defined by the level of a signal true=X+\Y+,false=X-\Y-
        void onClick(){ onClick(false); } //overloaded definition of AnalogButton::onClick() method for low level of a signal, X-\Y-
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
        uint16_t sigVal2Min; //minimum of a signal level for the second axis position (HIGH level)
        uint16_t sigVal2Max; //maximum of a signal level for the second axis position (HIGH level)
        enum state btState2; 
        enum input btInput2;
        Joystick *jstk; //address of a joystick object
        //void DoAction(enum input in, unsigned long mls); //overloaded DigitalButton::DoAction(...) method for the second axis position
    };

    explicit Joystick(const uint8_t &_x_pin, 
                       const uint8_t &_y_pin, 
                       const uint8_t &_bt_pin, 
                       const uint16_t &_sig_high=JSTK_HIGH_SIG,
                       const uint16_t &_sig_low=JSTK_LOW_SIG,
                       const uint16_t &_sig_high_ts=JSTK_HIGH_TRESHOLD,
                       const uint16_t &_sig_low_ts=JSTK_LOW_TRESHOLD);
    void run(uint32_t mls=0); //processing of joystick manipulation signals
    //void setTopPos(const jsHardPos _jhp){ jhpTop=_jhp; }; 
    void setTopPos(const byte pin, const bool plus);//setup the top position of a joystick by the pin and the signal level
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
    JoystickButton bt; //joystick button object
    byte x_pin,y_pin; //X&Y axes pins
    jsHardPos jhpTop=jhpY_PLUS;//top joystick position, =Y+ by default
};


#endif
