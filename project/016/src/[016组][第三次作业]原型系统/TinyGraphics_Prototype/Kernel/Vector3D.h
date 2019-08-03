#ifndef VECTOR_3D_INCLUDED__
#define VECTOR_3D_INCLUDED__

#include <assert.h>
#include "Real.h"

#define CHECK_RANGE(n)        \
  do {                        \
    assert(0 <= n && n < 3);  \
  } while (false)


class Vector3D {
private:
  real m_vec[3];

public:
  Vector3D() {
    assign(0, 0, 0);
  }

  Vector3D(real x, real y, real z) {
    assign(x, y, z);
  }

  real operator()(int i) const {
    CHECK_RANGE(i);
    return m_vec[i];
  }

  real& operator()(int i) {
    CHECK_RANGE(i);
    return m_vec[i];
  }

  void assign(real x, real y, real z);
  real dot_product(const Vector3D& rhs) const;
  Vector3D cross_product(const Vector3D& rhs) const;
  real square_norm() const;
  real norm() const;

  Vector3D& operator+=(const Vector3D& rhs) {
    m_vec[0] += rhs.m_vec[0];
    m_vec[1] += rhs.m_vec[1];
    m_vec[2] += rhs.m_vec[2];
  }

  Vector3D operator+(const Vector3D& rhs) const {
    return Vector3D(*this) += rhs;
  }
  
  void normalize();     // throws std::invalid_argument if norm == 0
  void scale(real sf);

  bool operator==(const Vector3D& rhs) const;
  bool operator!=(const Vector3D& rhs) const;
};

#undef CHECK_RANGE

#endif
