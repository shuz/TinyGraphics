#ifndef OBJECT_3D_INCLUDED__
#define OBJECT_3D_INCLUDED__

#include "Real.h"

namespace TinyGraphics {

  class Ray;
  class Material;
  class Position;
  class Vector3D;
  class Point3D;
  class Point2D;
  class TriangleSet;

  class Object3D {
  public:
    virtual
    ~Object3D() = 0;

    virtual
    const TriangleSet& to_triangle_set() const = 0;


    // compute the hit point of the ray on the object.
    // 
    // params:
    //   ray: the ray from which the hit point is computed
    //   normal:
    //     output parameter,
    //     set to be the unit normal vector of the hit point
    //   plane_idx:
    //     output parameter,
    //     the index of the plane the ray hit,
    //     used in get_plane_coord below
    // returns:
    //     the hit_point.
    //     ray.point_at(hit_point) is the hit point
    //     if hit_point <= 0, there is no hit point
    // note:
    //   hit_point <= 0 indicates there is no hit point,
    //   and the normal becomes invalid in this situation.
    virtual
    real intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const = 0;

    // compute the position of the point on the plane
    // return value's x and y should in range (0, 1) inclusive,
    // if the point is on the plane.
    // other values are returned if the point out of range.
    virtual
    Point2D get_plane_coord(int plane_idx, const Point3D& point) const = 0;

    // return true if point is inside the object
    virtual
    bool contain(const Point3D& point) const = 0;

    virtual
    const Material& get_material() const = 0;

    virtual
    const Position& get_position() const = 0;

    virtual
    void set_material(const Material& mat) = 0;

    virtual
    void set_position(const Position& pos) = 0;

    const Point3D& get_location() const;
    const Vector3D& get_front_vector() const;
    const Vector3D& get_up_vector() const;

    void set_location(const Point3D& point);
    void set_front_vector(const Vector3D& vec);
    void set_up_vector(const Vector3D& vec);

    void translate(const Vector3D& vec);

    void rotate_x(real angle);
    void rotate_y(real angle);
    void rotate_z(real angle);
    void rotate(const Vector3D& axis, real angle);
    void rotate(const Point3D& point, const Vector3D& axis, real angle);

    void transform(const Position& pos);

  protected:
    Object3D();

  private:
    Object3D(const Object3D&);              // not implemented
    Object3D& operator=(const Object3D&);   // not implemented
  };
}

#endif
