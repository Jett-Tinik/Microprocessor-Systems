#include <fstream>
#include <iostream>

#include "bitmap.hh"

using namespace std;

// colors are in hex: 8 digits representing AABBGGRR
// (transparency, Blue, Green, Red)

int main() {
  bitmap b(1024, 800, 0xFF000000);  // 0xFF000000
  b.clear(0xFF000000);

  // b.horiz_line(100, 100, 550, 0xFFFF0080);
  //  this one is my test for a single purple pixel

  b.random(500, 400, 300, 200);

  b.horiz_line(100, 400, 50, 0xFF000080);

  b.horiz_line(100, 400, 100, 0xFF0000FF);
  b.horiz_line(100, 400, 170, 0xFF0000FF);
  b.vert_line(100, 180, 110, 0xFF0000FF);
  b.vert_line(100, 180, 350, 0xFF0000FF);
  b.vert_line(100, 400, 100, 0x00FF00FF);

  b.flood_fill_allcolor(115, 110, 0xFF000000, 0xFFFFFFFF);

  b.grid(600, 500, 200, 200, 6, 6, 0xFFFF0000);

  for (uint32_t x = 200; x <= 600; x += 100)
    b.fill_rect(x, 200, 50, 50, 0xFF00FFFF);

  for (uint32_t x = 200; x <= 600; x += 100)
    b.fill_circle(x, 400, 50, 0xFF00FFFF);

  b.rect(200, 260, 50, 50, 0xFFFFFFFF);

  b.circle(200, 500, 50, 0xFFFFFFFF);
  // b.circle(200, 500, 2, 0xFFFFFFFF);
  // test circle of diameter 2

  // additional floodfill to fill in a circle
  b.flood_fill_allcolor(200, 500, 0xFF000000, 0xFFFF0000);

  // optional functions: line, wuline, load if you want to test your bonus
  // parts:

  b.line(300, 100, 430, 230, 0xFFFF0000);
  b.wuline(445, 445, 945, 545, 0xFF00FFFF);
  b.wuline(850, 645, 950, 345, 0xFFFF0080);

  b.triangle(800, 100, 900, 300, 1000, 200, 0xFF00FFFF);
  b.scatter(100, 550, 300, 200);

  b.save("test.webp");
  // b.load("Kruger2.webp");
  //  b.load("hello_world.txt");
}
