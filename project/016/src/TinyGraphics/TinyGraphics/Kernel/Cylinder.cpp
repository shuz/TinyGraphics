#include "Cylinder.h"
#include "Material.h"
#include "Primitive2D.h"
#include "Primitive3D.h"
#include "Ray.h"
#include "Position.h"
#include "Texture.h"

#include <math.h>

namespace TinyGraphics {

  static const int DEFAULT_LX = 50;
  static const int MINIMAL_LX = 3;

  struct Cylinder::Impl {
    real r, h;
    Position position;
    Material material;

    int lx;
    TriangleSet triangle_set;
    TriangleSet canonical_triangle_set;

    Impl(real r, real h) : r(r), h(h) {
      lx = DEFAULT_LX;
      update_triangle_set();
    }

    Impl(real r, real h, const Position& position)
      : r(r), h(h), position(position) {
      lx = DEFAULT_LX;
      update_triangle_set();
    }

    ~Impl() {
      delete material.texture;
    }

    template <class T>
    T to_object_coord(const T& p) const {
      T rtv(p);
      rtv.transform(position.get_transformer());
      return rtv;
    }

    template <class T>
    T to_world_coord(const T& p) const {
      T rtv(p);
      rtv.transform(position.get_transformer_inv());
      return rtv;
    }

    real intersect_obj(const Ray& ray, Vector3D& normal, int& plane_idx) const {
      real x0 = ray.origin.x, x1 = ray.direction(0);
      real y0 = ray.origin.y, y1 = ray.direction(1);
      real z0 = ray.origin.z, z1 = ray.direction(2);
      real r2 = r*r;
      real a = x1*x1 + z1*z1;
      real b = 2 * (x0*x1 + z0*z1);
      real c = x0*x0 + z0*z0 - r2;
      real delta = b*b - 4*a*c;

      if (delta < 0) {
        return -1;
      }

      real t1 = (-b - sqrt(delta)) / (2*a);
      real t2 = (-b + sqrt(delta)) / (2*a);

      real hit_point = std::numeric_limits<real>::infinity();
      bool is_hit = false;
      if (t1 > TG_EPSILON) {
        real y_t1 = ray.point_at(t1).y;
        if (0 <= y_t1 && y_t1 <= h) {
          hit_point = t1;
          plane_idx = 1;
          is_hit = true;
        }
      } else
      if (!is_hit && t2 > TG_EPSILON) {
        real y_t2 = ray.point_at(t2).y;
        if (0 <= y_t2 && y_t2 <= h) {
          hit_point = t2;
          plane_idx = 1;
          is_hit = true;
        }
      }

      if (is_hit) {
        Point3D hit_12 = ray.point_at(hit_point);
        normal.assign(hit_12.x, 0, hit_12.z);
        normal.normalize();
      }

      real t3 = -y0/y1;
      Point3D hit_3 = ray.point_at(t3);
      if (t3 > TG_EPSILON && t3 < hit_point &&
          hit_3.x * hit_3.x + hit_3.z * hit_3.z <= r2) {
        hit_point = t3;
        plane_idx = 2;
        normal.assign(0, -1, 0);
        is_hit = true;
      }

      real t4 = (h - y0)/y1;
      Point3D hit_4 = ray.point_at(t4);
      if (t4 > TG_EPSILON && t4 < hit_point &&
          hit_4.x * hit_4.x + hit_4.z * hit_4.z <= r2) {
        hit_point = t4;
        plane_idx = 3;
        normal.assign(0, 1, 0);
        is_hit = true;
      }

      if (!is_hit) return -1;
      return hit_point;
    }

    Point2D get_plane_coord_obj(int plane_idx, const Point3D& point) const {
      if (plane_idx == 1) {
        real v = point.y/h;
        real cos_theta = -point.z / r;
        real theta;
        if (abs(cos_theta) <= 1) {
          theta = acos(cos_theta);
        } else
        if (abs(cos_theta) <= 1 + TG_EPSILON) {
          theta = (cos_theta >  0) ? 0 : TG_PI;
        }
        if (point.x > 0) theta = TG_2PI - theta;
        return Point2D(theta / TG_2PI, v);
      } else
      if (plane_idx == 2) {
        return Point2D(0.5 + point.x/(2*r), 0.5 + point.z/(2*r));
      } else
      if (plane_idx == 3) {
        return Point2D(0.5 + point.x/(2*r), 0.5 - point.z/(2*r));
      }

      return Point2D(-1, -1);
    }

    bool contain_obj_coord(const Point3D& point) {
      if (0 <= point.y && point.y <= h &&
          point.x*point.x + point.z*point.z <= r*r)
        return true;
      return false;
    }

