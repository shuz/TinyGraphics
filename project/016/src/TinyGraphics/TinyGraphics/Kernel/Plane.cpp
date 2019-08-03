#include "Plane.h"
#include "ColorRGB.h"
#include "Material.h"
#include "Primitive2D.h"
#include "Primitive3D.h"
#include "Ray.h"
#include "Position.h"
#include "Texture.h"

namespace TinyGraphics {

  struct Plane::Impl {
    real a, b;
    Position position;
    Material material;

    TriangleSet triangle_set;
    TriangleSet canonical_triangle_set;

    Impl(real a, real b)
      : a(a), b(b) {
      update_triangle_set();
    }

    Impl(real a, real b, const Position& position)
      : a(a), b(b), position(position) {
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
      real min_t = std::numeric_limits<real>::infinity();
      real a_2 = a/2;
      real b_2 = b/2;

      if (ray.direction(1) != 0) {
        real t = -ray.origin.y / ray.direction(1);
        Point3D point = ray.point_at(t);
        if (t > TG_EPSILON && t < min_t &&
            -a_2 <= point.x && point.x <= a_2 &&
            -b_2 <= point.z && point.z <= b_2) {
          min_t = t;
          normal.assign(0, -1, 0);
          plane_idx = 1;
        }

        t = -ray.origin.y / ray.direction(1);
        point = ray.point_at(t);
        if (t > TG_EPSILON && t < min_t &&
            -a_2 <= point.x && point.x <= a_2 &&
            -b_2 <= point.z && point.z <= b_2) {
          min_t = t;
          normal.assign(0, 1, 0);
          plane_idx = 2;
        }
      }

      if (min_t == std::numeric_limits<real>::infinity())
        return -1;
      return min_t;
    }

    Point2D get_plane_coord_obj(int plane_idx, const Point3D& point) const {
      switch (plane_idx) {
        case 1:
          return Point2D(0.5 + point.x/a, 0.5 - point.z/b);
        case 2:
          return Point2D(0.5 + point.x/a, 0.5 + point.z/b);
        default:
          break;
      }
      return Point2D(-1, -1);
    }

    bool contain_obj(const Point3D& point) const {
      return false;     // neglect points on the plane
    }
  
  #define GENERATE_FACE(a1, b1, c1, a2, b2, c2, a3, b3, c3, a4, b4, c4)   \
    do {                                                                  \
      a = vert_num;                                                       \
      canonical_triangle_set.vertices.push_back(Point3D(a1, b1, c1));     \
      canonical_triangle_set.vertices.push_back(Point3D(a2, b2, c2));     \
      canonical_triangle_set.vertices.push_back(Point3D(a3, b3, c3));     \
      canonical_triangle_set.vertices.push_back(Point3D(a4, b4, c4));     \
      canonical_triangle_set.normals.push_back(normal);                   \
      canonical_triangle_set.normals.push_back(normal);                   \
      canonical_triangle_set.normals.push_back(normal);                   \
      canonical_triangle_set.normals.push_back(normal);                   \
      canonical_triangle_set.triangles.push_back(Triangle(a, a+1, a+2));  \
      canonical_triangle_set.triangles.push_back(Triangle(a, a+2, a+3));  \
      vert_num += 4;                                                      \
    } while (false)

    void update_triangle_set() {
      typedef TriangleSet::Triangle Triangle;

      int vertex_size = 8;
      int triangle_size = 4;
    
      canonical_triangle_set.clear();
      canonical_triangle_set.vertices.reserve(vertex_size);
      canonical_triangle_set.normals.reserve(vertex_size);
      canonical_triangle_set.triangles.reserve(triangle_size);

      real a_2 = a/2;
      real b_2 = b/2;

      Vector3D normal;
      int vert_num = 0;
      int a;

      normal.assign(0, 1, 0);
      GENERATE_FACE(-a_2, 0, +b_2, +a_2, 0, +b_2,
                    +a_2, 0, -b_2, -a_2, 0, -b_2);

      update_position();
    }

  #undef GENERATE_FACE

    void update_position() {
      triangle_set = canonical_triangle_set;
      triangle_set.transform(position.get_transformer_inv());
    }
  };
  
  Plane::Plane()
    : pimpl(new Impl(1, 1)) {}

  Plane::Plane(real a, real b)
    : pimpl(new Impl(a, b)) {}
  
  Plane::Plane(real a, real b, const Position& position)
    : pimpl(new Impl(a, b, position)) {}

  Plane::~Plane() {
    delete pimpl;
  }

  const TriangleSet& Plane::to_triangle_set() const {
    return pimpl->triangle_set;
  }

  real Plane::intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const {
    Ray obj_ray = pimpl->to_object_coord(ray);
    real hit_point = pimpl->intersect_obj(obj_ray, normal, plane_idx);
    normal = pimpl->to_world_coord(normal);
    return hit_point;
  }

  Point2D Plane::get_plane_coord(int plane_idx, const Point3D& point) const {
    return pimpl->get_plane_coord_obj(plane_idx, pimpl->to_object_coord(point));
  }

  bool Plane::contain(const Point3D& point) const {
    Point3D obj_point = pimpl->to_object_coord(point);
    return pimpl->contain_obj(obj_point);
  }

  const Material& Plane::get_material() const {
    return pimpl->material;
  }

  void Plane::set_material(const Material& material) {
    pimpl->material = material;
  }

  void Plane::get_extent(real& a, real& b) const {
    a = pimpl->a;
    b = pimpl->b;
  }

  void Plane::set_extent(real a, real b) {
    pimpl->a = a;
    pimpl->b = b;
    pimpl->update_triangle_set();
  }

  const Position& Plane::get_position() const {
    return pimpl->position;
  }

  void Plane::set_position(const Position& position) {
    pimpl->position = position;
    pimpl->update_position();
  }
}
