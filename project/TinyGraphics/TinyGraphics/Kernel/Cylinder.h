#ifndef CYLINDER_INCLUDED__
#define CYLINDER_INCLUDED__

#include "Object3D.h"
#include "Real.h"

namespace TinyGraphics {

  class Cylinder : public Object3D {
  public:
    Cylinder();
    Cylinder(real r, real h);
    Cylinder(real r, real h, const Position& position);
    ~Cylinder();

    const TriangleSet& to_triangle_set() const;
    real intersect(const Ray& ray, Vector3D& normal, int& plane_idx) const;
    Point2D get_plane_coord(int plane_idx, const Point3D& point) const;
    bool contain(const Point3D& point) const;

    void get_radius_height(real& radius, real& height) const;
    void set_radius_height(real radius, real height);

    void set_position(const Position& pos);
    const Position& get_position() const;

    void set_material(const Material& material);
    const Material& get_material() const;

    // to decide the number of triangles divided into
    // any integer >= 0 is legal
    int get_resolution() const;
    void set_resolution(int lx);

  private:
    Cylinder(const Cylinder&);              // not implemented
    Cylinder& operator=(const Cylinder&);   // not implemented

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
