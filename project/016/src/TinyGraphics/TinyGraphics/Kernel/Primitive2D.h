#ifndef PRIMITIVE_2D_INCLUDED__
#define PRIMITIVE_2D_INCLUDED__

#include "Real.h"

namespace TinyGraphics {

  class IntPoint2D {
  public:
    typedef int integer;
    integer x, y;

    IntPoint2D() {
      assign(0, 0);
    }

    IntPoint2D(integer x, integer y) {
      assign(x, y);
    }

    void assign(integer x, integer y) {
      this->x = x;
      this->y = y;
    }

    bool operator==(const IntPoint2D& rhs) const {
      return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const IntPoint2D& rhs) const {
      return x != rhs.x || y != rhs.y;
    }
  };

  class Point2D {
  public:
    real x, y;

    Point2D() {
      assign(0, 0);
    }

    Point2D(real x, real y) {
      assign(x, y);
    }

    void assign(real x, real y) {
      this->x = x;
      this->y = y;
    }

    bool operator==(const Point2D& rhs) const {
      return x == rhs.x && y == rhs.y;
    }

    bool operator!=(const Point2D& rhs) const {
      return x != rhs.x || y != rhs.y;
    }
  };

}

#endif
