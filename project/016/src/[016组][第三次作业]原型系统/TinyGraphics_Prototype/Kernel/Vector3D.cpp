#include "Vector3D.h"

#include <memory.h>
#include <math.h>
#include <stdexcept>

void Vector3D::assign(real x, real y, real z) {
  m_vec[0] = x;
  m_vec[1] = y;
  m_vec[2] = z;
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
  if (n == 0.0)
    throw std::invalid_argument("normalize: error: norm == 0");
  scale(1.0/n);
}

void Vector3D::scale(real sf) {
  m_vec[0] *= sf;
  m_vec[1] *= sf;
  m_vec[2] *= sf;
}

const size_t VEC_SIZE = 3*sizeof(real);

bool Vector3D::operator==(const Vector3D& v2) const {
  return memcmp(m_vec, v2.m_vec, VEC_SIZE) == 0; 
}

bool Vector3D::operator!=(const Vector3D& v2) const {
  return memcmp(m_vec, v2.m_vec, VEC_SIZE) != 0;
}
