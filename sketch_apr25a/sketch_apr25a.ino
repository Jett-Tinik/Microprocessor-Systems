#include <unistd.h>
int f(int x){
  return (4095*(x+1))/32; 
}

int y=0;

int delaytime = (3125/44);

void setup() {
  pinMode(DAC0, OUTPUT); 
  analogWriteResolution(12);
  //analogWrite(DAC0, 0);
  //analogWrite(DAC0, 4095);

}

void loop() {
  analogWrite(DAC0, f(y % 32));
  y=y+1;
  delayMicroseconds(delaytime);
}
