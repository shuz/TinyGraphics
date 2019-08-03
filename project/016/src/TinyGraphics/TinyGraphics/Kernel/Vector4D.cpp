#include "Vector4D.h"

#include <memory.h>
#include <math.h>
#include "Matrix4D.h"

namespace TinyGraphics {

  void Vector4D::assign(real x, real y, real z, real w) {
    m_vec[0] = x;   m_vec[1] = y;
    m_vec[2] = z;   m_vec[3] = w;
  }

  real Vector4D::dot_product(const Vector4D& v2) const {
    const Vector4D& v1 = *this;
    return v1(0)*v2(0) + v1(1)*v2(1) +
           v1(2)*v2(2) + v1(3)*v2(3);
  }

  real Vector4D::square_norm() const {
    return dot_product(*this);
  }

  real Vector4D::norm() const {
    return sqrt(dot_product(*this));
  }

  void Vector4D::normalize() {
    real n = norm();
    scale(1.0/n);
  }

  void Vector4D::scale(real sf) {
    m_vec[0] *= sf; m_vec[1] *= sf;
    m_vec[2] *= sf; m_vec[3] *= sf;
  }

  void Vector4D::transform(const Matrix4D& mat) {
    Vector4D origin(0, 0, 0, 0);
    origin *= mat;
    Vector4D dir(*this);
    dir *= mat;
    *this = dir - origin;
  }

  const size_t VEC_SIZE = 4*sizeof(real);

  bool Vector4D::operator==(const Vector4D& v2) const {
    return memcmp(m_vec, v2.m_vec, VEC_SIZE) == 0; 
  }

  bool Vector4D::operator!=(const Vector4D& v2) const {
    return memcmp(m_vec, v2.m_vec, VEC_SIZE) != 0;
  }
}