    void update_triangle_set() {
      typedef TriangleSet::Triangle Triangle;

      int vertex_size = 4*lx + 2;
      int triangle_size = 4*lx;

      canonical_triangle_set.clear();
      canonical_triangle_set.vertices.reserve(vertex_size);
      canonical_triangle_set.normals.reserve(vertex_size);
      canonical_triangle_set.triangles.reserve(triangle_size);

      Point3D top(0, h, 0);
      canonical_triangle_set.vertices.push_back(top);
      canonical_triangle_set.normals.push_back(Vector3D(0, 1, 0));

      int i;
      real dtheta = TG_2PI / lx;
      real theta = 0;
      for (i = 0; i < lx; ++i) {
        theta += dtheta;
        real x = r * cos(theta);
        real z = -r * sin(theta);

        Point3D vertex = Point3D(x, h, z);
        canonical_triangle_set.vertices.push_back(vertex);
        canonical_triangle_set.vertices.push_back(vertex);
        vertex.y = 0;
        canonical_triangle_set.vertices.push_back(vertex);
        canonical_triangle_set.vertices.push_back(vertex);

        Vector3D normal = Vector3D(x, 0, z);
        normal.normalize();
        canonical_triangle_set.normals.push_back(normal);
        canonical_triangle_set.normals.push_back(Vector3D(0, 1, 0));
        canonical_triangle_set.normals.push_back(normal);
        canonical_triangle_set.normals.push_back(Vector3D(0, -1, 0));
      }
    
      Point3D bottom(0, 0, 0);
      canonical_triangle_set.vertices.push_back(bottom);
      canonical_triangle_set.normals.push_back(Vector3D(0, -1, 0));

      int btm_idx = vertex_size - 1;
      for (i = 0; i < triangle_size; i += 4) {
        int b = i+1, c = (i == triangle_size - 4) ? 1 : b+4;
        int d = b+2, e = (i == triangle_size - 4) ? 3 : d+4;
        canonical_triangle_set.triangles.push_back(Triangle(0, b+1, c+1));
        canonical_triangle_set.triangles.push_back(Triangle(b, d, c));
        canonical_triangle_set.triangles.push_back(Triangle(c, d, e));
        canonical_triangle_set.triangles.push_back(Triangle(btm_idx, e+1, d+1));
      }

      update_position();
    }

    void update_position() {
      triangle_set = canonical_triangle_set;
      triangle_set.transform(position.get_transformer_inv());
    }
  };

  Cylinder::Cylinder()
    : pimpl(new Impl(1, 1)) {}

  Cylinder::Cylinder(real r, real h)
    : pimpl(new Impl(r, h)) {}

  Cylinder::Cylinder(real r, real h, const Position& position)
    : pimpl(new Impl(r, h, position)) {}

  Cylinder::~Cylinder() {
    delete pimpl;
  }

  const TriangleSet& Cylinder::to_triangle_set() const {
    return pimpl->triangle_set;
  }

  real Cylinder::intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const {
    Ray obj_ray = pimpl->to_object_coord(ray);
    real hit_point = pimpl->intersect_obj(obj_ray, normal, plane_idx);
    normal = pimpl->to_world_coord(normal);
    return hit_point;
  }

  Point2D Cylinder::get_plane_coord(int plane_idx, const Point3D& point) const {
    return pimpl->get_plane_coord_obj(plane_idx, pimpl->to_object_coord(point));
  }

  bool Cylinder::contain(const Point3D& point) const {
    Point3D obj_point = pimpl->to_object_coord(point);
    return pimpl->contain_obj_coord(obj_point);
  }

  const Material& Cylinder::get_material() const {
    return pimpl->material;
  }

  void Cylinder::set_material(const Material& material) {
    pimpl->material = material;
  }

  const Position& Cylinder::get_position() const {
    return pimpl->position;
  }

  void Cylinder::set_position(const Position& position) {
    pimpl->position = position;
    pimpl->update_position();
  }

  void Cylinder::get_radius_height(real& radius, real& height) const {
    radius = pimpl->r;  height = pimpl->h;
  }

  void Cylinder::set_radius_height(real radius, real height) {
    pimpl->r = radius;
    pimpl->h = height;
    pimpl->update_triangle_set();
  }

  int Cylinder::get_resolution() const {
    return pimpl->lx - MINIMAL_LX;
  }

  void Cylinder::set_resolution(int lx) {
    pimpl->lx = lx + MINIMAL_LX;    // make any integer >= 0 legal here
    pimpl->update_triangle_set();
  }
}
