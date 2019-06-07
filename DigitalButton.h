#ifndef DIGITALBUTTON_H
#define DIGITALBUTTON_H

#if ARDUINO >= 100
  #include <Arduino.h>
#else
  #include <WProgram.h>
#endif

#ifndef DIGITAL_BUTTON_DEBOUNCE
#define DIGITAL_BUTTON_DEBOUNCE 10 //wait mls after button pressed and before onClick is raised
#endif
#ifndef DIGITAL_BUTTON_HOLD
#define DIGITAL_BUTTON_HOLD 1000 //wait mls after button pressed and before onHold is raised
#endif
#ifndef DIGITAL_BUTTON_LONG
#define DIGITAL_BUTTON_LONG 5000 //wait mls after button pressed and before onLongHold is raised
#endif
#ifndef DIGITAL_BUTTON_IDLE
#define DIGITAL_BUTTON_IDLE 10000
#endif
#ifndef BTNS_EVENTS
#define BTNS_EVENTS 8 //need to be revised
#endif

//static const int BUTTON_ANALOG_SIGNAL_TRESHOLD = 10;
//static const int analog_pins[] = {A0,A1,A2,A3,A4,A5};
//enum pinType {analog,digital};
//button events: Pressed, Debounce, DoubleClick, ...
enum buttonEvent {beOnClick,beOffClick,beOnDblClick,beOffDblClick,beOnHold,beOffHold,beOnLongHold,beOffLongHold};

//Button class for digital pin
class DigitalButton {
  protected:
    static byte sid;
    byte id;		//ID of a button for debug purposes 1,2,3,...
    byte btPin;		//button input pin
    int btPinMode;      //pin mode, INPUT_PULLUP by default
    //button state
    enum state {bsIdle,bsPreClick,bsClick,bsHold,bsLongHold,bsForcedIdle}
      btState = bsIdle;
    //button signal
    enum input {biPress,biRelease,biWaitDebounce,biWaitHold,biWaitLongHold,biWaitIdle} 
      btInput = biRelease;
    unsigned long pressTimeStamp; //time when button is pressed
    byte btEvent=0; //need to be revised
 
    void DoAction(enum input in,unsigned long mls); //define an action & call an handler
    void DoAction(enum state _btst, enum input in, unsigned long mls);
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
    virtual void run(unsigned long mls=0); //processing button events
    byte getEvent(){return btEvent;}       //return button events //need to be revised
    bool checkEvent(buttonEvent evt){return btEvent&bit(evt);} //check the event //need to be revised
    void flushEvents(){btEvent=0;}			//reset the event //need to be revised

    inline virtual void onClick() { //Serial.print(id);Serial.println(" onClick");
      //handle an event
    }
    inline virtual void onHold() { //Serial.print(id);Serial.println(" onHold");
      //handle an event
    }
    inline virtual void onLongHold() { //Serial.print(id);Serial.println(" onLongHold");
      //handle an event
    }
    inline virtual void onIdle() { //Serial.print(id);Serial.println(" onIdle");
      //handle an event
	}
    inline virtual void offClick() { //Serial.print(id);Serial.println(" offClick");
      //handle an event
    }
    inline virtual void offHold() { //Serial.print(id);Serial.println(" offHold");
      //handle an event
    }
    inline virtual void offLongHold() { //Serial.print(id);Serial.println(" offLongHold");
      //handle an event
    }
    inline virtual void offIdle() { //Serial.print(id);Serial.println(" offIdle");
      //handle an event
    }
};


#endif
