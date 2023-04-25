#include <iostream>
using namespace std;

/*
Why 64 bit?
1. division --> call a func
2. Good encryption
ssh...http(s) s is secure- encryption
man in the middle- cut wire login yourself
replay attack: I don't understand what u did, but I know you connected to blank,
i sent that package 100k times
3. Other specialty instructions
4.Program using Mac or M1
5. NEON vector engine

Cache--usually revisiting old info

AND(a,b)
OR(a,b)
XOR(a,b)
NOT(a)

CMOS -  technology used to implement current circuits
NAND
NOR

A   B       AND
0   0        0
0   1        0
1   0        0
1   1        1

Cisc - Complex instruction Set Computer
Risc - Reduced Instruction Set Computer

Memory arranged in a rectangle (rows,cols)
latency is much higher if we go to a new place

PC Where your code is
SP Where data is for functions
LR

.global main -- export this symbol

main:
      mov (move) x0 #0 // x0 = 0
      mov x1 #7 //
      mov x2 #255 // limited to 8 bits (but with a shift)
      xorq //fastest way to set 0

*/
int main() {
  cout << "yes" << endl;
  return 0;
}
