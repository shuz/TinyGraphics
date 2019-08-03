#include "StdAfx.h"

#include "CDCGraphics2D.h"
#include "Kernel/ColorRGB.h"
#include "Kernel/Primitive2D.h"
#include "Kernel/Real.h"

#include "Utilities.h"

using namespace TinyGraphics;

static inline
int round(real x) {
  return (int) (x + 0.5);
}

struct CDCGraphics2D::Impl {
  CDC *dc;
  int width, height;

  Impl(CDC *dc) : dc(dc) {}

  int get_x(real x) {
    return round((1+x) * width) / 2;
  }

  int get_y(real y) {
    return round((1-y) * height) / 2;
  }
};

CDCGraphics2D::CDCGraphics2D(CDC *dc)
  : pimpl(new Impl(dc)) {}

CDCGraphics2D::~CDCGraphics2D() {
  delete pimpl;
}

void CDCGraphics2D::set_window_ext(int width, int height) {
  pimpl->width = width;  pimpl->height = height;
}

void CDCGraphics2D::get_window_ext(int& width, int& height) const {
  width = pimpl->width;  height = pimpl->height;
}

void CDCGraphics2D::draw_line(const Point2D& begin, const Point2D& end,
                              const ColorRGB& color) {
  COLORREF dc_color = convert_color(color);

	CPen newpen(PS_SOLID, 1, dc_color);
	CPen *oldpen = pimpl->dc->SelectObject(&newpen);

  pimpl->dc->MoveTo(pimpl->get_x(begin.x), pimpl->get_y(begin.y));
  pimpl->dc->LineTo(pimpl->get_x(end.x), pimpl->get_y(end.y));

  pimpl->dc->SelectObject(oldpen);
}

void CDCGraphics2D::draw_point(const Point2D& point, const ColorRGB& color) {
  COLORREF dc_color = convert_color(color);
  pimpl->dc->SetPixelV(
    pimpl->get_x(point.x), pimpl->get_y(point.y),
    dc_color
  );
}

void CDCGraphics2D::draw_background(const ColorRGB& color) {
  COLORREF dc_color = convert_color(color);
  CRect rect(0, 0, pimpl->width, pimpl->height);
  pimpl->dc->FillRect(rect, &CBrush(dc_color));
}

IntPoint2D CDCGraphics2D::to_pixel(const Point2D& point) const {
  return IntPoint2D(pimpl->get_x(point.x), pimpl->height - pimpl->get_y(point.y));  
}

void CDCGraphics2D::set_pixel(const IntPoint2D& point,
                              const ColorRGB& color) {
  COLORREF dc_color = convert_color(color);
  pimpl->dc->SetPixelV(point.x, pimpl->height - point.y, dc_color);
}

ColorRGB CDCGraphics2D::get_pixel(const IntPoint2D& point) const {
  COLORREF dc_color = pimpl->dc->GetPixel(point.x, pimpl->height - point.y);
  return convert_color(dc_color);
}
