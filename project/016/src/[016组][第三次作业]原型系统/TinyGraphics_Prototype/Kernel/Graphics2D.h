#ifndef GRAPHICS_2D_INCLUDED__
#define GRAPHICS_2D_INCLUDED__

class Point2D;
class ColorRGB;

class Graphics2D {
public:
  virtual
  ~Graphics2D() = 0;

  virtual
  void draw_line (const Point2D&, const Point2D&);

  virtual
  void draw_line (const Point2D&, const Point2D&, const ColorRGB&) = 0;

  virtual
  void draw_point(const Point2D&, const ColorRGB&) = 0;

protected:
  Graphics2D();

private:
  Graphics2D(const Graphics2D&);              // not implemented
  Graphics2D& operator=(const Graphics2D&);   // not implemented
};

#endif
