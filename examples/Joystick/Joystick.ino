#include <Joystick.h>

#ifndef CYCLE_STEP
#define CYCLE_STEP (200)
#endif

const byte pinX = A1, pinY = A0, pinBT = 7;
// Joystick(x,y,button,sig_high,sig_low,sig_high_treshold,sig_low_treshold): pinX mode = INPUT, pinY mode = INPUT, pinBT mode = INPUT_PULLUP
class MyJoystick:public Joystick {
    void OnClick_UP() { Serial.println("onclick UP"); }
    void OnClick_DOWN() { Serial.println("onclick DOWN"); }
    void OnClick_LEFT() { Serial.println("onclick LEFT"); }
    void OnClick_RIGHT() { Serial.println("onclick RIGHT"); }
    void OnClick_BUTTON() { Serial.println("onclick BUTTON"); }
    void OffClick_UP() { Serial.println("offclick UP"); }
    void OffClick_DOWN() { Serial.println("offclick DOWN"); }
    void OffClick_LEFT() { Serial.println("offclick LEFT"); }
    void OffClick_RIGHT() { Serial.println("offclick RIGHT"); }
    void OffClick_BUTTON() { Serial.println("offclick BUTTON"); }
    void OnHold_UP() { Serial.println("onhold UP"); }
    void OnHold_DOWN() { Serial.println("onhold DOWN"); }
    void OnHold_LEFT() { Serial.println("onhold LEFT"); }
    void OnHold_RIGHT() { Serial.println("onhold RIGHT"); }
    void OnHold_BUTTON() { Serial.println("onhold BUTTON"); }
    void OffHold_UP() { Serial.println("offhold UP"); }
    void OffHold_DOWN() { Serial.println("offhold DOWN"); }
    void OffHold_LEFT() { Serial.println("offhold LEFT"); }
    void OffHold_RIGHT() { Serial.println("offhold RIGHT"); }
    void OffHold_BUTTON() { Serial.println("offhold BUTTON"); }
    void OnLongHold_UP() { Serial.println("onlonghold UP"); }
    void OnLongHold_DOWN() { Serial.println("onlonghold DOWN"); }
    void OnLongHold_LEFT() { Serial.println("onlonghold LEFT"); }
    void OnLongHold_RIGHT() { Serial.println("onlonghold RIGHT"); }
    void OnLongHold_BUTTON() { Serial.println("onlonghold BUTTON"); }
    void OffLongHold_UP() { Serial.println("offlonghold UP"); }
    void OffLongHold_DOWN() { Serial.println("offlonghold DOWN"); }
    void OffLongHold_LEFT() { Serial.println("offlonghold LEFT"); }
    void OffLongHold_RIGHT() { Serial.println("offlonghold RIGHT"); }
    void OffLongHold_BUTTON() { Serial.println("offlonghold BUTTON"); }  
}

MyJoystick js(pinX,pinY,pinBT);

uint64_t cycle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  cycle = (uint64_t)millis() + CYCLE_STEP;  
  js.setTopPos(pinY,LOW); //верхняя позиция джойстика = Y-, по умолчанию верхняя позиция Y+
  Serial.println("Start");
}

void loop() {
  // put your main code here, to run repeatedly:
  js.run();
  if ((uint64_t)millis() >=  cycle) {
    cycle += CYCLE_STEP;
   
/*    Serial.print("X ");
    Serial.print(analogRead(pinX));
    Serial.print(" Y ");
    Serial.print(analogRead(pinY));
    Serial.print(" B ");
    Serial.println(digitalRead(pinBT));*/
  }

    
}
