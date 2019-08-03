#ifndef PERSPECTIVE_CAMERA_INCLUDED__
#define PERSPECTIVE_CAMERA_INCLUDED__

#include "Camera.h"
#include "Real.h"

class Point3D;
class Vector3D;

//
// read
//   Computer Graphics Principle and Practice Second Edition in C, Section 6.2
// to get more information to the concepts used below
//
// however, the canonical perspective here is abit different from
// the one on the book. it is defined by:
//   Cop at (0,0,-1)
//   Viewplane coincident with U-V plane
//   Viewplane window bounded by -1 to +1
// reference to the slide from University College London:
//   http://www.cs.ucl.ac.uk/staff/a.meyer/teaching/gmv
// 

class PerspectiveCamera
  : public Camera {
public:
  PerspectiveCamera();
  ~PerspectiveCamera();

  void set_vrp(const Point3D&  vrp);    // view reference point
  void set_vpn(const Vector3D& vpn);    // view plane normal
  void set_vup(const Vector3D& vup);    // view up vector

  void set_cop(const Point3D&  cop);    // center of projection
  void set_vpw(real umin, real umax,
               real vmin, real vmax);   // view plane window
  void set_vpd(real vpd);               // view plane distance
  void set_clip_planes(real front, real back);


  const Point3D&  get_vrp() const;
  const Vector3D& get_vpn() const;
  const Vector3D& get_vup() const;

  const Point3D&  get_cop() const;
  void get_vpw(real& umin, real& umax,
               real& vmin, real& vmax) const;
  real get_vpd() const;

  const Matrix4D& get_normalization_matrix() const;
  const Matrix4D& get_projection_matrix() const;

private:
  PerspectiveCamera(const PerspectiveCamera&);              // not implemented
  PerspectiveCamera& operator=(const PerspectiveCamera&);   // not implemented

private:
  struct Impl;
  Impl *pimpl;
};

#endif
