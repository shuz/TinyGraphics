#include "Position.h"

#include "Primitive3D.h"
#include "Vector3D.h"
#include "Matrix4D.h"

namespace TinyGraphics {

  struct Position::Impl {
    Point3D location;
    Vector3D u_axis, v_axis, n_axis;
    Matrix4D transformer;
    Matrix4D transformer_inv;
    Impl()
      : location(), u_axis(1, 0, 0), v_axis(0, 1, 0), n_axis(0, 0, 1) {}

    Impl(const Point3D& location)
      : location(location), u_axis(1, 0, 0), v_axis(0, 1, 0), n_axis(0, 0, 1) {
      update_transformer();
    }

    Impl(const Point3D& location, const Vector3D& vf, const Vector3D& vup)
      : location(location), v_axis(vup), n_axis(vf) {
      normalize_coord();
      update_transformer();
    }

    Impl *clone() const {
      return new Impl(*this);
    }

    void update_transformer() {
      // translate location to the origin
      Matrix4D t_location = Matrix4D::create_translate_matrix(-location.to_vec3d());
      Matrix4D r = Matrix4D::create_orient_matrix(u_axis, v_axis, n_axis);
      transformer = t_location * r;
      transformer_inv = transformer.inverse();
    }

    void update_coord() {
      location = Point3D::ORIGIN;
      u_axis = Vector3D::X_AXIS;
      v_axis = Vector3D::Y_AXIS;
      n_axis = Vector3D::Z_AXIS;
      location.transform(transformer_inv);
      u_axis.transform(transformer_inv);
      v_axis.transform(transformer_inv);
      n_axis.transform(transformer_inv);
    }

    void normalize_coord() {
      u_axis = v_axis.cross_product(n_axis);
      v_axis = n_axis.cross_product(u_axis);
      u_axis.normalize();  v_axis.normalize();  n_axis.normalize();
    }
  };

  Position::Position() 
    : pimpl(new Impl()) {}

  Position::Position(const Point3D& location) 
    : pimpl(new Impl(location)) {}

  Position::Position(const Point3D& location, const Vector3D& vf, const Vector3D& vup)
    : pimpl(new Impl(location, vf, vup)) {}

  Position::Position(const Position& rhs)
    : pimpl(rhs.pimpl->clone()) {}

  Position& Position::operator=(const Position& rhs) {
    Impl *new_pimpl = rhs.pimpl->clone();
    delete pimpl;
    pimpl = new_pimpl;
    return *this;
  }

  Position::~Position() {
    delete pimpl;
  }

  const Point3D& Position::get_location() const {
    return pimpl->location;
  }

  void Position::set_location(const Point3D& location) {
    pimpl->location = location;
    pimpl->update_transformer();
  }

  const Vector3D& Position::get_up_vector() const {
    return pimpl->v_axis;
  }

  void Position::set_up_vector(const Vector3D& vup) {
    pimpl->v_axis = vup;
    pimpl->normalize_coord();
    pimpl->update_transformer();
  }

  const Vector3D& Position::get_front_vector() const {
    return pimpl->n_axis;
  }

  void Position::set_front_vector(const Vector3D& vf) {
    pimpl->n_axis = vf;
    pimpl->normalize_coord();
    pimpl->update_transformer();
  }

  void Position::translate(const Vector3D& vec) {
    pimpl->location += vec;
    pimpl->update_transformer();
  }

  void Position::rotate_x(real angle) {
    rotate(Vector3D::X_AXIS, angle);
  }

  void Position::rotate_y(real angle) {
    rotate(Vector3D::Y_AXIS, angle);
  }

  void Position::rotate_z(real angle) {
    rotate(Vector3D::Z_AXIS, angle);
  }

  void Position::rotate(const Vector3D& axis, real angle) {
    Vector3D n_axis(axis);
    n_axis.normalize();
    Matrix4D rot_mat(Matrix4D::create_rotate_matrix(n_axis, angle));
    pimpl->u_axis *= rot_mat;
    pimpl->v_axis *= rot_mat;
    pimpl->n_axis *= rot_mat;
    pimpl->update_transformer();
  }

  void Position::rotate(const Point3D& point, const Vector3D& axis, real angle) {
    Vector3D n_axis(axis);
    n_axis.normalize();
    Matrix4D rot_mat(Matrix4D::create_rotate_matrix(point.to_vec3d(), n_axis, angle));
    pimpl->location.transform(rot_mat);
    pimpl->u_axis.transform(rot_mat);
    pimpl->v_axis.transform(rot_mat);
    pimpl->n_axis.transform(rot_mat);
    pimpl->update_transformer();
  }

  void Position::transform(const Position& pos) {
    pimpl->transformer *= pos.get_transformer();
    pimpl->transformer_inv = pos.get_transformer_inv() * pimpl->transformer_inv;
    pimpl->update_coord();
  }

  const Matrix4D& Position::get_transformer() const {
    return pimpl->transformer;
  }

  const Matrix4D& Position::get_transformer_inv() const {
    return pimpl->transformer_inv;
  }
}
