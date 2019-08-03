#include "Primitive3D.h"
#include <cassert>
using namespace std;

void cross(Point3D& ret_val, Point3D& v1, Point3D& v2) {
  assert(&ret_val != &v1 && &ret_val != &v2);

  ret_val.p[0] = v1.y() * v2.z() - v2.y() * v1.z();
  ret_val.p[1] = v1.z() * v2.x() - v2.z() * v1.x();
  ret_val.p[2] = v1.x() * v2.y() - v2.x() * v1.y();
  ret_val.p[3] = 1;
}

Point3D line2Vector(Line3D& l) {
  return Point3D(l.end.x() - l.begin.x(),
                 l.end.y() - l.begin.y(),
                 l.end.z() - l.begin.z());
}