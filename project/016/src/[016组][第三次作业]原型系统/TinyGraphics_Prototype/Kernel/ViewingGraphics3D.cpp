#include "ViewingGraphics3D.h"

#include "Graphics2D.h"
#include "Camera.h"
#include "Primitive2D.h"
#include "Primitive3D.h"
#include "Matrix4D.h"
#include "Vector4D.h"

struct ViewingGraphics3D::Impl {
  const Camera *camera;
  Graphics2D *graphics_2d;

  Impl(const Camera* c, Graphics2D *g)
    : camera(c), graphics_2d(g) {}
};

static Point2D project(const Point3D& point, const Matrix4D& mat) {
  Vector4D vec(point.x, point.y, point.z, 1);
  vec *= mat;
  return Point2D(vec(0) / vec(3), vec(1) / vec(3));
}

ViewingGraphics3D::ViewingGraphics3D(const Camera* c, Graphics2D *g)
  : pimpl(new Impl(c, g)) {}

ViewingGraphics3D::~ViewingGraphics3D() {
  delete pimpl;
}

void ViewingGraphics3D::draw_line(const Point3D& begin, const Point3D& end,
                                  const ColorRGB& color) {
  Matrix4D n = pimpl->camera->get_normalization_matrix();
  Matrix4D p = pimpl->camera->get_projection_matrix();
  Matrix4D mat = n*p;
  pimpl->graphics_2d->draw_line(project(begin, mat), project(end, mat), color);
}
