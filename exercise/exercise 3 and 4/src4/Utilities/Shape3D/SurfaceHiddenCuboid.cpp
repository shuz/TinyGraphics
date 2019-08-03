#include "SurfaceHiddenCuboid.h"

#include "../Primitive3D.h"
#include "../Painter3D.h"
#include "../Transform.h"

#include <limits>
#include <cassert>
using namespace std;

// find the point which is invisible
int findInvisible(Point3D vertices[8], Point3D& viewDir, Matrix4D& tranformer) {
  assert(viewDir.p[3] == 1);
  int max = 0;
  double max_dist = - numeric_limits<double>::max();
  for (int i = 0; i < 8; ++i) {
    assert(vertices[i].p[3] == 1);

    // transform, and then dot-product
    double dist = (vertices[i].p * tranformer) * viewDir.p;
    if (dist > max_dist) {
      max_dist = dist;
      max = i;
    }
  }
  return max;
}


SurfaceHiddenCuboid::SurfaceHiddenCuboid(Point3D vertices[], unsigned int color)
  : m_color(color) {
  for (int i = 0; i < 8; ++i) {
    m_vertices[i] = vertices[i];
  }
}

SurfaceHiddenCuboid::~SurfaceHiddenCuboid() {}

void SurfaceHiddenCuboid::draw(Painter3D *p, WorldInfo *info) {
  Line3D line;

  int inv = findInvisible(m_vertices, info->viewDirection, info->transformer);

  for (int n = 0; n < 8; n += 4) {
    for (int i = n; i < n + 3; ++i) {
      if (i == inv || i+1 == inv)
        continue;   // skip invisible lines

      line.begin = m_vertices[i];
      line.end = m_vertices[i + 1];
      p->drawLine(line, m_color);
    }
    if (n == inv || n+3 == inv)
      continue;   // skip invisible lines    

    line.begin = m_vertices[n + 3];
    line.end = m_vertices[n];
    p->drawLine(line, m_color);
  }

  for (int i = 0; i < 4; ++i) {
    if (i == inv || i+4 == inv)
      continue;   // skip invisible lines
    line.begin = m_vertices[i];
    line.end = m_vertices[i + 4];
    p->drawLine(line, m_color);
  }
}

void SurfaceHiddenCuboid::transform(Matrix4D& m) {
  for (int i = 0; i < 8; ++i) {
    m_vertices[i].transform(m);
  }
}
