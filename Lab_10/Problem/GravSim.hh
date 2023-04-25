#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <cmath>
#include <cstring>
#include <vector>

#include "Vec3d.hh"

constexpr double G = 6.67408e-11;

class Body {
 private:
  char name[16];
  double m;   // mass of the body
  double Gm;  // precomputed G*m for speed
  Vec3d pos;
  Vec3d v;
  Vec3d a;
  friend class GravSim;

 public:
  Body(const char name[16], const char orbits[16], double m, double x, double y,
       double z, double vx, double vy, double vz);
  inline friend std::ostream& operator<<(std::ostream& s, const Body& b);
  inline Vec3d gravAccel(const Body& b) const;
};

class GravSim {
 public:
 private:
  double t;
  std::vector<Body> bodies;

 public:
  GravSim(const char filename[]);
  void timestep(double dt);
  void forward(uint32_t n, double dt);
  inline friend std::ostream& operator<<(std::ostream& s, const GravSim& sim);
};

// same speed whe  we try to merge, hh for vec looked into cc, but Grav.hh
// already had the library to see
