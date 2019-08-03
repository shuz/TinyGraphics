#include "Rect3D.h"
#include "../Primitive3D.h"
#include "../Painter3D.h"


Rect3D::Rect3D(Point3D vertices[], unsigned int color)
  : m_color(color) {
  for (int i = 0; i < 4; ++i) {
    m_vertices[i] = vertices[i];
  }
}

Rect3D::~Rect3D() {}

void Rect3D::draw(Painter3D *p, WorldInfo * /*info*/) {
  Line3D line;
  for (int i = 0; i < 3; ++i) {
    line.begin = m_vertices[i];
    line.end = m_vertices[i + 1];
    p->drawLine(line, m_color);
  }
  line.begin = m_vertices[3];
  line.end = m_vertices[0];
  p->drawLine(line, m_color);
}

void Rect3D::transform(Matrix4D& m) {
  for (int i = 0; i < 4; ++i) {
    m_vertices[i].transform(m);
  }
}
