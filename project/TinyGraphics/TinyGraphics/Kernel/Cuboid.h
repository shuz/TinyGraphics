#ifndef CUBOID_INCLUDED__
#define CUBOID_INCLUDED__

#include "Object3D.h"
#include "Real.h"

namespace TinyGraphics {

  class Cuboid : public Object3D {
  public:
    Cuboid();
    Cuboid(real a, real b, real c);
    Cuboid(real a, real b, real c, const Position& position);
    ~Cuboid();

    const TriangleSet& to_triangle_set() const;
    real intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const;
    Point2D get_plane_coord(int plane_idx, const Point3D& point) const;
    bool contain(const Point3D& point) const;

    void set_material(const Material& material);
    const Material& get_material() const;

    void set_extent(real a, real b, real c);
    void get_extent(real& a, real& b, real& c) const;

    void set_position(const Position& position);
    const Position& get_position() const;

  private:
    Cuboid(const Cuboid&);              // not implemented
    Cuboid& operator=(const Cuboid&);   // not implemented

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
