#include "Cuboid.h"
#include "ColorRGB.h"
#include "Primitive3D.h"
#include "Graphics3D.h"

struct Cuboid::Impl {
  real a, b, c;
  Point3D origin;
  Impl(real a, real b, real c, const Point3D& origin)
    : a(a), b(b), c(c), origin(origin) {}
};

Cuboid::Cuboid(real a, real b, real c, const Point3D& origin)
  : pimpl(new Impl(a, b, c, origin)) {}

Cuboid::~Cuboid() {
  delete pimpl;
}

void Cuboid::draw(Graphics3D *graphics) const {
  real a = pimpl->a, b = pimpl->b, c = pimpl->c;
  real x = pimpl->origin.x, y = pimpl->origin.y, z = pimpl->origin.z;
  x -= a/2; y -= b/2; z -= c/2;

  Point3D vertices[] = {
    Point3D(x, y, z),
    Point3D(x+a, y, z),
    Point3D(x+a, y, z+c),
    Point3D(x, y, z+c),
    Point3D(x, y+b, z),
    Point3D(x+a, y+b, z),
    Point3D(x+a, y+b, z+c),
    Point3D(x, y+b, z+c),
  };

  for (int n = 0; n < 8; n += 4) {
    for (int i = n; i < n + 3; ++i) {
      graphics->draw_line(vertices[i], vertices[i+1], ColorRGB::BLACK);
    }
    graphics->draw_line(vertices[n+3], vertices[n], ColorRGB::BLACK);
  }

  for (int i = 0; i < 4; ++i) {
    graphics->draw_line(vertices[i], vertices[i+4], ColorRGB::BLACK);
  }
}
