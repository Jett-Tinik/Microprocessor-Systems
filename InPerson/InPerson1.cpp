#include <iostream>
using namespace std;
/*
byte: 8 bits   1010 1111
               1011 1111=
parity         even--> always mkae even number of 1
               1010 1111 p=0
               1110 1111 p=1
               0000 0001 p=2
*/

int add(int a, int b) { return a + b; }

// funtion prototype
double hypot(double a, double b);

int factorial(int n) {  // n*(n-1)*(n-2)...1
  int prod = 1;
  for (int i = 1; i <= n; i++) prod *= i;
  return prod;
}

int fact(int x) { return x * fact(x - 1); }

int main() {
  // 100 lines of code
  // cout<<add(2,3)<<'\n';
  // optimizer
  cout << (2 + 3) << '\n';
  cout << factorial(5) << '\n';
  cout << "hello" << '\n';
  cout << fact(5) << '\n';
  
}