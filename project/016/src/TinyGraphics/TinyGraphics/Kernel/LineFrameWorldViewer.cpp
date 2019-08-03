#include "LineFrameWorldViewer.h"

#include "World3D.h"
#include "Object3D.h"
#include "Graphics2D.h"
#include "Graphics3D.h"
#include "Primitive2D.h"
#include "Primitive3D.h"
#include "Material.h"
#include "Matrix4D.h"
#include "Camera.h"
#include "ZBuffer.h"

namespace TinyGraphics {

  namespace Detail {
    inline 
    int sgn(int x) {
      return (x > 0) ? 1 : (x < 0) ? -1 : 0;
    }

    inline
    void swap(int& x, int& y) {
      int temp = x;
      x = y;  y = temp;
    }

    inline
    int max(int x, int y) {
      return (x > y) ? x : y;
    }
  }

  using namespace Detail;

  class LineFrameGraphics3D : public Graphics3D {
  public:
    LineFrameGraphics3D(Graphics2D *graphics, const Camera *camera)
      : graphics_2d(graphics), camera(camera), zbuffer(graphics) {
      int x, y;
      graphics_2d->get_window_ext(x, y);
      zbuffer.create(x, y);
    }

    void draw_line(const Point3D& begin, const Point3D& end,
                   const ColorRGB& color) {
      const Matrix4D& mat = camera->get_projection_matrix();
      Point3D p_begin = begin * mat,
              p_end = end * mat;
      draw_transformed_line(p_begin, p_end, color);
    }

    void draw_triangle_set(const TriangleSet& triangles,
                           const Material& material) {
      const ColorRGB& color = material.color;
      const Matrix4D& mat = camera->get_projection_matrix();
      TriangleSet::TriangleContainer::const_iterator
        itor = triangles.triangles.begin(),
        end = triangles.triangles.end();
      for (; itor != end; ++itor) {
        Point3D a = triangles.vertices[(*itor).a] * mat;
        Point3D b = triangles.vertices[(*itor).b] * mat;
        Point3D c = triangles.vertices[(*itor).c] * mat;
        draw_transformed_line(a, b, color);
        draw_transformed_line(b, c, color);
        draw_transformed_line(c, a, color);
      }
    }

    void draw_transformed_line(const Point3D& begin, const Point3D& end,
                               const ColorRGB& color) {
      IntPoint2D int_begin = graphics_2d->to_pixel(project(begin)),
                 int_end   = graphics_2d->to_pixel(project(end));
      // Bresenham's algorithm
      int x = int_begin.x, y = int_begin.y;
      int dx = abs(int_end.x - int_begin.x);
      int dy = abs(int_end.y - int_begin.y);
      int s1 = sgn(int_end.x - int_begin.x);
      int s2 = sgn(int_end.y - int_begin.y);
      real z = begin.z;
      real dz = (end.z - z) / max(dx, dy);
      bool interchange = false;
      if (dy > dx) {
        swap(dx, dy);
        interchange = true;
      }

      int err = 2*dy - dx;
      for (int i = 0; i < dx; ++i) {
        zbuffer.set_pixel(x, y, z, color);
        if (err > 0) {
          if (interchange)
            x += s1;
          else
            y += s2;
          err -= 2*dx;
        }
        if (interchange)
          y += s2;
        else
          x += s1;
        z += dz;
        err += 2*dy;
      }
    }

    static Point2D project(const Point3D& point, const Matrix4D& mat) {
      Point3D p = point * mat;
      return Point2D(p.x, p.y);
    }

    static Point2D project(const Point3D& point) {
      return Point2D(point.x, point.y);
    }

  private:
    Graphics2D *graphics_2d;
    const Camera *camera;
    ZBuffer zbuffer;

    LineFrameGraphics3D(const LineFrameGraphics3D&);             // not implemented
    LineFrameGraphics3D& operator=(const LineFrameGraphics3D&);  // not implemented
  };

  struct LineFrameWorldViewer::Impl {
    const World3D *world;
    const Camera *camera;
    Impl(const World3D *world, const Camera *camera)
      : world(world), camera(camera) {}
  };

  LineFrameWorldViewer::LineFrameWorldViewer(const World3D *world, const Camera *camera)
    : pimpl(new Impl(world, camera)) {}

  LineFrameWorldViewer::~LineFrameWorldViewer() {
    delete pimpl;
  }

  const Camera *LineFrameWorldViewer::get_camera() const {
    return pimpl->camera;
  }

  void LineFrameWorldViewer::set_camera(const Camera *camera) {
    pimpl->camera = camera;
  }

  void LineFrameWorldViewer::draw(Graphics2D *g2d) const {
    g2d->draw_background(pimpl->world->get_background_color());

    LineFrameGraphics3D g3d(g2d, pimpl->camera);
    World3D::ObjectIterator obj_itor = pimpl->world->get_object_iterator();
  
    while (obj_itor.has_next()) {
      Object3D *obj = obj_itor.next();
      g3d.draw_triangle_set(obj->to_triangle_set(), obj->get_material());
    }
  }
}
