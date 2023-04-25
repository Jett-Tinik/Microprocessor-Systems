/*
  Author: Jett Tinik and Philip Mascaro
  cite:
  pledge: I pledge my Honor that I
  have abided by the Stevens Honor System.
 */
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <iomanip>
#include <iostream>
using namespace std;

// question 1:
float sum_forward(int n) {
  float sum1 = 0;
  for (float i = 1; i <= n; i++) {
    sum1 += 1.0 / i;
    // cout << sum1 << ' ';
  }
  cout << sum1 << ' ' << '\n';
  return sum1;
}

float sum_backward(int n) {
  float sum2 = 0;
  for (float i = n; i >= 1; i--) {
    sum2 += 1.0 / i;
    // cout << sum2 << ' ';
  }
  cout << sum2 << ' ' << '\n';
  return sum2;
}

// we introduced this function to compute the difference
float roundoff_error_difference(int n) {
  float difference = sum_forward(n) - sum_backward(n);

  // sum from smallest item to largest item is the most accurate because it
  // allows for more carry-over to stack up

  return difference;
}

// question 2:
// part 1:
float mystery_sum1(int n) {
  float s = 0;
  for (uint32_t i = 1; i <= n; i++) {
    s += 1.0 / (i * i);
  }

  return s;
}

float mystery_sum1corrected(int n) {
  float s = 0;
  for (uint64_t i = 1; i <= n; i++) {
    s += 1.0 / (i * i);
  }

  return s;
}

// part 2:
float mystery_sum2corrected(int n) {
  float s = 0;
  for (uint64_t i = n; i >= 1; i--) {
    s += 1.0 / (i * i);
  }

  return s;
}

// question 3:
double combineNumber(int a, int b) {
  int test = b;
  double dec_b = 0.0 + b;
  while (test > 0) {
    test /= 10;
    dec_b /= 10;
  }
  return a + dec_b;
}

// question 4:
void add(double c[3][3], const double a[3][3], const double b[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      c[i][j] = a[i][j] + b[i][j];
    }
  }
}

// only need to consider the 3*3 2D matrix
void print(const double a[3][3]) {
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << a[i][j] << '\t';
    }
    cout << '\n';
  }
  cout << '\n';
}

// question 5:
void quadratic(double a, double b, double c) {
  double right = sqrt((b * b) - (4 * a * c));
  double r1 = (-b + right) / (2 * a);
  double r2 = (-b - right) / (2 * a);
  cout << r1 << '\t' << r2 << '\n';
}

int main() {
  cout << setprecision(12) << setw(10);
  // test cases for question 1:
  cout << "answers for question 1:-------------------------" << endl;
  float q1_ans_1 = sum_forward(100);
  float q1_ans_2 = sum_backward(100);

  // we added this for the compare
  cout << roundoff_error_difference(100);
  cout << '\n';

  // test cases for question 2:
  cout << "answers for question 2:-------------------------" << endl;
  // input variable n = 100 for both functions,
  for (int n = 100; n <= 10000000; n *= 2) {
    float s1 = mystery_sum1(n);
    float s2 = mystery_sum1corrected(n);
    float s3 = mystery_sum2corrected(n);
    /*
    printf("%9d     %9.7lf %9.7lf %9.7lf %9.7lf %9.7lf %9.7lf\n", n, s1,
           sqrt(6 * s1), s2, sqrt(6 * s2), s3, sqrt(6 * s3));
           */

    // we added the double tab so that the columns are easier to see once the
    // "inf" items decrease the column size
    cout << n << '\t' << '\t' << s1 << '\t' << '\t' << sqrt(6 * s1) << '\t'
         << '\t' << s2 << '\t' << '\t' << sqrt(6 * s2) << '\t' << '\t' << s3
         << '\t' << '\t' << sqrt(6 * s3) << '\n';
    // backwards sum is more accurate to pi because the backwards sum
    // gives 3.14159250259 while the forward sum gives 3.14139342308

#if 0
    cout << n << '\t' << s1 << '\t' << sqrt(6 * s1) << '\t' << s2 << '\t'
         << sqrt(6 * s2) << '\t' << s3 << '\t' << sqrt(6 * s3) << '\n';
#endif
  }
  cout << "\n\n";

  // test cases for question 3:
  cout << "answers for question 3:-------------------------" << endl;
  cout << "combineNumber(34, 25) " << combineNumber(34, 25) << endl;
  cout << "combineNumber(1234, 56789123) " << combineNumber(1234, 56789123)
       << endl;

  // test cases for question 4:
  cout << "answers for question 4:-------------------------" << endl;
  // matrix example 1
  double a1[3][3] = {{1, 2, 3}, {4, 1, -2}, {-3, 1, 4}};
  double b1[3][3] = {{5, -1, 3}, {3, 2, 4}, {-2, 4, -2}};
  double c1[3][3];
  add(c1, a1, b1);  // c = a + b
  print(c1);

  /* should print
      6  1  6
      7  3  2
      -5 5  2
  */

  // matrix example 2
  double a2[3][3] = {{1.0, 2.5, -2.0}, {2.0, 1.3, 1.2}, {-1.2, 1.4, 3.1}};
  double b2[3][3] = {{2.0, 1.5, 1.0}, {-1.0, 2.3, 1.2}, {-1.2, 1.4, 3.1}};
  double c2[3][3];
  add(c2, a2, b2);  // c = a + b
  print(c2);

  // test cases for question 5:
  cout << "answers for question 5:-------------------------" << endl;
  quadratic(1.0, 2.0, 1.0);
  // you need to print out the two roots inside of your function
  quadratic(1.0, -4, 4.000001);
}