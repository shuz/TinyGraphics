#include "Camera.h"
#include "Primitive3D.h"
#include "Position.h"
#include "Vector3D.h"
#include "Ray.h"

namespace TinyGraphics {

  Camera::Camera() {}
  Camera::~Camera() {}

  Ray Camera::to_canonical_coord(const Ray& ray) const {
    Ray rtv(ray);
    rtv.transform(get_normalization_matrix());
    return rtv;
  }

  Ray Camera::to_world_coord(const Ray& ray) const {
    Ray rtv(ray);
    rtv.transform(get_normalization_matrix_inv());
    return rtv;
  }

  Vector3D Camera::to_canonical_coord(const Vector3D& vec) const {
    Vector3D rtv(vec);
    rtv.transform(get_normalization_matrix());
    return rtv;
  }

  Vector3D Camera::to_world_coord(const Vector3D& ray) const {
    Vector3D rtv(ray);
    rtv.transform(get_normalization_matrix_inv());
    return rtv;
  }

  Point3D Camera::to_canonical_coord(const Point3D& vec) const {
    Point3D rtv(vec);
    rtv.transform(get_normalization_matrix());
    return rtv;
  }

  Point3D Camera::to_world_coord(const Point3D& ray) const {
    Point3D rtv(ray);
    rtv.transform(get_normalization_matrix_inv());
    return rtv;
  }


  void Camera::adjust_aspect_ratio(real aspect_ratio) {
    real width, height;
    get_vpw(width, height);
    height = width * aspect_ratio;
    set_vpw(width, height);
  }


  const Point3D& Camera::get_location() const {
    return get_position().get_location();
  }

  const Vector3D& Camera::get_front_vector() const {
    return get_position().get_front_vector();
  }

  const Vector3D& Camera::get_up_vector() const {
    return get_position().get_up_vector();
  }

  void Camera::set_location(const Point3D& point) {
    Position pos = get_position();
    pos.set_location(point);
    set_position(pos);
  }

  void Camera::set_front_vector(const Vector3D& vec) {
    Position pos = get_position();
    pos.set_front_vector(vec);
    set_position(pos);
  }

  void Camera::set_up_vector(const Vector3D& vec) {
    Position pos = get_position();
    pos.set_up_vector(vec);
    set_position(pos);
  }


  void Camera::translate(const Vector3D& vec) {
    Position pos = get_position();
    pos.translate(vec);
    set_position(pos);
  }

  void Camera::rotate_x(real angle) {
    rotate(Vector3D::X_AXIS, angle);
  }

  void Camera::rotate_y(real angle) {
    rotate(Vector3D::Y_AXIS, angle);
  }

  void Camera::rotate_z(real angle) {
    rotate(Vector3D::Z_AXIS, angle);
  }

  void Camera::rotate(const Vector3D& axis, real angle) {
    Position pos = get_position();
    pos.rotate(axis, angle);
    set_position(pos);
  }

  void Camera::rotate(const Point3D& point, const Vector3D& axis, real angle) {
    Position pos = get_position();
    pos.rotate(point, axis, angle);
    set_position(pos);
  }

  void Camera::transform(const Position& p) {
    Position pos = get_position();
    pos.transform(p);
    set_position(pos);
  }
}
