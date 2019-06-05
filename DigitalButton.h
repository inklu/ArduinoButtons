#ifndef DIGITALBUTTON_H
#define DIGITALBUTTON_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#ifndef DIGITAL_BUTTON_DEBOUNCE
#define DIGITAL_BUTTON_DEBOUNCE 10
#endif
#ifndef DIGITAL_BUTTON_HOLD
#define DIGITAL_BUTTON_HOLD 1000
#endif
#ifndef DIGITAL_BUTTON_LONG
#define DIGITAL_BUTTON_LONG 5000
#endif
#ifndef DIGITAL_BUTTON_IDLE
#define DIGITAL_BUTTON_IDLE 10000
#endif
#ifndef BTNS_EVENTS
#define BTNS_EVENTS 8
#endif

//static const int BUTTON_ANALOG_SIGNAL_TRESHOLD = 10;
//static const int analog_pins[] = {A0,A1,A2,A3,A4,A5};
//enum pinType {analog,digital};
//события кнопки: Нажата, Отпущена, ДвойноеНажатие, Отпускание после двойного нажатия...
enum buttonEvent {beOnClick,beOffClick,beOnDblClick,beOffDblClick,beOnHold,beOffHold,beOnLongHold,beOffLongHold};

//Класс кнопки для цифрового пина
class DigitalButton {
  protected:
    static byte sid;
    byte id;		//идентификатор кнопки для целей отладки 1,2,3,...
    byte btPin;		//пин кнопки
    int btPinMode;  //режим пина - по умолчанию INPUT_PULLUP
	//состояние кнопки: Ожидание, Нажатие, Нажата, Отпущена, Длительное нажатие, Принудительное ожидание
    enum state {bsIdle,bsPreClick,bsClick,bsHold,bsLongHold,bsForcedIdle}
      btState = bsIdle;
	//сигнал от кнопки: Нажата, Отпущена, Ожидание отскока, Ожидаение длительного нажатия,...
    enum input {biPress,biRelease,biWaitDebounce,biWaitHold,biWaitLongHold,biWaitIdle} 
      btInput = biRelease;
    unsigned long pressTimeStamp; //время фиксации события
    byte btEvent=0;
 
    void DoAction(enum input in,unsigned long mls); //определить действие и вызвать обработчик
  public:
    DigitalButton(){sid++;id=sid;};
    DigitalButton(byte pin,int pm=INPUT_PULLUP){
      btPin = pin;
      btPinMode = pm;
      pinMode(btPin,btPinMode);
      sid++;id=sid;
    }
    void setup(byte pin,int pm=INPUT_PULLUP){
      btPin = pin;
      btPinMode = pm;
      pinMode(btPin,btPinMode);
    } 
    virtual void run(unsigned long mls=0); //обработка событий кнопки
    byte getEvent(){return btEvent;}       //возврат события
    bool checkEvent(buttonEvent evt){return btEvent&bit(evt);} //проверка события
    void flushEvents(){btEvent=0;}			//сброс события

    inline virtual void onClick() { //Serial.print(id);Serial.println(" onClick");};
      //обработка события Кнопка нажата  
    }
    inline virtual void onHold() { //Serial.print(id);Serial.println(" onHold");};
      //обработка события Кнопка удержана  
    }
    inline virtual void onLongHold() { //Serial.print(id);Serial.println(" onLongHold");};
      //обработка события Кнопка долго удержана  
    }
    inline virtual void onIdle() { //Serial.print(id);Serial.println(" onIdle");};

	}
    inline virtual void offClick() { //Serial.print(id);Serial.println(" offClick");};
      //обработка события Кнопка отпущена после нажатия  
    }
    inline virtual void offHold() { //Serial.print(id);Serial.println(" offHold");};
      //обработка события Кнопка отпущена после удержания  
    }
    inline virtual void offLongHold() { //Serial.print(id);Serial.println(" offLongHold");};
      //обработка события Кнопка отпущена после длительного нажатия  
    }
    inline virtual void offIdle() { //Serial.print(id);Serial.println(" offIdle");};
      
    }
};


#endif
