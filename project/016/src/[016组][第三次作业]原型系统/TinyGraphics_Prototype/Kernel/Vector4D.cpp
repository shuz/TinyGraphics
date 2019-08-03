#include "Vector4D.h"
#include "Vector3D.h"

#include <memory.h>
#include <math.h>
#include <stdexcept>

void Vector4D::assign(real x, real y, real z, real w) {
  m_vec[0] = x;   m_vec[1] = y;
  m_vec[2] = z;   m_vec[3] = w;
}

void Vector4D::from_vec3D(const Vector3D& v3) {
  assign(v3(0), v3(1), v3(2), 1.0);
}

Vector3D Vector4D::to_vec3d() const {
  Vector3D v3(m_vec[0], m_vec[1], m_vec[2]);

  if (m_vec[3] == 0.0)
    throw std::invalid_argument("to_vec3d: error: w == 0");

  if (m_vec[3] != 1.0)
    v3.scale(1.0/m_vec[3]);
  return v3;
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
  if (n == 0.0)
    throw std::invalid_argument("normalize: error: norm == 0");
  scale(1.0/n);
}

void Vector4D::scale(real sf) {
  m_vec[0] *= sf; m_vec[1] *= sf;
  m_vec[2] *= sf; m_vec[3] *= sf;
}

const size_t VEC_SIZE = 4*sizeof(real);

bool Vector4D::operator==(const Vector4D& v2) const {
  return memcmp(m_vec, v2.m_vec, VEC_SIZE) == 0; 
}

bool Vector4D::operator!=(const Vector4D& v2) const {
  return memcmp(m_vec, v2.m_vec, VEC_SIZE) != 0;
}
