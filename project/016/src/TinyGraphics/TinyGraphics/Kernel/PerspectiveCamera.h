#ifndef PERSPECTIVE_CAMERA_INCLUDED__
#define PERSPECTIVE_CAMERA_INCLUDED__

#include "Camera.h"

namespace TinyGraphics {

  //
  // read
  //   Computer Graphics Principle and Practice Second Edition in C, Section 6.2
  // to get more information to the concepts used below
  //
  // however, the canonical perspective here is different from
  // the one on the book. it is defined by:
  //   Cop at (0,0,-1)
  //   View plane coincident with U-V plane
  //   View plane window bounded by -1 to +1
  // reference to the slide from University College London:
  //   http://www.cs.ucl.ac.uk/staff/a.meyer/teaching/gmv
  // 

  class PerspectiveCamera : public Camera {
  public:
    PerspectiveCamera();
    ~PerspectiveCamera();

    const Position& get_position() const;
    const Vector3D& get_project_direction() const;

    // distance from camera location to cop along project_direction
    real get_cop_distance() const;
    void get_vpw(real& width, real& height) const;
    void get_vpw_resolution(int& nx, int& ny) const;

    void set_position(const Position& pos);
    void set_project_direction(const Vector3D& vec);

    void set_cop_distance(real cop_dist);
    void set_vpw(real width, real height);
    void set_vpw_resolution(int nx, int ny);

    void scale(real sf);

    const Matrix4D& get_normalization_matrix() const;
    const Matrix4D& get_normalization_matrix_inv() const;
    const Matrix4D& get_projection_matrix() const;

    Ray get_ray(int x, int y) const;

  private:
    PerspectiveCamera(const PerspectiveCamera&);              // not implemented
    PerspectiveCamera& operator=(const PerspectiveCamera&);   // not implemented

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
