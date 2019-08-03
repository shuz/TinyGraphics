#include "ParallelCamera.h"

#include "Primitive3D.h"
#include "Position.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"
#include "Ray.h"

namespace TinyGraphics {

  struct ParallelCamera::Impl {
    Impl() 
      : proj_dir(0, 0, 1),  width(1), height(1), nu(0), nv(0) {
        compute_normalization_matrix();
      }

      Position pos;
      Vector3D proj_dir;    // project direction from object to view plane
      real width, height;   // view plane windows's width and height
      int nu, nv;           // view plane window resolution

      Matrix4D nper;        // composed of the matrices below, from left to right
      Matrix4D nper_inv;    // inverse of nper

      void compute_normalization_matrix();
  };

  ParallelCamera::ParallelCamera()
    : pimpl(new Impl) {}

  ParallelCamera::~ParallelCamera() {
    delete pimpl;
  }

  void ParallelCamera::set_position(const Position& pos) {
    pimpl->pos = pos;
    pimpl->compute_normalization_matrix();
  }

  void ParallelCamera::set_project_direction(const Vector3D& proj_dir) {
    pimpl->proj_dir = proj_dir;
    pimpl->compute_normalization_matrix();
  }

  void ParallelCamera::set_vpw(real width, real height) {
    pimpl->width = width;
    pimpl->height = height;
    pimpl->compute_normalization_matrix();
  }

  void ParallelCamera::set_vpw_resolution(int nu, int nv) {
    pimpl->nu = nu;
    pimpl->nv = nv;
  }

  const Position&  ParallelCamera::get_position() const {
    return pimpl->pos;
  }

  const Vector3D& ParallelCamera::get_project_direction() const {
    return pimpl->proj_dir;
  }

  void ParallelCamera::get_vpw(real& width, real& height) const {
    width = pimpl->width;
    height = pimpl->height;
  }

  void ParallelCamera::get_vpw_resolution(int& nx, int& ny) const {
    nx = pimpl->nu;
    ny = pimpl->nv;
  }

  const Matrix4D& ParallelCamera::get_normalization_matrix() const {
    return pimpl->nper;
  }

  const Matrix4D& ParallelCamera::get_normalization_matrix_inv() const {
    return pimpl->nper_inv;
  }

  const Matrix4D& ParallelCamera::get_projection_matrix() const {
    return pimpl->nper;
  }

  void ParallelCamera::scale(real sf) {
    pimpl->width  *= sf;
    pimpl->height *= sf;
    pimpl->compute_normalization_matrix();
  }

  void ParallelCamera::Impl::compute_normalization_matrix() {
    // setup viewing reference coordinate
    Matrix4D vrc = pos.get_transformer();

    Vector3D pd(proj_dir);
    pd.normalize();
    Matrix4D shear = Matrix4D::create_orient_matrix(Vector3D(1, 0, 0), Vector3D(0, 1, 0), pd);
    Matrix4D scale = Matrix4D::create_scale_matrix(Vector3D(2/width, 2/height, 1));

    nper = vrc * shear * scale;
    nper_inv = nper.inverse();
  }

  Ray ParallelCamera::get_ray(int x, int y) const {
    Point3D screen(-1, -1, 0);
    screen.x += x*(2.0/pimpl->nu);
    screen.y += y*(2.0/pimpl->nv);
    return to_world_coord(Ray(Point3D(screen.x, screen.y, 1), screen));
  }
}
