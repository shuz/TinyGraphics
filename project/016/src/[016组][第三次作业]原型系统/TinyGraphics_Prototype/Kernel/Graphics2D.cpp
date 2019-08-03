#include "Graphics2D.h"
#include "ColorRGB.h"

Graphics2D::Graphics2D() {}
Graphics2D::~Graphics2D() {}

void Graphics2D::draw_line(const Point2D& begin, const Point2D& end) {
  draw_line(begin, end, ColorRGB::BLACK);
}
