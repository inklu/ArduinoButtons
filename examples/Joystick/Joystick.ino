#include <Joystick.h>

#ifndef CYCLE_STEP
#define CYCLE_STEP (200)
#endif

const byte pinX = A1, pinY = A0, pinBT = 4;

void printDebug() {
  Serial.print("X ");
  Serial.print(analogRead(pinX));
  Serial.print(" Y ");
  Serial.print(analogRead(pinY));
  Serial.print(" B ");
  Serial.println(digitalRead(pinBT));
}

// Joystick(x,y,button,sig_high,sig_low,sig_high_treshold,sig_low_treshold): pinX mode = INPUT, pinY mode = INPUT, pinBT mode = INPUT_PULLUP
class MyJoystick: public Joystick {
    String elem[5] = {"UP", "RIGHT", "DOWN", "LEFT", "BUTTON"};
  public:
    MyJoystick(const uint8_t &_x_pin, const uint8_t &_y_pin, const uint8_t &_bt_pin): Joystick(_x_pin, _y_pin, _bt_pin) {}
    void onClick(const jsPos jsp) {
      Serial.print("onclick ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
    void onHold(const jsPos jsp) {
      Serial.print("onhold ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
    void onLongHold(const jsPos jsp) {
      Serial.print("onlonghold ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
    void onIdle(const jsPos jsp) {
      Serial.print("onidle ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
    void offClick(const jsPos jsp) {
      Serial.print("offclick ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
    void offHold(const jsPos jsp) {
      Serial.print("offhold ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
    void offLongHold(const jsPos jsp) {
      Serial.print("offlonghold ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
    void offIdle(const jsPos jsp) {
      Serial.print("offidle ");
      Serial.println(elem[jsp]);
      //printDebug();
    }
};

MyJoystick js(pinX, pinY, pinBT);

uint64_t cycle;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  cycle = (uint64_t)millis() + CYCLE_STEP;
  js.setTopPos(pinX,HIGH); //верхняя позиция джойстика = X+, по умолчанию верхняя позиция Y+
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
