#ifndef CAMERA_INCLUDED__
#define CAMERA_INCLUDED__

#include "Real.h"

namespace TinyGraphics {

  class Matrix4D;
  class Vector3D;
  class Ray;
  class Point3D;
  class Position;

  class Camera {
  public:
    virtual
    ~Camera() = 0;

    virtual
    const Position& get_position() const = 0;

    // project direction from object to view plane
    virtual
    const Vector3D& get_project_direction() const = 0;

    virtual
    void get_vpw(real& width, real& height) const = 0;

    virtual
    void get_vpw_resolution(int& nx, int& ny) const = 0;

    virtual
    void set_position(const Position& pos) = 0;

    virtual
    void set_project_direction(const Vector3D& vec) = 0;

    virtual
    void set_vpw(real width, real height) = 0;

    // set the resolution for ray iteration. 
    // from (0, 0) to (nx, ny) inclusive
    virtual
    void set_vpw_resolution(int nx, int ny) = 0;

    // get the ray shot to the corresponding position of the window
    // (x, y) ranges from (0, 0) to (nu, nv) inclusive
    virtual
    Ray get_ray(int x, int y) const = 0;

    virtual
    void scale(real sf) = 0;

    virtual
    const Matrix4D& get_normalization_matrix() const = 0;

    virtual
    const Matrix4D& get_normalization_matrix_inv() const = 0;

    virtual
    const Matrix4D& get_projection_matrix() const = 0;

    // adjust the height of vpw by aspect_ratio and width
    void adjust_aspect_ratio(real aspect_ratio);

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

    Vector3D to_world_coord(const Vector3D& vec) const;
    Point3D  to_world_coord(const Point3D& point) const;
    Ray      to_world_coord(const Ray& ray) const;

    Vector3D to_canonical_coord(const Vector3D& vec) const;
    Point3D  to_canonical_coord(const Point3D& point) const;
    Ray      to_canonical_coord(const Ray& ray) const;

  protected:
    Camera();

  private:
    Camera(const Camera&);              // not implemented
    Camera& operator=(const Camera&);   // not implemented
  };
}

#endif
