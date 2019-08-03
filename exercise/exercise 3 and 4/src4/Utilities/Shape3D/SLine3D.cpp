#include "SLine3D.h"
#include "../Primitive3D.h"
#include "../Painter3D.h"

SLine3D::SLine3D(Line3D& line, unsigned int color)
  : m_line(line), m_color(color) {}

SLine3D::~SLine3D() {}

void SLine3D::draw(Painter3D *p, WorldInfo * /*info*/) {
  p->drawLine(m_line, m_color);
}

void SLine3D::transform(Matrix4D& m) {
  m_line.transform(m);
}
