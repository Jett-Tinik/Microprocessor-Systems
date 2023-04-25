#include <webp/decode.h>
#include <webp/encode.h>

#include <fstream>
#include <iostream>
#include <random>

#include "bitmap.hh"
using namespace std;
/*

        AUTHOR: Jett Tinik and Philip Mascaro
        CITE: https://www.cplusplus.com/reference/cstdlib/rand/
        I pledge my Honor that I have abided by the Stevens Honor System.
*/

/*
        In order to compile you will need to install libwebp, a new graphics
        standard from google. Most image programs won't yet work with webp,
        which is better compression than jpeg in general.

        In order to install under msys2:
        https://packages.msys2.org/package/mingw-w64-x86_64-libwebp

        In order to access a particular element of this bitmap (x,y) use the
        following equation point(x,y) does this

        y*w + x

        this works because the first point is 0*w+0 = 0, the second would be
   0*w+1

        one row down would be 1*w + 0
 */

bitmap::bitmap(uint32_t w, uint32_t h, uint32_t color)
    : w(w), h(h), rgb(new uint32_t[w * h]) {
  for (uint32_t i = 0; i < w * h; i++) rgb[i] = color;
}

bitmap::~bitmap() { delete[] rgb; }

void bitmap::clear(uint32_t color) {
  for (uint32_t i = 0; i < w * h; i++) rgb[i] = color;
}

void bitmap::horiz_line(uint32_t x1, uint32_t x2, uint32_t y, uint32_t color) {
  // TODO: implement this
  for (uint32_t i = y * w + x1; i <= y * w + x2; i++) rgb[i] = color;
}

void bitmap::vert_line(uint32_t y1, uint32_t y2, uint32_t x, uint32_t color) {
  // TODO: implement this
  for (uint32_t i = y1 * w + x; i <= y2 * w + x; i += w) rgb[i] = color;
}

void bitmap::fill_rect(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                       uint32_t color) {
  // TODO: implement this

  for (uint32_t j = 0; j <= h; j++) {
    bitmap::horiz_line(x0, x0 + w, y0 + j, color);
  }
}

void bitmap::rect(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                  uint32_t color) {
  // TODO: implement this
  // 2 horizontal lines, 2 vertical lines
  bitmap::horiz_line(x0, x0 + w, y0, color);
  bitmap::horiz_line(x0, x0 + w, y0 + h, color);
  bitmap::vert_line(y0, y0 + h, x0, color);
  bitmap::vert_line(y0, y0 + h, x0 + w, color);
}

void bitmap::grid(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                  uint32_t divx, uint32_t divy, uint32_t color) {
  // TODO: implement this
  bitmap::rect(x0, y0, w, h, color);
  for (int i = 1; i < divx; i++) {
    bitmap::vert_line(y0, y0 + h, x0 + (i * w) / divx, color);
  }
  for (int i = 1; i < divy; i++) {
    bitmap::horiz_line(x0, x0 + w, y0 + (i * h) / divy, color);
  }

  // horizontal and vertical lines that are evenly spaced
}

std::default_random_engine gen;

// https://stackoverflow.com/questions/22853349/how-to-generate-random-32bit-integers-in-c
void bitmap::random(uint32_t x0, uint32_t y0, uint32_t rw, uint32_t rh) {
  // TODO: implement this

  uint32_t dots = rand() % (rw * rh);
  uint32_t color = 0x00FFFFFF;

  bitmap::rect(x0, y0, rw, rh, color);
  for (int i = 1; i < dots; i++) {
    int rx = rand() % rw;
    int ry = rand() % rh;
    bitmap::horiz_line(x0 + rx, x0 + rx, y0 + ry, color);
  }
}

void bitmap::circle(uint32_t x, uint32_t y, uint32_t d, uint32_t color) {
  // TODO: implement this
  double r = d / 2;

  double inner_r = r - 0.5;
  double ri2 = inner_r * inner_r;

  double outer_r = r + 0.5;
  double ro2 = outer_r * outer_r;

  double test_calc = 0;

  for (int i = x - d; i < x + d; i++) {
    for (int j = y - d; j < y + d; j++) {
      test_calc = ((i - x) * (i - x)) + ((j - y) * (j - y));
      if (ro2 > test_calc) {
        if (ri2 < test_calc) {
          bitmap::horiz_line(i, i, j, color);
        }
      }
    }
  }
}

