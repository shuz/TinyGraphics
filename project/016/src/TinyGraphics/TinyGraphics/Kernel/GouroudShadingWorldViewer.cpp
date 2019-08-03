#include "GouroudShadingWorldViewer.h"

#include "World3D.h"
#include "Object3D.h"
#include "Graphics2D.h"
#include "Graphics3D.h"
#include "Primitive2D.h"
#include "Primitive3D.h"
#include "Matrix4D.h"
#include "Material.h"
#include "Ray.h"
#include "Light.h"
#include "Camera.h"
#include "ZBuffer.h"

#include <assert.h>

namespace TinyGraphics {

  namespace Detail {
    inline 
    int sgn(int x) {
      return (x > 0) ? 1 : (x < 0) ? -1 : 0;
    }

    template <typename T>
    inline
    void swap(T& x, T& y) {
      T temp = x;
      x = y;  y = temp;
    }

    inline
    int max(int x, int y) {
      return (x > y) ? x : y;
    }

    inline
    int round(real x) {
      return (int)(x + 0.5);
    }

    // the following structures are used in draw_transformed_triangle  
    struct Vertex {
      int x, y;
      real z;
      ColorRGB color;

      Vertex() {}
      Vertex(const IntPoint2D& xy, real z, const ColorRGB& color)
        : x(xy.x), y(xy.y), z(z), color(color) {}
    };

    struct Edge {
      int y0, dy;
      real x0, z0;
      real kx_inv, kz_inv;
      ColorRGB color0, k_color;

      void step() {
        ++y0;  --dy;
        x0 += kx_inv;
        z0 += kz_inv;
        color0 += k_color;
      }

      void assign(const Vertex& p1, const Vertex& p2) {
        const Vertex *pp1 = &p1, *pp2 = &p2;
        if (pp1->y > pp2->y)
          swap(pp1, pp2);
        x0 = pp1->x;
        y0 = pp1->y;
        dy = pp2->y - y0;
        z0 = pp1->z;
        color0 = pp1->color;
        if (dy != 0) {
          real dy_inv = 1.0 / dy;
          kx_inv = (pp2->x - pp1->x) * dy_inv;
          kz_inv = (pp2->z - pp1->z) * dy_inv;
          k_color = (pp2->color - pp1->color) * dy_inv;
        } else {
          // set kx_inv and kz_inv to infinity for compare
          kx_inv = std::numeric_limits<real>::infinity();

          // kz_inv and k_color are never useful in this situation
          kz_inv = 0;
          k_color = ColorRGB::BLACK;
        }
      }

      bool operator > (const Edge& rhs) const {
        if (y0 > rhs.y0) return true;
        if (y0 < rhs.y0) return false;
        if (x0 > rhs.x0) return true;
        if (x0 < rhs.x0) return false;
        if (kx_inv > rhs.kx_inv) return true;
        return false;
      }
    };
  }

  using namespace Detail;

  class GouroudShadingGraphics3D : public Graphics3D {
  public:
    typedef World3D::LightIterator LightIterator;

    GouroudShadingGraphics3D(Graphics2D *graphics, const Camera *camera,
                             const World3D *world, bool use_material)
      : graphics_2d(graphics), camera(camera), world(world),
        zbuffer(graphics), use_material(use_material) {
      int x, y;
      graphics_2d->get_window_ext(x, y);
      zbuffer.create(x, y);
    }

