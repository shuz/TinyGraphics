#ifndef RAY_INCLUDED__
#define RAY_INCLUDED__

#include "Primitive3D.h"
#include "ColorRGB.h"

namespace TinyGraphics {

  class Ray {
  public:
    Ray() {}
    Ray(const Point3D& p1, const Point3D& p2)
      : origin(p1), direction(p2-p1) {
      direction.normalize();
    }

    Point3D point_at(real dist) const {
      return origin + direction * dist;
    }

    void transform(const Matrix4D& mat) {
      origin.transform(mat);
      direction.transform(mat);
      direction.normalize();
    }

    Point3D origin;
    Vector3D direction;       // assumed to be unit vector
    ColorRGB color;
  };
}

#endif