// https://stackoverflow.com/questions/1201200/fast-algorithm-for-drawing-filled-circles
void bitmap::fill_circle(uint32_t x0, uint32_t y0, uint32_t d, uint32_t color) {
  // TODO: implement this

  double r = d / 2;

  double outer_r = r + 0.5;
  double ro2 = outer_r * outer_r;

  double test_calc = 0;

  for (int i = x0 - d; i < x0 + d; i++) {
    for (int j = y0 - d; j < y0 + d; j++) {
      test_calc = ((i - x0) * (i - x0)) + ((j - y0) * (j - y0));
      if (ro2 > test_calc) {
        bitmap::horiz_line(i, i, j, color);
      }
    }
  }
}

// https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
// extra credit +50
void bitmap::line(int32_t x1, int32_t y1, int32_t x2, int32_t y2,
                  uint32_t color) {
  // TODO: optional for +50

  double d1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  double d2 = 0;
  double d3 = 0;
  double s = 0;
  double A = 0;
  double h = 0;

  for (int32_t i = x1; i <= x2; i++) {
    for (int32_t j = y1; j <= y2; j++) {
      // space
      d2 = sqrt((i - x2) * (i - x2) + (j - y2) * (j - y2));
      d3 = sqrt((x1 - i) * (x1 - i) + (y1 - j) * (y1 - j));

      s = 0.5 * (d1 + d2 + d3);
      A = sqrt(s * (s - d1) * (s - d2) * (s - d3));
      h = 2 * A / d1;
      if (h <= 0.5) {
        bitmap::horiz_line(i, i, j, color);
      }
    }
  }
}

// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
//  extra credit +50
uint32_t interpolate(uint32_t left, uint32_t right, double prop) {
  double interp = (1 - prop) * left + prop * right;
  double to_round = interp + 0.5;
  uint32_t rounded = (uint32_t)to_round;
  return rounded;
}

void bitmap::wuline(uint32_t x1, uint32_t y1, uint32_t x2, uint32_t y2,
                    uint32_t color) {
  // TODO: optional for +50
  double d1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

  double d2 = 0;
  double d3 = 0;
  double s = 0;
  double A = 0;
  double h = 0;

  uint32_t color2 = 0xFF000000;

  uint32_t T1 = color / (256 * 256 * 256);
  uint32_t r1 = (color / (256 * 256)) % 256;
  uint32_t g1 = (color / 256) % 256;
  uint32_t b1 = color % 256;

  uint32_t T2 = color2 / (256 * 256 * 256);
  uint32_t r2 = (color2 / (256 * 256)) % 256;
  uint32_t g2 = (color2 / 256) % 256;
  uint32_t b2 = color2 % 256;

  uint32_t T3 = 0;
  uint32_t r3 = 0;
  uint32_t g3 = 0;
  uint32_t b3 = 0;

  uint32_t color3 = 0;

  uint32_t line_width = 1;
  double p = 1;

  // uint8_t print_item = 0;

  for (int32_t i = x1; i <= x2; i++) {
    for (int32_t j = y1; j <= y2; j++) {
      // space
      d2 = sqrt((i - x2) * (i - x2) + (j - y2) * (j - y2));
      d3 = sqrt((x1 - i) * (x1 - i) + (y1 - j) * (y1 - j));

      s = 0.5 * (d1 + d2 + d3);
      A = sqrt(s * (s - d1) * (s - d2) * (s - d3));
      h = 2 * (A / d1);

      if (h <= line_width) {
        p = (h + 0.0) / line_width;

        T3 = interpolate(T1, T2, p);
        r3 = interpolate(r1, r2, p);
        g3 = interpolate(g1, g2, p);
        b3 = interpolate(b1, b2, p);

        color3 = T3 * (256 * 256 * 256) + r3 * (256 * 256) + g3 * 256 + b3;

        bitmap::horiz_line(i, i, j, color3);
      }
    }
  }
}

void bitmap::save(const char filename[]) {
  uint8_t* out;
  size_t s = WebPEncodeRGBA((uint8_t*)rgb, w, h, 4 * w, 100, &out);
  ofstream f(filename, ios::binary);
  f.write((char*)out, s);
  WebPFree(out);
}

// not required for this assignment but +50 if you look it up and do it
//  but if you do, test it by loading in a picture, modify, and save it out
void bitmap::load(const char filename[]) {
  uint8_t* out;
  // TODO:
  //	int s= WebPGetInfo(rgb, w*h*4, w, h, out);
}
