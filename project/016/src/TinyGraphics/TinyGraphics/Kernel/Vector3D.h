#ifndef VECTOR_3D_INCLUDED__
#define VECTOR_3D_INCLUDED__

#include <assert.h>
#include "Real.h"

namespace TinyGraphics {

  #define CHECK_RANGE(n)        \
    do {                        \
      assert(0 <= n && n < 3);  \
    } while (false)

  class Vector4D;
  class Matrix4D;

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

    explicit Vector3D(const Vector4D& v4) {
      from_vec4d(v4);
    }

    real operator()(int i) const {
      CHECK_RANGE(i);
      return m_vec[i];
    }

    real& operator()(int i) {
      CHECK_RANGE(i);
      return m_vec[i];
    }

    //
    // convertions from and to Vector4D
    // treating v4 as the homogeneous coordinate of v3
    //
    // v3 = (v4.x, v4.y, v4.z) / v4.w
    Vector4D to_vec4d() const;
    // v4 = (v3.x, v3y, v3y, 1)
    void     from_vec4d(const Vector4D& v4);

    void assign(real x, real y, real z);
    real dot_product(const Vector3D& rhs) const;
    Vector3D cross_product(const Vector3D& rhs) const;
    real square_norm() const;
    real norm() const;

    Vector3D& operator+=(const Vector3D& rhs) {
      m_vec[0] += rhs.m_vec[0];
      m_vec[1] += rhs.m_vec[1];
      m_vec[2] += rhs.m_vec[2];
      return *this;
    }

    Vector3D operator+(const Vector3D& rhs) const {
      return Vector3D(*this) += rhs;
    }
  
    Vector3D& operator-=(const Vector3D& rhs) {
      m_vec[0] -= rhs.m_vec[0];
      m_vec[1] -= rhs.m_vec[1];
      m_vec[2] -= rhs.m_vec[2];
      return *this;
    }

    Vector3D operator-(const Vector3D& rhs) const {
      return Vector3D(*this) -= rhs;
    }

    Vector3D operator-() const {
      return Vector3D(-m_vec[0], -m_vec[1], -m_vec[2]);
    }

    void normalize();
    void scale(real sf);
    // transform differs from operator *, it uses the following formula:
    // transform(this) == this * mat - 0 * mat;
    void transform(const Matrix4D& mat);

    Vector3D& operator*=(real sf) {
      scale(sf);
      return *this;
    }

    Vector3D operator*(real sf) const {
      return Vector3D(*this) *= sf;
    }

    bool operator==(const Vector3D& rhs) const;
    bool operator!=(const Vector3D& rhs) const;

    static const Vector3D ORIGIN;
    static const Vector3D X_AXIS;
    static const Vector3D Y_AXIS;
    static const Vector3D Z_AXIS;
  };

  inline
  Vector3D operator*(real sf, const Vector3D& vec) {
    return vec*sf;
  }

  #undef CHECK_RANGE
}

#endif
