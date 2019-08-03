#include "PerspectiveCamera.h"

#include "Primitive3D.h"
#include "Primitive2D.h"
#include "Position.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"
#include "Ray.h"

namespace TinyGraphics {

  struct PerspectiveCamera::Impl {
    Impl() 
      : proj_dir(0, 0, 1), cop_dist(1), width(1), height(1), nu(0), nv(0) {
      compute_normalization_matrix();
    }

    Position pos;
    Vector3D proj_dir;    // project direction from object to view plane
    real cop_dist;        // distance from camera location to cop along project_direction
    real width, height;   // view plane windows's width and height
    int nu, nv;           // view plane window resolution

    Matrix4D nper;        // composed of the matrices below, from left to right
    Matrix4D nper_inv;    // inverse of nper
    Matrix4D proj;        // projection matrix

    void compute_normalization_matrix();
  };

  PerspectiveCamera::PerspectiveCamera()
    : pimpl(new Impl) {}

  PerspectiveCamera::~PerspectiveCamera() {
    delete pimpl;
  }

  void PerspectiveCamera::set_position(const Position& pos) {
    pimpl->pos = pos;
    pimpl->compute_normalization_matrix();
  }

  void PerspectiveCamera::set_project_direction(const Vector3D& proj_dir) {
    pimpl->proj_dir = proj_dir;
    pimpl->compute_normalization_matrix();
  }

  void PerspectiveCamera::set_cop_distance(real cop_dist) {
    pimpl->cop_dist = cop_dist;
    pimpl->compute_normalization_matrix();
  }

  void PerspectiveCamera::set_vpw(real width, real height) {
    pimpl->width = width;
    pimpl->height = height;
    pimpl->compute_normalization_matrix();
  }

  void PerspectiveCamera::set_vpw_resolution(int nu, int nv) {
    pimpl->nu = nu;
    pimpl->nv = nv;
  }

  const Position&  PerspectiveCamera::get_position() const {
    return pimpl->pos;
  }

  const Vector3D& PerspectiveCamera::get_project_direction() const {
    return pimpl->proj_dir;
  }

  real PerspectiveCamera::get_cop_distance() const {
    return pimpl->cop_dist;
  }

  void PerspectiveCamera::get_vpw(real& width, real& height) const {
    width = pimpl->width;
    height = pimpl->height;
  }

  void PerspectiveCamera::get_vpw_resolution(int& nx, int& ny) const {
    nx = pimpl->nu;
    ny = pimpl->nv;
  }

  const Matrix4D& PerspectiveCamera::get_normalization_matrix() const {
    return pimpl->nper;
  }

  const Matrix4D& PerspectiveCamera::get_normalization_matrix_inv() const {
    return pimpl->nper_inv;
  }

  const Matrix4D& PerspectiveCamera::get_projection_matrix() const {
    return pimpl->proj;
  }

  void PerspectiveCamera::scale(real sf) {
    pimpl->cop_dist *= sf;
    pimpl->width    *= sf;
    pimpl->height   *= sf;
    pimpl->compute_normalization_matrix();
  }

  void PerspectiveCamera::Impl::compute_normalization_matrix() {
    // setup viewing reference coordinate
    Matrix4D vrc = pos.get_transformer();

    Point3D cop(proj_dir * cop_dist);
    // translate the cop so that it lies on the n axis
    Matrix4D t_vp_cop = Matrix4D::create_translate_matrix(Vector3D(-cop.x, -cop.y, 0));

    
    real y1 = -height/2 - cop.y;
    real y2 =  height/2 - cop.y;
    real x1 = -width/2 - cop.x;
    real x2 =  width/2 - cop.x;
    real d = cop.z;

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

    static const Matrix4D mat(
      1, 0, 0, 0,
      0, 1, 0, 0,
      0, 0, 1, -1,
      0, 0, 0, 1
    );

    nper = vrc * t_vp_cop * reg * s;
    nper_inv = nper.inverse();

    proj = nper * mat;
  }

  Ray PerspectiveCamera::get_ray(int x, int y) const {
    Point3D screen(-1, -1, 0);
    screen.x += x*(2.0/pimpl->nu);
    screen.y += y*(2.0/pimpl->nv);
    return to_world_coord(Ray(Point3D(0, 0, 1), screen));
  }

}
