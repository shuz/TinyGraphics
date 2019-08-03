#ifndef PAINTER_3D_INCLUDED__
#define PAINTER_3D_INCLUDED__

struct Line3D;
struct Point3D;
class Matrix4D;
// note: since Line3D and Point3D don't take the const semantic,
//       all Line3D& and Point3D& here means const refrence passing,
//       with value passing semantic.

class Painter3D {
public:
  Painter3D();
  virtual ~Painter3D() = 0;

  virtual void drawLine(Line3D& line, unsigned int color = 0) = 0;
  virtual void drawPixel(Point3D& point, unsigned int color = 0) = 0;
};

#endif
