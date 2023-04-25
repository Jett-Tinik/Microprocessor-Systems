#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

int main() {
  int secret;
  int guess;
  int count = 0;

  srand(time(NULL));
  secret = rand() % 10 + 1;

  while (count < 3) {
    cout << "Guess?" << endl;
    cin >> guess;
    if (guess == secret) {
      cout << "Yay" << endl;
      exit(0);
    }
    count++;
  }
  cout << secret << endl;
}