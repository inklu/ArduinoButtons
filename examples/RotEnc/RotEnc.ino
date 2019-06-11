#include <RotEnc.h>

const int clkPin = 2; //the clk attach to pin 2
const int dtPin = 3; //the dt pin attach to pin 3
const int swPin = 4 ; //the sw pin attach to pin 4

int encoderVal = 0;

class MyRotEnc:public RotEnc {
  public:
    MyRotEnc(const byte _clkPin, const byte _dtPin, const byte _swPin):RotEnc(_clkPin,_dtPin,_swPin){};
    void onClockwise() { encoderVal++; Serial.println(encoderVal); }
    void onCounterclockwise() { encoderVal--; Serial.println(encoderVal); }
    void offClick() { encoderVal=0; Serial.println("Counter reset"); }
};

MyRotEnc re(clkPin,dtPin,swPin);

void setup()
{
  Serial.begin(9600); // initialize serial communications at 9600 bps
  Serial.println("Start");
}

void loop()
{
  re.run();
}
