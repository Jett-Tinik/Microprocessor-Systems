#include <cmath>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

// https://www.cplusplus.com/reference/fstream/ifstream/
// https://www.cplusplus.com/reference/string/stod/
// https://www.cplusplus.com/reference/string/string/substr/
// https://stackoverflow.com/questions/45387284/how-to-put-a-new-line-inside-a-string-in-c/
// https://www.cplusplus.com/reference/string/string/getline/
// https://www.sciencedirect.com/topics/computer-science/buffered-switch
// https://www.youtube.com/watch?v=lc8aTECbVuk

void read_points(string filename) {
  double x_o = 0, y_o = 0, z_o = 0;

  ifstream coordinates_file(filename);

  int num = 0;
  double x = 0, y = 0, z = 0, dis = 0, buffer = 0;
  string line, end;
  string::size_type s_a;
  string::size_type s_b;

  if (coordinates_file.is_open()) {
    while (getline(coordinates_file, line)) {
      // remember & fetches location
      x = stod(line, &s_a);
      y = stod(line.substr(s_a));
      // now switch to z
      end = line.substr(s_a);
      buffer = stod(end, &s_b);
      z = stod(end.substr(s_b));
      // solve
      dis = sqrt(((x - x_o) * (x - x_o)) + ((y - y_o) * (y - y_o)) +
                 ((z - z_o) * (z - z_o)));
      // read out
      cout << "Distance from x coordinate" << num
           << "Distance from y coordinate" << num
           << "Distance from z coordinate" << num << "Distance from (0,0,0)"
           << dis << '\n';
    }
    coordinates_file.close();
  }
}

int main() {
  read_points("points.dat");
  return 0;
}
