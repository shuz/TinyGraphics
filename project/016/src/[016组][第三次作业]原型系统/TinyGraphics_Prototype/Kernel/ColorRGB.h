#ifndef COLOR_RGB_INCLUDED__
#define COLOR_RGB_INCLUDED__

#include "Real.h"

#define CLAMP(c)              \
  do {                        \
    if (c > 1.0) c = 1.0;     \
    else                      \
    if (c < 0.0) c = 0.0;     \
  } while (false)

class ColorRGB {
public:
  real red, green, blue;
  
  ColorRGB()
    : red(0), green(0), blue(0) {}
  ColorRGB(real r, real g, real b)
    : red(r), green(g), blue(b) {}

  void clamp() {
    CLAMP(red);
    CLAMP(green);
    CLAMP(blue);
  }

  void scale(real sf) {
    red   *= sf;
    green *= sf;
    blue  *= sf;
  }

  ColorRGB& operator+=(const ColorRGB& rhs) {
    red   += rhs.red;
    blue  += rhs.blue;
    green += rhs.green;
  }

  ColorRGB operator+(const ColorRGB& rhs) const {
    return ColorRGB(*this) += rhs;
  }

  ColorRGB operator*=(const ColorRGB& rhs) {
    red   *= rhs.red;
    blue  *= rhs.blue;
    green *= rhs.green;
  }

  ColorRGB operator*(const ColorRGB& rhs) const {
    return ColorRGB(*this) *= rhs;
  }

  static const ColorRGB BLACK;
  static const ColorRGB WHITE;

  static const ColorRGB RED;
  static const ColorRGB YELLOW;
  static const ColorRGB GREEN;
  static const ColorRGB CYAN;
  static const ColorRGB BLUE;
  static const ColorRGB MAGENTA;
};

#undef CLAMP

#endif
