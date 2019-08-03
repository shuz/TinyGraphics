#ifndef PRIMITIVE_3D_INCLUDED__
#define PRIMITIVE_3D_INCLUDED__

#include "Real.h"
#include "Vector3D.h"

class Point3D {
public:
  real x, y, z;

  Point3D() {}
  Point3D(real x, real y, real z) {
    assign(x, y, z);
  }

  void assign(real x, real y, real z) {
    this->x = x;
    this->y = y;
    this->z = z;
  }
};

class Line3D {
public:
  Point3D begin, end;
  
  Line3D() {}
  Line3D(Point3D b, Point3D e)
    : begin(b), end(e) {}

  void assign(Point3D b, Point3D e) {
    begin = b;  end = e;
  }
};

#endif
