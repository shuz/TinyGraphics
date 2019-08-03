#ifndef PRIMITIVE_2D_INCLUDED__
#define PRIMITIVE_2D_INCLUDED__

#include "Real.h"

class Point2D {
public:
  real x, y;

  Point2D() {}
  Point2D(real x, real y) {
    assign(x, y);
  }

  void assign(real x, real y) {
    this->x = x;
    this->y = y;
  }
};

class Line2D {
public:
  Point2D begin, end;
  
  Line2D() {}
  Line2D(Point2D b, Point2D e)
    : begin(b), end(e) {}

  void assign(Point2D b, Point2D e) {
    begin = b;  end = e;
  }
};

#endif
