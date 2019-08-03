#ifndef PARALLEL_CAMERA_INCLUDED__
#define PARALLEL_CAMERA_INCLUDED__

#include "Camera.h"

namespace TinyGraphics {

  //
  // read
  //   Computer Graphics Principle and Practice Second Edition in C, Section 6.2
  // to get more information to the concepts used below
  //

  class ParallelCamera : public Camera {
  public:
    ParallelCamera();
    ~ParallelCamera();

    const Position& get_position() const;
    const Vector3D& get_project_direction() const;

    void get_vpw(real& width, real& height) const;
    void get_vpw_resolution(int& nx, int& ny) const;

    void set_position(const Position& pos);
    void set_project_direction(const Vector3D& vec);

    void set_vpw(real width, real height);
    void set_vpw_resolution(int nx, int ny);

    void scale(real sf);

    const Matrix4D& get_normalization_matrix() const;
    const Matrix4D& get_normalization_matrix_inv() const;
    const Matrix4D& get_projection_matrix() const;

    Ray get_ray(int x, int y) const;

  private:
    ParallelCamera(const ParallelCamera&);              // not implemented
    ParallelCamera& operator=(const ParallelCamera&);   // not implemented

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
