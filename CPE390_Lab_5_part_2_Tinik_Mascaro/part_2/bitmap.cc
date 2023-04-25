#include "bitmap.hh"

#include <webp/decode.h>
#include <webp/encode.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>

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
  // uses given formula to go from i=x1 to i=x2 at constant y
  for (uint32_t i = y * w + x1; i <= y * w + x2; i++) rgb[i] = color;
}

void bitmap::vert_line(uint32_t y1, uint32_t y2, uint32_t x, uint32_t color) {
  // TODO: implement this
  // uses given formula to go from i=y1 to i=y2 at constant x
  for (uint32_t i = y1 * w + x; i <= y2 * w + x; i += w) rgb[i] = color;
}

void bitmap::fill_rect(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                       uint32_t color) {
  // TODO: implement this
  // for all values of j from y0 to y0+h, create a line from x0 to x0+w at the y
  // value of j
  for (uint32_t j = 0; j <= h; j++) {
    bitmap::horiz_line(x0, x0 + w, y0 + j, color);
  }
}

void bitmap::rect(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                  uint32_t color) {
  // TODO: implement this
  // 2 horizontal lines, 2 vertical lines using the coordinates of the corners
  // of the rectangle
  bitmap::horiz_line(x0, x0 + w, y0, color);
  bitmap::horiz_line(x0, x0 + w, y0 + h, color);
  bitmap::vert_line(y0, y0 + h, x0, color);
  bitmap::vert_line(y0, y0 + h, x0 + w, color);
}

void bitmap::grid(uint32_t x0, uint32_t y0, uint32_t w, uint32_t h,
                  uint32_t divx, uint32_t divy, uint32_t color) {
  // TODO: implement this
  // outer border
  bitmap::rect(x0, y0, w, h, color);

  // divx-2 vertical dividers, summonned in multiples of w / divx away from x0
  // if divx was 3 (3 columns), summons at x0+(1/3)w and x0+(1/2)w
  for (int i = 1; i < divx; i++) {
    bitmap::vert_line(y0, y0 + h, x0 + (i * w) / divx, color);
  }

  // divy-2 vertical dividers, summonned in multiples of h / divy away from y0
  // if divy was 4 (4 rows), summons at y0+(1/4)h, y0+(2/4)h, and y0+(3/4)h
  for (int i = 1; i < divy; i++) {
    bitmap::horiz_line(x0, x0 + w, y0 + (i * h) / divy, color);
  }

  // horizontal and vertical lines that are evenly spaced
}

std::default_random_engine gen;

// https://stackoverflow.com/questions/22853349/how-to-generate-random-32bit-integers-in-c
void bitmap::random(uint32_t x0, uint32_t y0, uint32_t rw, uint32_t rh) {
  // TODO: implement this

  // for every pixel within the boundaries specified by the starting corner and
  // the dimensions of the box, set the pixel to a random color to create static
  for (uint32_t i = x0; i <= x0 + rw; i++) {
    for (uint32_t j = y0; j <= y0 + rh; j++) {
      rgb[j * w + i] = gen();
    }
  }
}

