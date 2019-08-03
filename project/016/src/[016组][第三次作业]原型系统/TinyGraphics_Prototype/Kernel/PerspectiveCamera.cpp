#include "PerspectiveCamera.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Matrix4D.h"

struct PerspectiveCamera::Impl {
  Impl()
    : vrp(0, 0, 0), vpn(0, 0, 1), vup(0, 1, 0),
      cop(0, 0, 1), umin(-1), umax(1), vmin(-1), vmax(1),
      vpd(0), fcp(0), bcp(1) {}

  Point3D  vrp;     // view reference point
  Vector3D vpn;     // view plane normal
  Vector3D vup;     // view up vector

  Point3D  cop;     // center of projection
  
  real umin, umax;  // view plane window, u axis
  real vmin, vmax;  // view plane window, v axis
  real vpd;         // view plane distance
  real fcp;         // front clipping plane
  real bcp;         // back clipping plane

  mutable Matrix4D nper;    // composed of the matrices below, from left to right

  // THE FOLLOWING MATRICES ARE NOT ACTUALLY USED IN THE CURRUNT VERSION
  Matrix4D wc_vrc;  // world coordinate to viewing-reference coordinate

  const Matrix4D& get_normalization_matrix() const;
};

PerspectiveCamera::PerspectiveCamera()
  : pimpl(new Impl) {}

PerspectiveCamera::~PerspectiveCamera() {
  delete pimpl;
}

void PerspectiveCamera::set_vrp(const Point3D& vrp) {
  pimpl->vrp = vrp;
}

void PerspectiveCamera::set_vpn(const Vector3D& vpn) {
  pimpl->vpn = vpn;
}

void PerspectiveCamera::set_vup(const Vector3D& vup) {
  pimpl->vup = vup;
}

void PerspectiveCamera::set_cop(const Point3D& cop) {
  pimpl->cop = cop;
}

void PerspectiveCamera::set_vpw(real umin, real umax,
                                real vmin, real vmax) {
  pimpl->umin = umin; pimpl->umax = umax;
  pimpl->vmin = vmin; pimpl->vmax = vmax;
}

void PerspectiveCamera::set_vpd(real vpd) {
  pimpl->vpd = vpd;
}

void PerspectiveCamera::set_clip_planes(real front, real back) {
  pimpl->fcp = front; pimpl->bcp = back;
}

const Point3D&  PerspectiveCamera::get_vrp() const {
  return pimpl->vrp;
}

const Vector3D& PerspectiveCamera::get_vpn() const {
  return pimpl->vpn;
}

const Vector3D& PerspectiveCamera::get_vup() const {
  return pimpl->vup;
}

const Point3D&  PerspectiveCamera::get_cop() const {
  return pimpl->cop;
}

void PerspectiveCamera::get_vpw(real& umin, real& umax,
                                real& vmin, real& vmax) const {
  umin = pimpl->umin; umax = pimpl->umax;
  vmin = pimpl->vmin; vmax = pimpl->vmax;
}

real PerspectiveCamera::get_vpd() const {
  return pimpl->vpd;
}

const Matrix4D& PerspectiveCamera::get_normalization_matrix() const {
  return pimpl->get_normalization_matrix();
}

const Matrix4D& PerspectiveCamera::get_projection_matrix() const {
  static const Matrix4D mat(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, -1,
    0, 0, 0, 1);
  return mat;
}

const Matrix4D& PerspectiveCamera::Impl::get_normalization_matrix() const {
  // translate vrp to the origin
  Vector3D minus_vrp(-vrp.x, -vrp.y, -vrp.z);
  Matrix4D t_vrp = Matrix4D::create_translate_matrix(minus_vrp);

  // setup vrc
  Vector3D n_axis(vpn);
  Vector3D u_axis(vup.cross_product(vpn));
  Vector3D v_axis(vpn.cross_product(u_axis));
  n_axis.normalize(); u_axis.normalize(); v_axis.normalize();
  Matrix4D r = Matrix4D::create_orient_matrix(u_axis, v_axis, n_axis);

  // move the view plane to the uv plane and
  // translate the cop so that it lies on the n axis
  Matrix4D t_vp_cop = Matrix4D::create_translate_matrix(Vector3D(cop.x, cop.y, -vpd));

  real y1 = vmin - cop.y;
  real y2 = vmax - cop.y;
  real x1 = umin - cop.x;
  real x2 = umax - cop.x;
  real d = cop.z - vpd;

  real px = x1 + x2;
  real py = y1 + y2;
  real dx = x2 - x1;
  real dy = y2 - y1;
  
  // change the view volume into a regular pyramid
  Matrix4D reg;
  reg(0, 0) = 2*d/dx;
  reg(1, 1) = 2*d/dy;
  reg(2, 0) = -px/dx;
  reg(2, 1) = -py/dy;
  reg(3, 0) = -d*px/dx;
  reg(3, 1) = -d*py/dy;
  
  // scale to canonical view
  Matrix4D s = Matrix4D::create_scale_matrix(1/d);

  nper = t_vrp * r * t_vp_cop * reg * s;
  return nper;
}
