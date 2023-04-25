#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

using namespace std;

// return the integer sum of the array x

int sum(const int x[], int len) {
  int sum = 0;
  for (int i = 0; i < len; i++) {
    sum += x[i];
  }
  return sum;
}

double mean(const int x[], int len) {
  double sum = 0;
  for (int i = 0; i < len; i++) {
    sum += x[i];
  }
  return sum / len;
}

// compute teh dot product sum(a[i]*b[i])
double dot(const double a[], const double b[], int len) {
  double sum = 0;
  double totsum = 0;
  for (int i = 0; i < len; i++) {
    sum = a[i] * b[i];
    totsum = totsum + sum;
    // could do sum += a[i]*b[i]
  }
  return totsum;
}

void stats(const double x[], uint32_t len, double& mean, double& min,
           double& max) {
  double sum = x[0];               // 27
  double tempmin = x[0];           // 1
  double tempmax = x[0];           // 8
  for (int i = 1; i < len; i++) {  // 4
    sum += x[i];                   // 27
    if (x[i] < tempmin) tempmin = x[i];
    if (x[i] > tempmax) tempmax = x[i];
  }
  mean = sum / len;  // write to memory
  min = tempmin;     // write to memory
  max = tempmax;
}

double fact(int n) {
  if (n == 0) {
    return 1;
  }
  return (n)*fact(n - 1);
  // n = 0 return 1
  // n = 1
}

int main() {
  int a[] = {1, 2, 3, 4};
  int z = sum(a, 4);  // 10

  double m = mean(a, 4);  // 2.5

  double x[] = {1, 2, 3};
  double y[] = {3, 4, 6};
  double d = dot(x, y, 3);  // 1*3+2*4+3*6

  double mean, min, max;
  stats(x, 3, mean, min, max);

  // write a recursive function to compute
  cout << fact(100);
}