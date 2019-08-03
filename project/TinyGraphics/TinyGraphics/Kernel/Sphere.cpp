#include "Sphere.h"
#include "Material.h"
#include "Primitive2D.h"
#include "Primitive3D.h"
#include "Ray.h"
#include "Position.h"
#include "Texture.h"

#include <math.h>

namespace TinyGraphics {

  static const int DEFAULT_LX = 30;
  static const int MINIMAL_LX = 4;

  struct Sphere::Impl {
    real r;
    Position position;
    Material material;

    int lx;
    TriangleSet triangle_set;
    TriangleSet canonical_triangle_set;

    Impl(real r) : r(r) {
      lx = DEFAULT_LX;
      update_triangle_set();
    }

    Impl(real r, const Position& position)
      : r(r), position(position) {
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
      Vector3D origin(ray.origin.to_vec3d());

      real a = ray.direction.square_norm();
      real b = 2 * origin.dot_product(ray.direction);
      real c = origin.square_norm() - r*r;
      real delta = b*b - 4*a*c;

      if (delta < 0) {
        return -1;
      }

      real t1 = (-b - sqrt(delta)) / (2*a);
      real t2 = (-b + sqrt(delta)) / (2*a);

      real hit_point;
      if (t1 > TG_EPSILON)
        hit_point = t1;
      else 
        hit_point = t2;

      normal = ray.point_at(hit_point).to_vec3d();
      normal.normalize();
      plane_idx = 1;

      return hit_point;
    }

    Point2D get_plane_coord_obj(int plane_idx, const Point3D& point) const {
      if (plane_idx == 1) {
        real cos_phi = point.y / r;
        real sin2_phi = 1 - cos_phi*cos_phi;
        if (sin2_phi > TG_EPSILON*TG_EPSILON) {
          real phi = acos(cos_phi);
          real sin_phi = sqrt(sin2_phi);
          real cos_theta = -point.z / (r * sin_phi);
          real theta;
          if (abs(cos_theta) <= 1) {
            theta = acos(cos_theta);
          } else
          if (abs(cos_theta) <= 1 + TG_EPSILON) {
            theta = (cos_theta >  0) ? 0 : TG_PI;
          }
          if (point.x > 0) theta = TG_2PI - theta;

          return Point2D(theta/TG_2PI, 1 - phi/TG_PI);
        } else 
        if (abs(sin2_phi) <= TG_EPSILON*TG_EPSILON) {        // the poles
          if (point.y < 0)
            return Point2D(0, 0);
          else
            return Point2D(1, 1);
        }
        // not in range if reach here
      }
      return Point2D(-1, -1);
    }

    bool contain_obj_coord(const Point3D& point) {
      return Vector3D(point.to_vec3d()).square_norm() < r*r;
    }

    void update_triangle_set() {
      typedef TriangleSet::Triangle Triangle;

      int ly = lx/2;
      int vertex_size = 2 + lx*(ly-1);
      int triangle_size = 2*lx*(ly-1);

      canonical_triangle_set.clear();
      canonical_triangle_set.vertices.reserve(vertex_size);
      canonical_triangle_set.normals.reserve(vertex_size);
      canonical_triangle_set.triangles.reserve(triangle_size);

      Point3D top, bottom;
      top.y += r;    bottom.y -= r;
      canonical_triangle_set.vertices.push_back(top);
      canonical_triangle_set.normals.push_back(Vector3D(0, 1, 0));

      int i, j;
      real dtheta = TG_PI / ly;
      real dphi = TG_2PI / lx;

      for (i = 1; i < ly; ++i) {
        real theta = TG_PI_2 - dtheta * i;
        real y = r * sin(theta);
        real ry = r * cos(theta);

        for (j = 0; j < lx; ++j) {
          real phi = dphi * j;
          real x = ry * cos(phi);
          real z = -ry * sin(phi);
          Point3D vertex = Point3D(x, y, z);
          canonical_triangle_set.vertices.push_back(vertex);
          Vector3D normal = Vector3D(x, y, z);
          normal.normalize();
          canonical_triangle_set.normals.push_back(normal);
        }
      }

      canonical_triangle_set.vertices.push_back(bottom);
      canonical_triangle_set.normals.push_back(Vector3D(0, -1, 0));

      for (i = 0; i < lx; ++i) {          // north pole
        int a = i+1, b = (i == lx-1) ? 1 : a+1, c = 0;
        canonical_triangle_set.triangles.push_back(Triangle(a, b, c));
      }

      for (i = 0; i < ly - 2; ++i) {      // body
        int offset = 1 + i*lx;
        for (j = 0; j < lx; ++j) {
          int a = j + offset;
          int b = a+lx;    // the point on the next latitude
          int c = ((j == lx-1) ? offset : a+1);
          canonical_triangle_set.triangles.push_back(Triangle(a, b, c));

          a = c; c = (j == lx-1) ? b-j : b+1;
          canonical_triangle_set.triangles.push_back(Triangle(a, b, c));
        }
      }

      for (i = 0; i < lx; ++i) {          // south pole
        int offset = 1 + (ly-2)*lx;
        int a = i, b = vertex_size-1,
            c = (a == lx-1) ? 1 : a+1;
        a += offset; c += offset;
        canonical_triangle_set.triangles.push_back(Triangle(a, b, c));
      }

      update_position();
    }

    void update_position() {
      triangle_set = canonical_triangle_set;
      triangle_set.transform(position.get_transformer_inv());
    }
  };
  
  Sphere::Sphere()
    : pimpl(new Impl(1)) {}

  Sphere::Sphere(real r)
    : pimpl(new Impl(r)) {}

  Sphere::Sphere(real r, const Position& position)
    : pimpl(new Impl(r, position)) {}

  Sphere::~Sphere() {
    delete pimpl;
  }

  const TriangleSet& Sphere::to_triangle_set() const {
    return pimpl->triangle_set;
  }

  real Sphere::intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const {
    Ray obj_ray = pimpl->to_object_coord(ray);
    real hit_point = pimpl->intersect_obj(obj_ray, normal, plane_idx);
    normal = pimpl->to_world_coord(normal);
    return hit_point;
  }

  Point2D Sphere::get_plane_coord(int plane_idx, const Point3D& point) const {
    return pimpl->get_plane_coord_obj(plane_idx, pimpl->to_object_coord(point));
  }

  bool Sphere::contain(const Point3D& point) const {
    Point3D obj_point = pimpl->to_object_coord(point);
    return pimpl->contain_obj_coord(obj_point);
  }

  const Material& Sphere::get_material() const {
    return pimpl->material;
  }

  void Sphere::set_material(const Material& material) {
    pimpl->material = material;
  }

  const Position& Sphere::get_position() const {
    return pimpl->position;
  }

  void Sphere::set_position(const Position& position) {
    pimpl->position = position;
    pimpl->update_position();
  }

  real Sphere::get_radius() const {
    return pimpl->r;
  }

  void Sphere::set_radius(real radius) {
    pimpl->r = radius;
    pimpl->update_triangle_set();
  }

  int Sphere::get_resolution() const {
    return pimpl->lx - MINIMAL_LX;
  }

  void Sphere::set_resolution(int lx) {
    pimpl->lx = lx + MINIMAL_LX;    // make any integer >= 0 legal here
    pimpl->update_triangle_set();
  }
}
