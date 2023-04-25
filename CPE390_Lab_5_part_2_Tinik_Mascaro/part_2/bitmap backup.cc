#include <webp/decode.h>
#include <webp/encode.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

#include "bitmap.hh"
#include "webp/mux_types.h"
using namespace std;

/*

        AUTHOR: Jett Tinik and Philip Mascaro
        CITE:
          https://www.cplusplus.com/reference/cstdlib/rand/
          https://www.tutorialspoint.com/how-can-i-get-a-file-s-size-in-cplusplus
          https://stackoverflow.com/questions/28231580/error-decoding-animated-webp-ios/28472740#28472740
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

  for (uint32_t i = x0; i <= x0 + rw; i++) {
    for (uint32_t j = y0; j <= y0 + rh; j++) {
      rgb[j * w + i] = gen();
    }
  }
}

/*
// was told by TA to add this one as well
void bitmap::random2(uint32_t x0, uint32_t y0, uint32_t rw, uint32_t rh) {
  // TODO: implement this

  // creates a rectangle with random points illuminated

  uint32_t dots = rand() % (rw * rh);
  uint32_t color = 0x00FFFFFF;

  bitmap::rect(x0, y0, rw, rh, color);

  for (int i = 1; i < dots; i++) {
    int rx = rand() % rw;
    int ry = rand() % rh;
    bitmap::horiz_line(x0 + rx, x0 + rx, y0 + ry, color);
  }
}
*/

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
        cout << "color";
      }
      if (h <= 3) {
        cout << h << '\n';
      }
    }
  }
}

// https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm
//  extra credit +50

// wrote this to use in wuline
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

  uint32_t T2 = 0;  // color2 / (256 * 256 * 256);
  uint32_t r2 = 0;  //(color2 / (256 * 256)) % 256;
  uint32_t g2 = 0;  //(color2 / 256) % 256;
  uint32_t b2 = 0;  // color2 % 256;

  uint32_t T3 = 0;
  uint32_t r3 = 0;
  uint32_t g3 = 0;
  uint32_t b3 = 0;

  uint32_t color3 = 0;

  // increased width of line from 1 pixel to 10 pixels to better see the
  // functionality
  uint32_t line_width = 10;
  double p = 1;

  // uint8_t print_item = 0;

  for (int32_t i = x1; i <= x2; i++) {
    for (int32_t j = y1; j <= y2; j++) {
      // space
      color2 = rgb[i + w * j];

      T2 = color2 / (256 * 256 * 256);
      r2 = (color2 / (256 * 256)) % 256;
      g2 = (color2 / 256) % 256;
      b2 = color2 % 256;

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

        // color3 = ((T3 * 256 + r3) * 256 + g3) * 256 + b3;
        color3 = T3 * (256 * 256 * 256) + r3 * (256 * 256) + g3 * 256 + b3;
        cout << i << " " << j << " " << p << " " << g1 << " " << g2 << " " << g3
             << '\n';
        bitmap::horiz_line(i, i, j, color3);
      }
    }
  }
  cout << interpolate(255, 0, 0.5) << '\n';
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
  // uint8_t* out;
  //  TODO:
  // int s = WebPGetInfo(rgb, w * h * 4, w, h, out);
  cout << '\n';
  cout << "load function" << '\n';
  // https://www.tutorialspoint.com/how-can-i-get-a-file-s-size-in-cplusplus
  ifstream in_file(filename, ios::binary);
  in_file.seekg(0, ios::end);
  int file_size = in_file.tellg();
  cout << "Size of the file is"
       << " " << file_size << " "
       << "bytes" << '\n';

  uint8_t* out = new uint8_t[file_size];  // const
  in_file.read((char*)out, file_size);    //
  /*uint8_t* out = new uint8_t[file_size];  // const
  in_file.read((char*)out, file_size); */

  // skip the header

  ofstream out_file("out_test.webp", ios::binary);
  out_file.write((char*)out, file_size);

  /*


    // https://developers.google.com/speed/webp/docs/riff_container
    uint8_t skip = 12;
    const uint8_t data_location = out[skip];
    const uint8_t data_start = out[0];

    //
    https://stackoverflow.com/questions/28231580/error-decoding-animated-webp-ios/28472740#28472740
    // WebPData image_data;

    // rgb =
    // cout << w << ' ' << h << '\n';
    int width = 0;
    int height = 0;

    int s =
        WebPGetInfo(out[0], file_size, &width, &height);  //(uint8_t const*)(&(
    ))
    //  uint8_t* s = WebPDecodeRGBA(&data_location, file_size, &width, &height);
    cout << file_size << ' ' << width << ' ' << height << ' ' << s << '\n';

    // WebPDecodeRGBA(
    // cout << rgb[0] << '\n';
    // bitmap::save("test_out.webp");

    */

  cout << "printing array" << '\n';
  for (int i = 0; i < 20; i++) {
    cout << "i = " << i << ' ' << out[i] << '\n';
  }
}

//

//

//

// lab 6
void bitmap::flood_fill_allcolor(uint32_t x, uint32_t y, uint32_t findcolor,
                                 uint32_t replace_color) {
  if (rgb[x + w * y] == findcolor) {
    rgb[x + w * y] = replace_color;
    if (!(x <= 0)) {
      flood_fill_allcolor(x - 1, y, findcolor, replace_color);
    }
    if (!(x > w)) {
      flood_fill_allcolor(x + 1, y, findcolor, replace_color);
    }
    if (!(y <= 0)) {
      flood_fill_allcolor(x, y - 1, findcolor, replace_color);
    }
    if (!(y > h)) {
      flood_fill_allcolor(x, y + 1, findcolor, replace_color);
    }
  }
}
