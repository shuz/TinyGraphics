#ifndef Z_BUFFER_INCLUDED__
#define Z_BUFFER_INCLUDED__

#include "Real.h"
#include "Graphics2D.h"

namespace TinyGraphics {

  class ZBuffer {
  public:
    ZBuffer(Graphics2D *graphics) {
      graphics_2d = graphics;
      x_ext = y_ext = 0;
      size = 0;
      zbuffer = 0;
    }

    // create a z-buffer buffering a window
    // range from (0, 0) to (x, y) inclusive
    ZBuffer(Graphics2D *graphics, int x, int y) {
      graphics_2d = graphics;
      zbuffer = 0;
      create(x, y);
    }

    ~ZBuffer() {
      delete [] zbuffer;
    }

    // create a z-buffer buffering a window
    // range from (0, 0) to (x, y) inclusive
    // delete old buffer and create a new one
    void create(int x, int y) {
      delete [] zbuffer;
      x_ext = x+1;  y_ext = y+1;
      size = x_ext * y_ext;
      zbuffer = (size == 0) ? 0 : new real[size];
      clear();
    }

    real& operator() (int x, int y) {
      return zbuffer[x + y*x_ext];
    }

    real operator() (int x, int y) const {
      return zbuffer[x + y*x_ext];
    }

    int get_pos(int x, int y) const {
      return x + y*x_ext;
    }

    real& operator[] (int pos) {
      return zbuffer[pos];
    }

    real operator[] (int pos) const {
      return zbuffer[pos];
    }

    // set the pixel if point (x, y) in the screen and 
    // zbuffer(x, y) <= z < 0
    void set_pixel(int x, int y, real z, const ColorRGB& color) {
      if (0 <= x && x < x_ext && 0 <= y && y < y_ext) {
        int pos = get_pos(x, y);
        if (zbuffer[pos] <= z && z < 0) {
          graphics_2d->set_pixel(IntPoint2D(x, y), color);
          zbuffer[pos] = z;
        }
      }
    }

    void clear() {
      int size = x_ext * y_ext;
      for (int i = 0; i < size; ++i) {
        zbuffer[i] = -std::numeric_limits<real>::infinity();
      }
    }

  private:
    int x_ext, y_ext;
    int size;
    real *zbuffer;
    Graphics2D *graphics_2d;
  };
}

#endif
