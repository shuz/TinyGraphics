#ifndef SPHERE_INCLUDED__
#define SPHERE_INCLUDED__

#include "Object3D.h"
#include "Real.h"

namespace TinyGraphics {

  class Sphere : public Object3D {
  public:
    Sphere();
    Sphere(real r);
    Sphere(real r, const Position& position);
    ~Sphere();

    const TriangleSet& to_triangle_set() const;
    real intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const;
    Point2D get_plane_coord(int plane_idx, const Point3D& point) const;
    bool contain(const Point3D& point) const;

    real get_radius() const;
    void set_radius(real radius);

    void set_position(const Position& pos);
    const Position& get_position() const;

    void set_material(const Material& material);
    const Material& get_material() const;

    // to decide the number of triangles divided into
    // any integer >= 0 is legal
    int get_resolution() const;
    void set_resolution(int lx);

  private:
    Sphere(const Sphere&);              // not implemented
    Sphere& operator=(const Sphere&);   // not implemented

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
