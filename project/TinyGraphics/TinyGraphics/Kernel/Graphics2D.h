#ifndef GRAPHICS_2D_INCLUDED__
#define GRAPHICS_2D_INCLUDED__

namespace TinyGraphics {

  class IntPoint2D;
  class Point2D;
  class ColorRGB;

  class Graphics2D {
  public:
    virtual
    ~Graphics2D() = 0;

    // map the points from the canonical view to the screen and draw
    virtual
    void draw_line (const Point2D&, const Point2D&, const ColorRGB&) = 0;

    virtual
    void draw_point(const Point2D&, const ColorRGB&) = 0;

    virtual
    void draw_background(const ColorRGB&) = 0;

    // map the point to pixel that can be 
    // drawn directly by the method below
    virtual
    IntPoint2D to_pixel(const Point2D&) const = 0;

    // set the pixel directly, no mapping taken
    virtual
    void set_pixel(const IntPoint2D&, const ColorRGB&) = 0;

    // get the current color of the pixel
    virtual
    ColorRGB get_pixel(const IntPoint2D&) const = 0;

    // get the width and height of the window
    virtual
    void get_window_ext(int& width, int& height) const = 0;

  protected:
    Graphics2D();

  private:
    Graphics2D(const Graphics2D&);              // not implemented
    Graphics2D& operator=(const Graphics2D&);   // not implemented
  };

}

#endif
