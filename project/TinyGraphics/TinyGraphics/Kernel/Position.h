#ifndef POSITION_INCLUDED__
#define POSITION_INCLUDED__

#include "Real.h"

namespace TinyGraphics {

  class Point3D;
  class Vector3D;
  class Matrix4D;

  class Position {
  public:
    Position();
    Position(const Point3D& location);
    Position(const Point3D& location, const Vector3D& vf, const Vector3D& vup);
    Position(const Position& rhs);
    Position& operator=(const Position& rhs);

    ~Position();

    const Point3D& get_location() const;
    void set_location(const Point3D& point);

    // front-vector indicates the front direction
    const Vector3D& get_front_vector() const;
    void set_front_vector(const Vector3D& vec);
  
    // up-vector indicates the up direction
    const Vector3D& get_up_vector() const;
    void set_up_vector(const Vector3D& vec);

    // translate the location by vec
    void translate(const Vector3D& vec);

    // rotate around x axis starting from the location by angle
    void rotate_x(real angle);

    // rotate around y axis starting from the location by angle
    void rotate_y(real angle);

    // rotate around z axis starting from the location by angle
    void rotate_z(real angle);

    // rotate around axis starting from the location by angle
    void rotate(const Vector3D& axis, real angle);

    // rotate around axis starting from the point by angle
    void rotate(const Point3D& point, const Vector3D& axis, real angle);

    // every Position represents a coordinate system relative to some other coord system,
    // call it Position p's ether coordinate system, the e.c.s
    // t1.transform(t2) make t1 the coord system relative to old t1's e.c.s,
    // and represent t2 with its old e.c.s replaced by t1
    void transform(const Position& pos);

    // transformer transforms from the e.c.s coord to the local coord
    const Matrix4D& get_transformer() const;
    const Matrix4D& get_transformer_inv() const;

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
