#ifndef VECTOR_4D_INCLUDED__
#define VECTOR_4D_INCLUDED__

#include <assert.h>
#include "Real.h"

#define CHECK_RANGE(n)        \
  do {                        \
    assert(0 <= n && n < 4);  \
  } while (false)

class Vector3D;

class Vector4D {
private:
  real m_vec[4];

public:
  Vector4D() {
    assign(0, 0, 0, 0);
  }

  explicit Vector4D(const Vector3D& v3) {
    from_vec3D(v3);
  }

  Vector4D(real x, real y, real z, real w) {
    assign(x, y, z, w);
  }

  void assign(real x, real y, real z, real w);

  real operator()(int i) const {
    CHECK_RANGE(i);
    return m_vec[i];
  }

  real& operator()(int i) {
    CHECK_RANGE(i);
    return m_vec[i];
  }

  Vector4D& operator+=(const Vector4D& rhs) {
    m_vec[0] += rhs.m_vec[0];
    m_vec[1] += rhs.m_vec[1];
    m_vec[2] += rhs.m_vec[2];
    m_vec[3] += rhs.m_vec[3];
  }

  Vector4D operator+(const Vector4D& rhs) const {
    return Vector4D(*this) += rhs;
  }

  //
  // convertions from and to Vector3D
  // treating v4 as the homogeneous coordinate of v3
  //
  // v4 = (v3.x, v3y, v3y, 1)
  void     from_vec3D(const Vector3D& v3);
  // v3 = (v4.x, v4.y, v4.z) / v4.w
  Vector3D to_vec3d() const;

  real dot_product(const Vector4D& rhs) const;
  real square_norm() const;
  real norm() const;

  void normalize();     // throws std::invalid_argument if norm == 0
  void scale(real sf);

  bool operator==(const Vector4D& rhs) const;
  bool operator!=(const Vector4D& rhs) const;
};

#undef CHECK_RANGE

#endif
