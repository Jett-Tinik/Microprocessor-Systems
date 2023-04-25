#include <cmath>
#include <iostream>
using namespace std;

This is an individual assignment
Determine the result for each statement and state the rule in C++
Explain EXACTLY what happens.
You must get every question here correct in order to qualify to retake the first
question of test #1
1. Write down the type of each constant shown.
  Write code in C++ to print the number of bytes of each one using
        sizeof( ) to verify.
  a. 24 // int, int8_t (signed), size = 1
  b. -52 //int, int16_t, size = 2
  c. 1234567890 //int32_t, size = 4
  d. 3U // uint8_t(unsigned), size = 1
  e. 4h // hex (base 16), size = 4
  f. 5ULL // unsigned long long, size = 8
  g. 2.5 // double, size =8
  h. 2.2f // float, size = 4
        
2. Initialize each variable using the base shown:
a. int a = __7BULL_____           123 (in hex)
b. uint16_t b = __776_____      510 (in octal)
c. uint8_t c = ___1101001______     105 (in binary)
3. For each value, show the result and explain how it is computed
Be sure to explain steps in sequence, including type promotion.

a. int8_t d = 127;
d++;  // d= -128, adds one to the number held in d, however overflows after 127
      // (signed (2^8-1) for pos), so wraps around to -128
b.int8_t e = -125;
e -= 5;  // e= 126, subtracts 5 from value in d, however underflows after -128
         // (signed (2^8) for neg) sets d equal to new value of 126
c.uint8_t f = 255;
f += 2;  // f= 1, adds 2 to value in f, however overflows after 255, so wraps
         // around to 1 (if plus 1 then 0)
d.uint16_t g = 65533;
g += 3;  // g= 0, adds 3 to value in g, however overflows after 65533, so wraps
         // around to 0
e.uint16_t h = 2;
h -= 4;  // h= 65534, subracts 4 from value in H, underflow after 0, so wraps
         // around to 65534
f.uint32_t i = -1;  // 11111111111111111111111111111111

int main() {
  {
    uint32_t a =
        2000000000 + 2000000000;  // The 2 billions are added as ints (8 bit)
                                  // causes a ton of overflow problems
    uint32_t b = 4000000000U;  // U signifies that 4 billion range for uint32_t
                               // (0 to 4,294,978,296), the sum of these numbers
                               // are 4 billion which fits
    cout << "a=" << a << '\n';
    cout << "b=" << b << '\n';
  }

  {
    uint32_t a = 3 * 1.5;  // = 3*1.5 = 4 drops decimal
    uint32_t b = 3 * 1.6;  // =  3*1.6 = 4 drops decimal
    int32_t c = -3 * 1.6;  // = 3*1.6 = -4 drops the decimal
    cout << "a=" << a << '\n';
    cout << "b=" << b << '\n';
    cout << "c=" << c << '\n';
  }

  {
    uint64_t a = 3 / 5 + 4 / 5;  // = 0 beacuse both are decimals less than one
                                 // with are dropped so 0.blah plus 0.blah 0+0
    uint64_t b = 5 % 3 + 6 % 3 + 7 % 3;  // add remainders 2 + 0 + 1 = 3
    cout << "a=" << a << '\n';
    cout << "b=" << b << '\n';
  }

  {
    double a =
        7 /
        2;  // 7/2 =3.5, the decimal is dropped and then 3 is saved as a double
    double b = 7 / 2.0;  // 7/ 2.0(now initialized as a double) = 3.5
    cout << "a=" << a << '\n';
    cout << "b=" << b << '\n';
  }

  {
    bool b1 = true;    // =1
    bool b2 = false;   // =0
    bool b3 = 3 == 4;  // =0
    bool b4 = 3 != 4;  // =1

    double sum = 0;
    for (int i = 0; i < 10; i++) sum += 0.1;
    bool b5 = sum == 1;  // 0
    bool b6 = sum != 1;  // 1

    cout << "b1=" << b1 << '\n';  // 1
    cout << "b2=" << b2 << '\n';  // 0
    cout << "b3=" << b3 << '\n';  // 0
    cout << "b4=" << b4 << '\n';  // 1
    cout << "b5=" << b5 << '\n';  // 0
    cout << "b6=" << b6 << '\n';  // 1
  }

  {
    double a = 1.0 / 0.0;  // inf
    double b = 0.0 / 0.0;  // Nan
    double c = sqrt(a);    // inf
    double d = sin(a);     // Nan
    double e = sin(0);     // 0
    double f = sqrt(-1);   // Nan
  }
}