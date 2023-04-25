#pragma once
#include <cmath>
#include <iostream>
using namespace std;

/*
        AUTHOR: Jett Tinik and Philip Mascaro
        I pledge my Honor that I have abided by the Stevens Honor System.
*/



class vec3d {
 public:
  double x, y, z;  // every 3d vector has x y z
                   // TODO:

  vec3d(double myX, double myY, double myZ) : x(myX), y(myY), z(myZ) {}

  friend vec3d operator+(const vec3d& a, const vec3d& b) {
    return vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
  }

  vec3d add(vec3d b) const {
    return vec3d(this->x + b.x, this->y + b.y, this->z + b.z);
  }

  friend vec3d add(const vec3d& a, const vec3d& b) {
    return vec3d(a.x + b.x, a.y + b.y, a.z + b.z);
  }

  friend double dist(const vec3d& a, const vec3d& b) {
    double x_piece = (a.x - b.x) * (a.x - b.x);
    double y_piece = (a.y - b.y) * (a.y - b.y);
    double z_piece = (a.z - b.z) * (a.z - b.z);
    return sqrt(x_piece + y_piece + z_piece);
  }

  double mag() const {
    double x_piece = (this->x) * (this->x);
    double y_piece = (this->y) * (this->y);
    double z_piece = (this->z) * (this->z);
    return sqrt(x_piece + y_piece + z_piece);
  }

  friend std::ostream& operator<<(std::ostream& s, const vec3d& f) {
    s << '<' << f.x << ", " << f.y << ", " << f.z << ">" << '\n';
  }
};
