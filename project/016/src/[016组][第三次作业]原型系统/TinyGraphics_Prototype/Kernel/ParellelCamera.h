#ifndef PARELLEL_CAMERA_INCLUDED__
#define PARELLEL_CAMERA_INCLUDED__

#include "Vector3D.h"

class Matrix4D;

//
// read
//   Computer Graphics Principle and Practice Second Edition in C, Section 6.2
// to get more information to the concepts used below
// 

// NOT IMPLEMENTED THIS TIME!

class ParellelCamera {
public:
  enum ProjectionType {
    PARELLEL, PERSPECTIVE
  };

  ProjectionType projection_type;

  Vector3D view_reference_point;
  Vector3D view_plane_normal;
  Vector3D view_up_vector;

  Vector3D projection_reference_point;
  
  real umin, umax;
  real vmin, vmax;
  real view_plane_distance;
  real front_clipping_plane;
  real back_clipping_plane;

  Matrix4D get_normalization_matrix();

  const Matrix4D& get_projection_matrix() const = 0;
};

#endif
