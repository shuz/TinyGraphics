#ifndef GRAPHICS_3D_INCLUDED__
#define GRAPHICS_3D_INCLUDED__

namespace TinyGraphics {

  class Point3D;
  class TriangleSet;
  class ColorRGB;
  class Material;

  class Graphics3D {
  public:
    virtual
    ~Graphics3D() = 0;

    virtual
    void draw_line(const Point3D&, const Point3D&, const ColorRGB&) = 0;

    virtual
    void draw_triangle_set(const TriangleSet&, const Material&) = 0;

  protected:
    Graphics3D();

  private:
    Graphics3D(const Graphics3D&);              // not implemented
    Graphics3D& operator=(const Graphics3D&);   // not implemented
  };
}

#endif