    void draw_line(const Point3D& begin, const Point3D& end,
                   const ColorRGB& color) {
      const Matrix4D& mat = camera->get_projection_matrix();
      Point3D p_begin = begin * mat,
              p_end = end * mat;
      IntPoint2D int_begin = graphics_2d->to_pixel(project(p_begin)),
                 int_end   = graphics_2d->to_pixel(project(p_end));
      // Bresenham's algorithm
      int x = int_begin.x, y = int_begin.y;
      int dx = abs(int_end.x - int_begin.x);
      int dy = abs(int_end.y - int_begin.y);
      int s1 = sgn(int_end.x - int_begin.x);
      int s2 = sgn(int_end.y - int_begin.y);
      real z = p_begin.z;
      real dz = (p_end.z - z) / max(dx, dy);
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

    void draw_triangle_set(const TriangleSet& triangles,
                           const Material& material) {
      const Matrix4D& mat = camera->get_projection_matrix();
      TriangleSet::TriangleContainer::const_iterator
        itor = triangles.triangles.begin(),
        end = triangles.triangles.end();
      int i = 0;
      for (; itor != end; ++itor) {
        int index_a = (*itor).a;
        int index_b = (*itor).b;
        int index_c = (*itor).c;
        Point3D a = triangles.vertices[index_a] * mat;
        Point3D b = triangles.vertices[index_b] * mat;
        Point3D c = triangles.vertices[index_c] * mat;
        IntPoint2D int_a = graphics_2d->to_pixel(project(a)),
                   int_b = graphics_2d->to_pixel(project(b)),
                   int_c = graphics_2d->to_pixel(project(c));

        // compute color for each vertex
        Vertex va(int_a, a.z, shade(a, triangles.normals[index_a], material)),
               vb(int_b, b.z, shade(b, triangles.normals[index_b], material)),
               vc(int_c, c.z, shade(c, triangles.normals[index_c], material));

        draw_transformed_triangle(va, vb, vc);
      }
    }

    void draw_transformed_triangle(const Vertex& a, const Vertex& b,
                                   const Vertex& c) {
      // setup the active edge table
      Edge edge[3];
      edge[0].assign(a, b);
      edge[1].assign(a, c);
      edge[2].assign(b, c);
      Edge *p_edge[7] = {&edge[0], &edge[1], &edge[2]};
      if (*p_edge[0] > *p_edge[1]) swap(p_edge[0], p_edge[1]);
      if (*p_edge[1] > *p_edge[2]) swap(p_edge[1], p_edge[2]);
      if (*p_edge[0] > *p_edge[1]) swap(p_edge[0], p_edge[1]);

      if (p_edge[0]->dy == 0) {   // indicates all points in a horizontal line
        scan_line(a, b);
        scan_line(a, c);
        scan_line(b, c);
      } else {
        if (p_edge[1]->dy == 0) {
          p_edge[1] = p_edge[2];
          p_edge[2] = 0;
        } else 
        if (p_edge[2]->dy == 0) {
          p_edge[2] = 0;
        }

        scan_triangle_edges(p_edge);
      }
    }

    // edge:
    //   the edge of the triangle, sorted by Edge::operator <,
    //   it contains 2 or 3 edges for non-degenerated triangles,
    //   since the horizontal edge is not useful in the array,
    void scan_triangle_edges(Edge *edge[]) {
      int i = 0;
      Edge left(*edge[i++]), right(*edge[i++]);
      while (true) {
        while (left.dy >= 0 && right.dy >= 0) {
          scan_line(left, right);
          left.step();  right.step();
        }
        if (edge[i] == 0) return;   // scan over
        if (left.dy < 0) {
          left = *edge[i++];
          left.step();
        }
        if (right.dy < 0) {
          right = *edge[i++];
          right.step();
        }
      }
    }

    void scan_line(const Edge& left, const Edge& right) {
      assert(left.y0 == right.y0);
      int y = left.y0;
      int x_begin = round(left.x0), x_end = round(right.x0);
      int dx = x_end - x_begin;
      real dz = right.z0 - left.z0;
      ColorRGB dcolor = right.color0 - left.color0;

      real ddz = (dx == 0) ? 0 : dz / dx;
      ColorRGB ddcolor = (dx == 0) ? ColorRGB::BLACK : dcolor * (1.0 / dx);

      for (int x = x_begin; x <= x_end; ++x) {
        int ddx = (int)(x - left.x0);
        real z = left.z0 + ddx * ddz;
        ColorRGB color(left.color0 + ddx * ddcolor);

        zbuffer.set_pixel(x, y, z, color);
      }
    }

    void scan_line(const Vertex& left, const Vertex& right) {
      assert(left.y == right.y);
      const Vertex *p_left = &left, *p_right = &right;
      if (p_left->x > p_right->x) swap(p_left, p_right);
      int y = p_left->y;
      int dx = p_right->x - p_left->x;
      real dz = p_right->z - p_left->z;
      ColorRGB dcolor = p_right->color - p_left->color;

      real ddz = (dx == 0) ? 0 : dz / dx;
      ColorRGB ddcolor = (dx == 0) ? ColorRGB::BLACK : dcolor * (1.0 / dx);
      for (int ddx = 0; ddx <= dx; ++ddx) {
        int x = ddx + p_left->x;
        real z = p_left->z + ddx * ddz;
        ColorRGB color(p_left->color + ddx * ddcolor);

        zbuffer.set_pixel(x, y, z, color);
      }
    }

    ColorRGB shade(const Point3D& point, const Vector3D& normal,
                   const Material& material) {
      ColorRGB rtv = material.color * world->get_ambient_color();
      if (use_material) rtv *= material.k_ambient;

      LightIterator lights = world->get_light_iterator();
      Ray light_ray;
      while (lights.has_next()) {

        Light *light = lights.next();
        if (!light->illuminate(point, light_ray)) continue;

        Vector3D light_vec = -light_ray.direction;
        ColorRGB diffuse_color = light_ray.color * material.color *
                                 normal.dot_product(light_vec);
        if (use_material) diffuse_color *= material.k_diffuse;

        // prevent negative color
        diffuse_color.clamp();

        rtv += diffuse_color;
      }
      rtv.clamp();
      return rtv;
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
    const World3D *world;
    ZBuffer zbuffer;
    bool use_material;

    // the following members are not implemented
    GouroudShadingGraphics3D(const GouroudShadingGraphics3D&);
    GouroudShadingGraphics3D& operator=(const GouroudShadingGraphics3D&);
  };

  struct GouroudShadingWorldViewer::Impl {
    const World3D *world;
    const Camera *camera;
    bool use_material;
    Impl(const World3D *world, const Camera *camera, bool use_material)
      : world(world), camera(camera), use_material(use_material) {}
  };

  GouroudShadingWorldViewer::GouroudShadingWorldViewer(
        const World3D *world, const Camera *camera, bool use_material
    )
    : pimpl(new Impl(world, camera, use_material)) {}

  GouroudShadingWorldViewer::~GouroudShadingWorldViewer() {
    delete pimpl;
  }

  const Camera *GouroudShadingWorldViewer::get_camera() const {
    return pimpl->camera;
  }

  void GouroudShadingWorldViewer::set_camera(const Camera *camera) {
    pimpl->camera = camera;
  }

  void GouroudShadingWorldViewer::draw(Graphics2D *g2d) const {
    g2d->draw_background(pimpl->world->get_background_color());

    GouroudShadingGraphics3D g3d(g2d, pimpl->camera, pimpl->world,
                                 pimpl->use_material);
    World3D::ObjectIterator obj_itor = pimpl->world->get_object_iterator();
  
    while (obj_itor.has_next()) {
      Object3D *obj = obj_itor.next();
      g3d.draw_triangle_set(obj->to_triangle_set(), obj->get_material());
    }
  }
}
