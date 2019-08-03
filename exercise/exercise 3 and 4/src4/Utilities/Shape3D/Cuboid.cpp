#include "Cuboid.h"
#include "../Primitive3D.h"
#include "../Painter3D.h"

Cuboid::Cuboid(Point3D vertices[], unsigned int color)
  : m_color(color) {
  for (int i = 0; i < 8; ++i) {
    m_vertices[i] = vertices[i];
  }
}

Cuboid::~Cuboid() {}

void Cuboid::draw(Painter3D *p, WorldInfo * /*info*/) {
  Line3D line;

  for (int n = 0; n < 8; n += 4) {
    for (int i = n; i < n + 3; ++i) {
      line.begin = m_vertices[i];
      line.end = m_vertices[i + 1];
      p->drawLine(line, m_color);
    }
    line.begin = m_vertices[n + 3];
    line.end = m_vertices[n];
    p->drawLine(line, m_color);
  }

  for (int i = 0; i < 4; ++i) {
    line.begin = m_vertices[i];
    line.end = m_vertices[i + 4];
    p->drawLine(line, m_color);
  }
}

void Cuboid::transform(Matrix4D& m) {
  for (int i = 0; i < 8; ++i) {
    m_vertices[i].transform(m);
  }
}
