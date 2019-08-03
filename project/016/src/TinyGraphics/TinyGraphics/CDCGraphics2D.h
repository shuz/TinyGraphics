#ifndef CDC_GRAPHICS_2D_INCLUDED__
#define CDC_GRAPHICS_2D_INCLUDED__

#include "Kernel/Graphics2D.h"

using namespace TinyGraphics;

class CDCGraphics2D : public Graphics2D {
public:
  CDCGraphics2D(CDC *dc);
  ~CDCGraphics2D();

  void set_window_ext(int width, int height);
  void get_window_ext(int& width, int& height) const;

  void draw_line (const Point2D&, const Point2D&,  const ColorRGB&);
  void draw_point(const Point2D&, const ColorRGB&);
  void draw_background(const ColorRGB&);

  void set_pixel(const IntPoint2D&, const ColorRGB&);
  ColorRGB get_pixel(const IntPoint2D&) const;
  IntPoint2D to_pixel(const Point2D&) const;

private:
  CDCGraphics2D(const CDCGraphics2D&);              // not implemented
  CDCGraphics2D& operator=(const CDCGraphics2D&);   // not implemented

private:
  struct Impl;
  Impl *pimpl;
};

#endif
