#include "Vector3D.h"

#include <memory.h>
#include <math.h>
#include "Vector4D.h"
#include "Matrix4D.h"

namespace TinyGraphics {

  const Vector3D Vector3D::ORIGIN(0, 0, 0);
  const Vector3D Vector3D::X_AXIS(1, 0, 0);
  const Vector3D Vector3D::Y_AXIS(0, 1, 0);
  const Vector3D Vector3D::Z_AXIS(0, 0, 1);

  void Vector3D::assign(real x, real y, real z) {
    m_vec[0] = x;
    m_vec[1] = y;
    m_vec[2] = z;
  }

  void Vector3D::from_vec4d(const Vector4D& v4) {
    assign(v4(0), v4(1), v4(2));
    if (v4(3) != 1.0)
      scale(1.0/v4(3));
  }

  Vector4D Vector3D::to_vec4d() const {
    return Vector4D(m_vec[0], m_vec[1], m_vec[2], 1.0);
  }

  real Vector3D::dot_product(const Vector3D& v2) const {
    const Vector3D& v1 = *this;
    return v1(0)*v2(0) +
           v1(1)*v2(1) +
           v1(2)*v2(2);
  }

  Vector3D Vector3D::cross_product(const Vector3D& v2) const {
    const Vector3D& v1 = *this;
    return Vector3D(v1(1)*v2(2) - v1(2)*v2(1),
	    			        v1(2)*v2(0) - v1(0)*v2(2),
			      	      v1(0)*v2(1) - v1(1)*v2(0));
  }

  real Vector3D::square_norm() const {
    return dot_product(*this);
  }

  real Vector3D::norm() const {
    return sqrt(dot_product(*this));
  }

  void Vector3D::normalize() {
    real n = norm();
    scale(1.0/n);
  }

  void Vector3D::scale(real sf) {
    m_vec[0] *= sf;
    m_vec[1] *= sf;
    m_vec[2] *= sf;
  }

  void Vector3D::transform(const Matrix4D& mat) {
    Vector3D origin(0, 0, 0);
    origin *= mat;
    Vector3D dir(*this);
    dir *= mat;
    *this = dir - origin;
  }

  const size_t VEC_SIZE = 3*sizeof(real);

  bool Vector3D::operator==(const Vector3D& v2) const {
    return memcmp(m_vec, v2.m_vec, VEC_SIZE) == 0; 
  }

  bool Vector3D::operator!=(const Vector3D& v2) const {
    return memcmp(m_vec, v2.m_vec, VEC_SIZE) != 0;
  }
}
