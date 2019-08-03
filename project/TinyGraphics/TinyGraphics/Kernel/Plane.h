#ifndef PLANE_INCLUDED__
#define PLANE_INCLUDED__

#include "Object3D.h"
#include "Real.h"

namespace TinyGraphics {

  class Plane : public Object3D {
  public:
    Plane();
    Plane(real a, real b);
    Plane(real a, real b, const Position& position);
    ~Plane();

    const TriangleSet& to_triangle_set() const;
    real intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const;
    Point2D get_plane_coord(int plane_idx, const Point3D& point) const;
    bool contain(const Point3D& point) const;

    void set_material(const Material& material);
    const Material& get_material() const;

    void set_extent(real a, real b);
    void get_extent(real& a, real& b) const;

    void set_position(const Position& position);
    const Position& get_position() const;

  private:
    Plane(const Plane&);              // not implemented
    Plane& operator=(const Plane&);   // not implemented

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
