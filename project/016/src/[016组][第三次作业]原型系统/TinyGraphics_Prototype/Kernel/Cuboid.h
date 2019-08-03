#ifndef CUBOID_INCLUDED__
#define CUBOID_INCLUDED__

#include "Object3D.h"
#include "Real.h"

class Point3D;

class Cuboid : public Object3D {
public:
  Cuboid(real a, real b, real c, const Point3D& origin);
  ~Cuboid();

  void draw(Graphics3D *graphics) const;

protected:
  Cuboid();

private:
  Cuboid(const Cuboid&);              // not implemented
  Cuboid& operator=(const Cuboid&);   // not implemented

private:
  struct Impl;
  Impl *pimpl;
};

#endif
