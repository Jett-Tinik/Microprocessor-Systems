/*
  Author: Jett Tinik and Philip Mascaro
  cite: "https://en.wikipedia.org/wiki/Heron's_formula" for Heron's Formula
  pledge: I pledge my Honor that I have abided by the Stevens Honor System.
 */
#include <math.h>

#include <cmath>
#include <iostream>
using namespace std;
int gcd(int a, int b) {
  int biggest_input = 0;

  if (b > a) {
    biggest_input = b;
  } else {
    biggest_input = a;
  }

  int temp_gcd = 0;
  for (int i = 1; i <= (biggest_input / 2) + 1; i++) {
    if (b % i == 0 && a % i == 0) {
      temp_gcd = i;
    }
  }

  return temp_gcd;
}

bool isPrime(int a) {
  bool is_prime_check = true;
  for (int i = 2; i <= (a / 2) + 1; i++) {
    if (a % i == 0) {
      is_prime_check = false;
    }
  }

  return is_prime_check;
}

int countPrimes(int a, int b) {
  int upper = 0;
  int lower = 0;
  if (b > a) {
    upper = b;
    lower = a;
  } else {
    upper = a;
    lower = b;
  }

  int counter = 0;
  for (int i = lower; i <= upper; i++) {
    counter += isPrime(i);
  }

  return counter;
}

void collatz(int a) {
  int current_value = a;
  while (current_value > 1) {
    cout << current_value << " ";
    if (current_value % 2 == 0) {
      current_value /= 2;
    } else {
      current_value *= 3;
      current_value += 1;
    }
  }
  cout << current_value << "\n";
}

double mean(double x[], int n) {
  double running_sum = 0;
  for (int i = 0; i < n; i++) {
    running_sum += x[i];
  }
  return (running_sum) / n;
}

int prod(int x[], int n) {
  int running_prod = 1;
  for (int i = 0; i < n; i++) {
    running_prod *= x[i];
  }
  return running_prod;
}

void demean(double x[], int n) {
  double given_mean = mean(x, n);

  // We are checking distances of the elements to the mean and selecting the
  // smaller distance between the saved and the current check. We need to
  // initialize the distance to be the largest distance possible for this data
  // type.
  double half_largest_size = 1;
  for (int i = 0; i < 63; i++) {
    half_largest_size *= 2;
  }

  double check = half_largest_size - 1;
  double max_size = half_largest_size + check;

  double current_size = max_size;
  double current_closest = 0;

  double difference = 0;
  for (int i = 0; i < n; i++) {
    difference = given_mean - x[i];
    if (difference < 0) {
      difference *= -1;
    }
    if (difference < current_size) {
      current_size = difference;
      current_closest = x[i];
    }
  }

  for (int i = 0; i < n; i++) {
    x[i] -= current_closest;
    // subtracts out the first closest item
    // for example, if the mean was 35 and the entries "30" and "40" were both
    // present, if 30 was first it subtracts 30 or if 40 was first it subtracts
    // 40
  }
}

void range_reverse(int x[], int n, int a, int b) {
  int old_a = x[a];
  int old_b = x[b];
  x[b] = old_a;
  x[a] = old_b;
  if (b - a > 1) {
    // recursion
    range_reverse(x, n, a + 1, b - 1);
  }
}
double hypot(double a, double b) {
  double c = sqrt((a * a) + (b * b));
  return c;
}

double mean(double a, double b) {
  double d = (a + b) / 2;
  return d;
}

bool pythagTriple(double a, double b) {
  double c = hypot(a, b);
  double intCheck = c;
  while (intCheck >= 1) {
    intCheck -= 1;
  }
  if (intCheck == 0.0) {
    return true;
  } else {
    return false;
  }
}

double areaOfTriangle(double x1, double y1, double x2, double y2, double x3,
                      double y3) {
  double a = hypot((y2 - y1), (x2 - x1));
  double b = hypot((y3 - y1), (x3 - x1));
  double c = hypot((y2 - y3), (x2 - x3));

  double s = (a + b + c) / 2;
  double area = sqrt(s * (s - a) * (s - b) * (s - c));
  return area;
}

int main() {
  cout << "gcd(12, 18)=" << gcd(12, 18) << '\n';
  cout << "gcd(1025, 3025)=" << gcd(1025, 3025) << '\n';
  cout << "isPrime(5)=" << isPrime(5) << '\n';
  cout << "isPrime(9)=" << isPrime(9) << '\n';

  cout << "isPrime(1001)=" << isPrime(1001) << '\n';
  cout << "isPrime(2601)=" << isPrime(2601) << '\n';
  cout << "isPrime(1013)=" << isPrime(1013) << '\n';

  cout << "countPrimes(1,100): " << countPrimes(1, 100) << '\n';
  cout << "countPrimes(1,10000): " << countPrimes(1, 10000) << '\n';

  collatz(5);   // should print out 5 16 8 4 2 1
  collatz(40);  // should print out 40 20 10 5 16 8 4 2 1
  collatz(17);

  double x[] = {10, 20, 30, 40, 50, 60};
  constexpr int n = sizeof(x) / sizeof(double);
  cout << mean(x, n) << '\n';  // should print 35

  double y[] = {1.0, 2.0, 3.0, 4.0};
  cout << mean(y, sizeof(y) / sizeof(double)) << '\n';  // should print 2.5

  int a[] = {3, 4, 1, 2, -2};
  cout << prod(a, sizeof(a) / sizeof(int)) << '\n';

  int b[] = {2, 4, 8, -2, -4};
  cout << prod(b, sizeof(b) / sizeof(int)) << '\n';

  demean(x, n);  // should subtract the mean from each element

  for (int i = 0; i < n; i++) cout << x[i] << ' ';
  cout << '\n';

  int c[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  range_reverse(c, 9, 2, 4);

  // you should print out the array c
  for (int i = 0; i < sizeof(c) / sizeof(int); i++)
    cout << c[i] << ' ';  // should print 1 2 5 4 3 6 7 8 9
  cout << '\n';

  cout << "hypot(3,4)=" << hypot(3, 4) << '\n';  // should print 5
  cout << "hypot(4,5)=" << hypot(4, 5) << '\n';

  cout << "mean(3.0,sqrt(8.0)) = " << mean(3.0, sqrt(8.0)) << '\n';

  cout << "mean(1,4)=" << mean(1, 4) << '\n';

  cout << "if sqrt(3**2 +4**2) is a whole number?: " << pythagTriple(3, 4)
       << endl;
  cout << "if sqrt(2**2 +3**2) is a whole number?: " << pythagTriple(2, 3)
       << endl;

  cout << areaOfTriangle(0, 0, 10, 0, 10, 5) << '\n';  // should be approx 25
  cout << areaOfTriangle(0, 0, 5, 3, 2, 6) << '\n';

  return 0;
}