#include "Graphics3D.h"
#include "ColorRGB.h"

Graphics3D::Graphics3D() {}
Graphics3D::~Graphics3D() {}

void Graphics3D::draw_line(const Point3D& begin, const Point3D& end) {
  draw_line(begin, end, ColorRGB::BLACK);
}
