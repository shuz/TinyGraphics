#ifndef PRIMITIVE_3D_INCLUDED__
#define PRIMITIVE_3D_INCLUDED__

#include "Matrix4D.h"

struct Point3D {
  Vector4D p;   // homogeneous coordinate
  double x() { return p[0]/p[3]; }
  double y() { return p[1]/p[3]; }
  double z() { return p[2]/p[3]; }

  Point3D() {}
  Point3D(double x, double y, double z, double w = 1)
    : p(x, y, z, w) {}

  void transform(Matrix4D& m) {
    p = p * m;
  }

  void assign(double x, double y, double z, double w = 1) {
    p.assign(x, y, z, w);
  }
};

inline
bool operator==(Point3D& p1, Point3D& p2) {
  return p1.p == p2.p;
}

inline
bool operator!=(Point3D& p1, Point3D& p2) {
  return p1.p != p2.p;
}

struct Line3D {
  Point3D begin, end;
  
  Line3D() {}
  Line3D(Point3D b, Point3D e)
    : begin(b), end(e) {}

  void transform(Matrix4D& m) {
    begin.p = begin.p * m;
    end.p = end.p * m;
  }

  void assign(Point3D b, Point3D e) {
    begin = b;  end = e;
  }
};

// postfix cross product operator
// produces the cross product treating v1 and v2 as 3D vectors
// from the origin.
//
// note: ret_val in multiply can't be any of its operands
//       or you'll probably get the wrong answer!
void cross(Point3D& ret_val, Point3D& v1, Point3D& v2);

inline
Point3D operator*(Point3D& v1, Point3D& v2) {
  Point3D p;
  cross(p, v1, v2);
  return p;
}

// convert a line to a vector from origin
Point3D line2Vector(Line3D& l);

inline
bool operator==(Line3D& l1, Line3D& l2) {
  return l1.begin == l2.begin &&
         l1.end == l2.end;
}

inline
bool operator!=(Line3D& l1, Line3D& l2) {
  return !(l1 == l2);
}

#endif