void bitmap::circle(uint32_t x, uint32_t y, uint32_t d, uint32_t color) {
  // TODO: implement this
  // sets the radius as half the diameter (double division, not int division)

  // creates an upper radius and a lower radius that are each half of a unit
  // away from the regular radius

  // normally using (i-x)^2+(j-y)^2 = r^2 for coordinates (i,j) with a center of
  // (x,y), but it would be nearly impossible for the calculation to exactly
  // equal the radius

  // therefore, just check if the calculation falls within the boundary
  // specified by the upper and lower radii

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

  // exactly the same method as regular circle, only no inner band check since
  // we want the distance to go all the way down to the center
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

  // given the end points and some test point (i,j), use Heron's formula to
  // calculate the area of the triangle specified by these 3 points

  // then use the distance from the two endpoints of the line as the base of the
  // triangle and solve for the height; this height is the distance from the
  // point (i,j) to the line specified by the endpoints

  // using Heron's formula to avoid divide by 0 that arises when using slopes

  // check if the distance from the point to the line is less than 1 for a line
  // that has a width of 1 pixel and change the color of the pixel to the
  // desired color of the line

  // for some reason, there is a bug where some pixels do not get colored, but
  // there does not seem to be any reason for any one pixel to be skipped over
  // the others since changing the line length but leaving the start point and
  // the angle changes where the blank pixel is located
  double d1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
  double d2 = 0;
  double d3 = 0;
  double s = 0;
  double A = 0;
  double h = 0;

  // figure out the left and right points
  uint32_t leftx = std::min(x1, x2);
  uint32_t rightx = std::max(x1, x2);
  uint32_t bottomy = std::min(y1, y2);
  uint32_t topy = std::max(y1, y2);

  for (int32_t i = leftx; i <= rightx; i++) {
    for (int32_t j = bottomy; j <= topy; j++) {
      //
      d2 = sqrt((i - x1) * (i - x1) + (j - y1) * (j - y1));
      d3 = sqrt((x2 - i) * (x2 - i) + (y2 - j) * (y2 - j));

      s = 0.5 * (d1 + d2 + d3);
      A = sqrt(s * (s - d1) * (s - d2) * (s - d3));
      h = 2 * A / d1;
      if (h <= 0.5) {
        rgb[i + w * j] = color;
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

  // Heron's formula method again to get distance, initializing variables
  double d1 = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

  double d2 = 0;
  double d3 = 0;
  double s = 0;
  double A = 0;
  double h = 0;

  // storage for the other color, is reset later
  uint32_t color2 = 0xFF000000;

  // split the line color into its 4 channels
  uint32_t r1 = color / (256 * 256 * 256);
  uint32_t g1 = (color / (256 * 256)) % 256;
  uint32_t b1 = (color / 256) % 256;
  uint32_t T1 = color % 256;

  uint32_t r2 = 0;  // color2 / (256 * 256 * 256);
  uint32_t g2 = 0;  //(color2 / (256 * 256)) % 256;
  uint32_t b2 = 0;  //(color2 / 256) % 256;
  uint32_t T2 = 0;  // color2 % 256;

  uint32_t r3 = 0;
  uint32_t g3 = 0;
  uint32_t b3 = 0;
  uint32_t T3 = 0;

  // new color
  uint32_t color3 = 0;

  // increased width of line from 1 pixel to 10 pixels to better see the
  // functionality
  uint32_t line_width = 10;
  double p = 1;

  // uint8_t print_item = 0;
  // figure out the left and right points
  uint32_t leftx = std::min(x1, x2);
  uint32_t rightx = std::max(x1, x2);
  uint32_t bottomy = std::min(y1, y2);
  uint32_t topy = std::max(y1, y2);
  cout << "DEBUG" << leftx << ' ' << rightx << ' ' << bottomy << ' ' << topy
       << '\n';

  for (int32_t i = leftx; i <= rightx; i++) {
    for (int32_t j = bottomy; j <= topy; j++) {
      // for each pixel, take its color and split it into each of the 4 channels
      color2 = rgb[i + w * j];

      r2 = color2 / (256 * 256 * 256);    // red
      g2 = (color2 / (256 * 256)) % 256;  // green
      b2 = (color2 / 256) % 256;          // blue
      T2 = color2 % 256;                  // Transparency

      // Heron's calculation
      d2 = sqrt((i - x1) * (i - x1) + (j - y1) * (j - y1));
      d3 = sqrt((x2 - i) * (x2 - i) + (y2 - j) * (y2 - j));

      s = 0.5 * (d1 + d2 + d3);
      A = sqrt(s * (s - d1) * (s - d2) * (s - d3));
      h = 2 * (A / d1);

      // if within the desired witdh, set the proportion of the distance within
      // the width as p and use as the interpolation proportion between the line
      // color and the current color
      if (h <= line_width) {
        p = (h + 0.0) / line_width;

        T3 = interpolate(T1, T2, p);  // Transparency
        r3 = interpolate(r1, r2, p);  // red
        g3 = interpolate(g1, g2, p);  // green
        b3 = interpolate(b1, b2, p);  // blue

        // combine the interpolated channels back into a single color also
        // prints out verificaation information
        color3 = r3 * (256 * 256 * 256) + g3 * (256 * 256) + b3 * 256 + T3;
        cout << i << " " << j << " " << p << " " << g1 << " " << g2 << " " << g3
             << '\n';
        // sets color, also has the blind spot issue from regular line
        rgb[i + w * j] = color3;
      }
    }
  }
  // test that interpolate works
  // unclear of the order of T,r,g, and b, but all are consistently set
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
  //  TODO:
  // int s = WebPGetInfo(rgb, w * h * 4, w, h, out);

  //
  cout << '\n';
  cout << "load function" << '\n';

  //
  // https://www.tutorialspoint.com/how-can-i-get-a-file-s-size-in-cplusplus
  ifstream in_file(filename, ios::binary);
  in_file.seekg(0, ios::end);
  int file_size = in_file.tellg();
  cout << "Size of the file is"
       << " " << file_size << " "
       << "bytes" << '\n';

  // provided by Professor Kruger at the end of class
  uint8_t* out = new uint8_t[file_size];
  in_file.read((char*)out, file_size);

  // used to test if .read works. Unfortunately, cannot tell when is supposed to
  // be happening with .read
  ofstream out_file("out_test.webp", ios::binary);
  out_file.write((char*)out, file_size);
  //

  // skip the header
  // https://developers.google.com/speed/webp/docs/riff_container
  // header is presumed to be 12 bytes
  uint8_t skip = 12;

  // https://developers.google.com/speed/webp/docs/api
  //  attempts to get the width and height of the input image, but the cout
  //  shows that WebPGetInfo does not work as expected
  // attempted using WebPDecodeRGBA but no luck there either
  int width = 0;
  int height = 0;

  int s = WebPGetInfo(&out[skip], file_size, &width, &height);
  // WebPDecodeRGBA
  cout << file_size << ' ' << width << ' ' << height << ' ' << s << '\n';

  // prints out the elements in the out array, but most entries are blank or
  // garbage, with no elements being from "RIFF" item in header as expected
  cout << "printing array" << '\n';
  for (int i = 0; i < 20; i++) {
    cout << "i = " << i << ' ' << out[i] << '\n';
  }

  // Unfortunately we had to stop here, as it is 2 hours before the assignment
  // closes and we are not close to finishing. However, the following steps are
  // what we would do if the functions above worked as expected:

  // w = width;
  // h = height;
  // uint8_t pixels_split = WebPGetInfo(&out[skip], file_size, &width, &height);
  // uint32_t pixels_merge[file_size];
  // for (int i = 0; i < file_size; i+=4) {
  //    uint8_t r = pixels_split[i];
  //    uint8_t g = pixels_split[i+1];
  //    uint8_t b = pixels_split[i+2];
  //    uint8_t T = pixels_split[i+3];
  //    pixels_merge[i] = r *(256*256*256) + g *(256*256) + b *256 + T3;
  // }
  // rgb = pixels_merge;
  // (do something to alter the image)
  // bitmap::save("test_out.webp");
}

// ADDITIONAL FUNCTIONS THAT WE WROTE FOR FUN

void bitmap::scatter(uint32_t x0, uint32_t y0, uint32_t rw, uint32_t rh) {
  // TODO: implement this

  // creates a rectangle with random points within it illuminated

  // max randomness is the full box
  uint32_t dots = rand() % (rw * rh);
  uint32_t color = 0x00FFFFFF;

  bitmap::rect(x0, y0, rw, rh, color);

  // for a random position, color the pixel to the specified color
  for (int i = 1; i < dots; i++) {
    int rx = rand() % rw;
    int ry = rand() % rh;
    bitmap::horiz_line(x0 + rx, x0 + rx, y0 + ry, color);
  }
}

void bitmap::triangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2,
                      int32_t x3, int32_t y3, uint32_t color) {
  // 3 lines, connecting sets of 2 points
  bitmap::line(x1, y1, x2, y2, color);
  bitmap::line(x3, y3, x2, y2, color);
  bitmap::line(x1, y1, x3, y3, color);
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



/*
ANSWERS TO DISCUSSION QUESTIONS:

1. How many bytes is the raw image specified in testbitmap.cc? The size is 1024 x 800.

There are 3,276,800 bytes in the raw image
red, green, blue, and transparency are each a byte, so its 4 bytes per pixel
1024*800 pixels
Size = 4*1024*800 bytes = 3,276,800





2. How many bytes is the .webp that you save when you have all functions written?

137,684 bytes


3.Take a .jpg and convert on the command line using convert:
      convert yourimage.jpg yourimage.webp
how much better is the compression for webp than jpeg for your image?


The compression for the webp is almost 3 times better in terms of bytes used.

Kruger.jpg is 33,968 bytes

Using the command “cwebp -q 100 Kruger.jpg -o Kruger2.webp”, Kruger2.webp is 12,562 bytes
    convert command provided did not work
    "-q 100" means quality 100, leaving this piece out results in default quality of 75 being used


*/