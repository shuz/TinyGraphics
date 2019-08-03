#include "Shadow.h"

#include "../Painter3D.h"
#include "../Shape3D.h"

// decorator that performs a projection before drawing
struct ShadowPainter : Painter3D {
public:
  ShadowPainter(Painter3D *painter, Matrix4D& proj, unsigned int color)
    : m_painter(painter), m_proj(proj), m_color(color) {}

  ~ShadowPainter() {}

  void drawLine(Line3D& line, unsigned int color = 0) {
    Line3D copyLine(line);
    copyLine.transform(m_proj);
    m_painter->drawLine(copyLine, m_color);     // draw with Shadow's color
  }

  void drawPixel(Point3D& point, unsigned int color = 0) {
    Point3D copyPoint(point);
    copyPoint.transform(m_proj);
    m_painter->drawPixel(copyPoint, m_color);   // draw with Shadow's color
  }

private:
  Painter3D *m_painter;
  Matrix4D& m_proj;
  unsigned int m_color;
};

Shadow::Shadow(Shape3D *shape, Matrix4D& proj,
               Point3D& viewDir, unsigned int color)
  : m_shape(shape), m_proj(proj),
    m_color(color), m_viewDir(viewDir) {}

Shadow::~Shadow() {}

void Shadow::draw(Painter3D *p, WorldInfo *info) {
  Matrix4D m = info->transformer * m_proj;
  ShadowPainter painter(p, m, m_color);

  WorldInfo shadowInfo(info->transformer, m_viewDir);

  m_shape->draw(&painter, &shadowInfo);
}

void Shadow::transform(Matrix4D& m) {
  // IGNORE the transform request
}
