#ifndef VIEWING_GRAPHICS_3D_INCLUDED__
#define VIEWING_GRAPHICS_3D_INCLUDED__

#include "Graphics3D.h"

class Graphics2D;
class Camera;

class ViewingGraphics3D
  : public Graphics3D {
public:
  ViewingGraphics3D(const Camera*, Graphics2D *);
  ~ViewingGraphics3D();

  void draw_line(const Point3D&, const Point3D&, const ColorRGB&);

private:
  struct Impl;
  Impl *pimpl;

  ViewingGraphics3D(const ViewingGraphics3D&);            // not implemented
  ViewingGraphics3D& operator=(const ViewingGraphics3D&); // not implemented
};

#endif
