#include "CDCGraphics2D.h"
#include "Kernel/ColorRGB.h"
#include "Kernel/Primitive2D.h"
#include "StdAfx.h"

struct CDCGraphics2D::Impl {
  CDC *dc;
  int width, height;
  Impl(CDC *dc) : dc(dc) {}
};

CDCGraphics2D::CDCGraphics2D(CDC *dc)
  : pimpl(new Impl(dc)) {}

CDCGraphics2D::~CDCGraphics2D() {
  delete pimpl;
}

static COLORREF convert_color(const ColorRGB& color) {
  const int COLOR_FACTOR = 0xFF;
  return RGB(color.red   * COLOR_FACTOR,
             color.green * COLOR_FACTOR,
             color.blue  * COLOR_FACTOR);
}

void CDCGraphics2D::set_window_ext(int width, int height) {
  pimpl->width = width;  pimpl->height = height;
}

void CDCGraphics2D::draw_line(const Point2D& begin, const Point2D& end,
                              const ColorRGB& color) {
  COLORREF dc_color = convert_color(color);

	CPen newpen(PS_SOLID, 1, dc_color);
	CPen *oldpen = pimpl->dc->SelectObject(&newpen);

  pimpl->dc->MoveTo((int)(begin.x * pimpl->width), (int)(begin.y * pimpl->height));
  pimpl->dc->LineTo((int)(end.x * pimpl->width),   (int)(end.y * pimpl->height));

  pimpl->dc->SelectObject(oldpen);
}

void CDCGraphics2D::draw_point(const Point2D& point, const ColorRGB& color) {
  COLORREF dc_color = convert_color(color);
  pimpl->dc->SetPixel(
    (int)(point.x * pimpl->width),
    (int)(point.y * pimpl->height),
    dc_color
  );
}
