#ifndef TEXTURE_INCLUDED__
#define TEXTURE_INCLUDED__

#include "real.h"

namespace TinyGraphics {

  class ColorRGB;
  class Point2D;

  class Texture {
  public:
    virtual
    ~Texture() = 0;

    // get the color of the specified point,
    // ranging from (0, 0) to (1, 1) inclusive
    // return BLACK if out of range
    virtual
    ColorRGB get_color(const Point2D& point) const = 0;

  protected:
    Texture();

  private:
    Texture(const Texture&);              // not implemented
    Texture& operator=(const Texture&);   // not implemented  
  };
}

#endif
