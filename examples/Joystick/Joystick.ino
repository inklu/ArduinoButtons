#include <Joystick.h>

#ifndef CYCLE_STEP
#define CYCLE_STEP (200)
#endif

const byte pinX = A1, pinY = A0, pinBT = 7;
// Joystick(x,y,button,sig_high,sig_low,sig_high_treshold,sig_low_treshold): pinX mode = INPUT, pinY mode = INPUT, pinBT mode = INPUT_PULLUP
Joystick js(pinX,pinY,pinBT);

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
