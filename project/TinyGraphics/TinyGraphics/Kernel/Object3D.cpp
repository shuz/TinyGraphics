#include "Object3D.h"
#include "Position.h"
#include "Vector3D.h"

namespace TinyGraphics {

  Object3D::Object3D() {}
  Object3D::~Object3D() {}


  const Point3D& Object3D::get_location() const {
    return get_position().get_location();
  }

  const Vector3D& Object3D::get_front_vector() const {
    return get_position().get_front_vector();
  }

  const Vector3D& Object3D::get_up_vector() const {
    return get_position().get_up_vector();
  }

  void Object3D::set_location(const Point3D& point) {
    Position pos = get_position();
    pos.set_location(point);
    set_position(pos);
  }

  void Object3D::set_front_vector(const Vector3D& vec) {
    Position pos = get_position();
    pos.set_front_vector(vec);
    set_position(pos);
  }

  void Object3D::set_up_vector(const Vector3D& vec) {
    Position pos = get_position();
    pos.set_up_vector(vec);
    set_position(pos);
  }


  void Object3D::translate(const Vector3D& vec) {
    Position pos = get_position();
    pos.translate(vec);
    set_position(pos);
  }

  void Object3D::rotate_x(real angle) {
    rotate(Vector3D::X_AXIS, angle);
  }

  void Object3D::rotate_y(real angle) {
    rotate(Vector3D::Y_AXIS, angle);
  }

  void Object3D::rotate_z(real angle) {
    rotate(Vector3D::Z_AXIS, angle);
  }

  void Object3D::rotate(const Vector3D& axis, real angle) {
    Position pos = get_position();
    pos.rotate(axis, angle);
    set_position(pos);
  }

  void Object3D::rotate(const Point3D& point, const Vector3D& axis, real angle) {
    Position pos = get_position();
    pos.rotate(point, axis, angle);
    set_position(pos);
  }

  void Object3D::transform(const Position& p) {
    Position pos = get_position();
    pos.transform(p);
    set_position(pos);
  }
}