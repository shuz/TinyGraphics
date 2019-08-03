#include "SPoint3D.h"
#include "../Primitive3D.h"
#include "../Painter3D.h"

SPoint3D::SPoint3D(Point3D& point, unsigned int color)
  : m_point(point), m_color(color) {}

SPoint3D::~SPoint3D() {}

void SPoint3D::draw(Painter3D *p, WorldInfo * /*info*/) {
  p->drawPixel(m_point, m_color);
}

void SPoint3D::transform(Matrix4D& m) {
  m_point.transform(m);
}
