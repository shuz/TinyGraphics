#ifndef VECTOR_4D_INCLUDED__
#define VECTOR_4D_INCLUDED__

#include <assert.h>
#include "Real.h"

namespace TinyGraphics {

  class Matrix4D;

  #define CHECK_RANGE(n)        \
    do {                        \
      assert(0 <= n && n < 4);  \
    } while (false)

  class Vector4D {
  private:
    real m_vec[4];

  public:
    Vector4D() {
      assign(0, 0, 0, 0);
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

    real dot_product(const Vector4D& rhs) const;
    real square_norm() const;
    real norm() const;

    void normalize();
    void scale(real sf);
    // transform differs from operator *, it uses the following formula:
    // transform(this) == this * mat - 0 * mat;
    void transform(const Matrix4D& mat);

    Vector4D& operator+=(const Vector4D& rhs) {
      m_vec[0] += rhs.m_vec[0];
      m_vec[1] += rhs.m_vec[1];
      m_vec[2] += rhs.m_vec[2];
      m_vec[3] += rhs.m_vec[3];
      return *this;
    }

    Vector4D operator+(const Vector4D& rhs) const {
      return Vector4D(*this) += rhs;
    }
  
    Vector4D& operator-=(const Vector4D& rhs) {
      m_vec[0] -= rhs.m_vec[0];
      m_vec[1] -= rhs.m_vec[1];
      m_vec[2] -= rhs.m_vec[2];
      m_vec[3] -= rhs.m_vec[3];
      return *this;
    }

    Vector4D operator-(const Vector4D& rhs) const {
      return Vector4D(*this) -= rhs;
    }

    Vector4D operator-() const {
      return Vector4D(-m_vec[0], -m_vec[1], -m_vec[2], -m_vec[3]);
    }

    Vector4D& operator*=(real sf) {
      scale(sf);
      return *this;
    }

    Vector4D operator*(real sf) const {
      return Vector4D(*this) *= sf;
    }

    bool operator==(const Vector4D& rhs) const;
    bool operator!=(const Vector4D& rhs) const;
  };

  inline
  Vector4D operator*(real sf, const Vector4D& vec) {
    return vec*sf;
  }

  #undef CHECK_RANGE
}

#endif
