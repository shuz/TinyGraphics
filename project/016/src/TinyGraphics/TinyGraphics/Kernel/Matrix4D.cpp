#include "Matrix4D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include <memory.h>

namespace TinyGraphics {

  const Matrix4D Matrix4D::IDENTITY(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1
  );

  const Matrix4D Matrix4D::ZERO(
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0
  );

  void Matrix4D::assign(real m00, real m01, real m02, real m03,
                        real m10, real m11, real m12, real m13,
                        real m20, real m21, real m22, real m23,
                        real m30, real m31, real m32, real m33) {
    m_mat[ 0] = m00; m_mat[ 1] = m01; m_mat[ 2] = m02; m_mat[ 3] = m03;
    m_mat[ 4] = m10; m_mat[ 5] = m11; m_mat[ 6] = m12; m_mat[ 7] = m13;
    m_mat[ 8] = m20; m_mat[ 9] = m21; m_mat[10] = m22; m_mat[11] = m23;
    m_mat[12] = m30; m_mat[13] = m31; m_mat[14] = m32; m_mat[15] = m33;
  }

  Matrix4D Matrix4D::operator*(const Matrix4D& rhs) const {
    Matrix4D ret_val;
    const Matrix4D& lhs = *this;

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        ret_val(i, j) = 0;
        for (int k = 0; k < 4; ++k) {
          ret_val(i, j) += lhs(i, k) * rhs(k, j);
        }
      }
    }
    return ret_val;
  }

  Matrix4D& Matrix4D::operator*=(const Matrix4D& rhs) {
    return (*this) = (*this) * rhs;
  }

  Matrix4D Matrix4D::transpose() const {
    Matrix4D ret_val;
    const Matrix4D& m = *this;

    for (int i = 0; i < 4; ++i) {
      for (int j = 0; j < 4; ++j) {
        ret_val(i, j) = m(j, i);
      }
    }
    return ret_val;
  }


  Vector4D operator*(const Vector4D& v, const Matrix4D& m) {
    Vector4D ret_val;

    ret_val(0) = v(0)*m(0, 0) + v(1)*m(1, 0) +
                 v(2)*m(2, 0) + v(3)*m(3, 0);
    ret_val(1) = v(0)*m(0, 1) + v(1)*m(1, 1) +
                 v(2)*m(2, 1) + v(3)*m(3, 1);
    ret_val(2) = v(0)*m(0, 2) + v(1)*m(1, 2) +
                 v(2)*m(2, 2) + v(3)*m(3, 2);
    ret_val(3) = v(0)*m(0, 3) + v(1)*m(1, 3) +
                 v(2)*m(2, 3) + v(3)*m(3, 3);

    return ret_val;
  }

  Vector4D& operator*=(Vector4D& v, const Matrix4D& m) {
    return v = v * m; 
  }

  Vector3D operator*(const Vector3D& v, const Matrix4D& m) {
    Vector4D v4 = v.to_vec4d();
    return Vector3D(v4*m);
  }

  Vector3D& operator*=(Vector3D& v, const Matrix4D& m) {
    return v = v * m;
  }

  const size_t MAT_SIZE = 16*sizeof(real);

  bool Matrix4D::operator==(const Matrix4D& rhs) const {
    return memcmp(m_mat, rhs.m_mat, MAT_SIZE) == 0;
  }

  bool Matrix4D::operator!=(const Matrix4D& rhs) const {
    return memcmp(m_mat, rhs.m_mat, MAT_SIZE) != 0;
  }

  bool Matrix4D::is_identity() const {
    return memcmp(m_mat, IDENTITY.m_mat, MAT_SIZE) == 0;
  }

  namespace Detail {
    //////////////////////////////////////////////////////////////////////////
    // the following codes are used to implement 
    // Matrix4D::determinant and Matrix4D::invert.
    // 
    // the codes are from GLT's implementation of matrix4,
    // in math/matrix4.cpp, 
    // with modified function name.
    //
    // the URL of GTL:
    //   http://www.nigels.com/glt/
    //

    #define MAT(m,r,c) (m)[(r)*4+(c)]

    // Here's some shorthand converting standard (row,column) to index.
    #define m11 MAT(m,0,0)
    #define m12 MAT(m,0,1)
    #define m13 MAT(m,0,2)
    #define m14 MAT(m,0,3)
    #define m21 MAT(m,1,0)
    #define m22 MAT(m,1,1)
    #define m23 MAT(m,1,2)
    #define m24 MAT(m,1,3)
    #define m31 MAT(m,2,0)
    #define m32 MAT(m,2,1)
    #define m33 MAT(m,2,2)
    #define m34 MAT(m,2,3)
    #define m41 MAT(m,3,0)
    #define m42 MAT(m,3,1)
    #define m43 MAT(m,3,2)
    #define m44 MAT(m,3,3)

    static
    real determinant(const real *m) {
      real d12, d13, d23, d24, d34, d41;
      real tmp[4];

      // pre-compute 2x2 dets for last two rows when computing
      // cofactors of first two rows.
      d12 = (m31*m42-m41*m32);
      d13 = (m31*m43-m41*m33);
      d23 = (m32*m43-m42*m33);
      d24 = (m32*m44-m42*m34);
      d34 = (m33*m44-m43*m34);
      d41 = (m34*m41-m44*m31);

      tmp[0] =  (m22 * d34 - m23 * d24 + m24 * d23);
      tmp[1] = -(m21 * d34 + m23 * d41 + m24 * d13);
      tmp[2] =  (m21 * d24 + m22 * d41 + m24 * d12);
      tmp[3] = -(m21 * d23 - m22 * d13 + m23 * d12);

      return m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];
    }


    // * the invert algorithm is substituted by the codes from Mesa 6.2.1,
    // * since there's a bug in the origin codes from GTL 

    // returns false if the matrix is singular
    //
    // from Mesa-6.2.1/src/glu/mesa/project.c
    //
    // Code contributed by Jacques Leroy jle@star.be
    //
    static
    bool invert(real *out, const real *m) {

    #define SWAP_ROWS(a, b) { real *tmp = (a); (a)=(b); (b)=tmp; }

       real wtmp[4][8];
       real m0, m1, m2, m3, s;
       real *r0, *r1, *r2, *r3;

       r0 = wtmp[0], r1 = wtmp[1], r2 = wtmp[2], r3 = wtmp[3];

       r0[0] = MAT(m, 0, 0), r0[1] = MAT(m, 0, 1),
       r0[2] = MAT(m, 0, 2), r0[3] = MAT(m, 0, 3),
       r0[4] = 1.0, r0[5] = r0[6] = r0[7] = 0.0,
       r1[0] = MAT(m, 1, 0), r1[1] = MAT(m, 1, 1),
       r1[2] = MAT(m, 1, 2), r1[3] = MAT(m, 1, 3),
       r1[5] = 1.0, r1[4] = r1[6] = r1[7] = 0.0,
       r2[0] = MAT(m, 2, 0), r2[1] = MAT(m, 2, 1),
       r2[2] = MAT(m, 2, 2), r2[3] = MAT(m, 2, 3),
       r2[6] = 1.0, r2[4] = r2[5] = r2[7] = 0.0,
       r3[0] = MAT(m, 3, 0), r3[1] = MAT(m, 3, 1),
       r3[2] = MAT(m, 3, 2), r3[3] = MAT(m, 3, 3),
       r3[7] = 1.0, r3[4] = r3[5] = r3[6] = 0.0;

       /* choose pivot - or die */
       if (fabs(r3[0]) > fabs(r2[0]))
          SWAP_ROWS(r3, r2);
       if (fabs(r2[0]) > fabs(r1[0]))
          SWAP_ROWS(r2, r1);
       if (fabs(r1[0]) > fabs(r0[0]))
          SWAP_ROWS(r1, r0);
       if (0.0 == r0[0])
          return false;

       /* eliminate first variable     */
       m1 = r1[0] / r0[0];
       m2 = r2[0] / r0[0];
       m3 = r3[0] / r0[0];
       s = r0[1];
       r1[1] -= m1 * s;
       r2[1] -= m2 * s;
       r3[1] -= m3 * s;
       s = r0[2];
       r1[2] -= m1 * s;
       r2[2] -= m2 * s;
       r3[2] -= m3 * s;
       s = r0[3];
       r1[3] -= m1 * s;
       r2[3] -= m2 * s;
       r3[3] -= m3 * s;
       s = r0[4];
       if (s != 0.0) {
          r1[4] -= m1 * s;
          r2[4] -= m2 * s;
          r3[4] -= m3 * s;
       }
       s = r0[5];
       if (s != 0.0) {
          r1[5] -= m1 * s;
          r2[5] -= m2 * s;
          r3[5] -= m3 * s;
       }
       s = r0[6];
       if (s != 0.0) {
          r1[6] -= m1 * s;
          r2[6] -= m2 * s;
          r3[6] -= m3 * s;
       }
       s = r0[7];
       if (s != 0.0) {
          r1[7] -= m1 * s;
          r2[7] -= m2 * s;
          r3[7] -= m3 * s;
       }

       /* choose pivot - or die */
       if (fabs(r3[1]) > fabs(r2[1]))
          SWAP_ROWS(r3, r2);
       if (fabs(r2[1]) > fabs(r1[1]))
          SWAP_ROWS(r2, r1);
       if (0.0 == r1[1])
          return false;

       /* eliminate second variable */
       m2 = r2[1] / r1[1];
       m3 = r3[1] / r1[1];
       r2[2] -= m2 * r1[2];
       r3[2] -= m3 * r1[2];
       r2[3] -= m2 * r1[3];
       r3[3] -= m3 * r1[3];
       s = r1[4];
       if (0.0 != s) {
          r2[4] -= m2 * s;
          r3[4] -= m3 * s;
       }
       s = r1[5];
       if (0.0 != s) {
          r2[5] -= m2 * s;
          r3[5] -= m3 * s;
       }
       s = r1[6];
       if (0.0 != s) {
          r2[6] -= m2 * s;
          r3[6] -= m3 * s;
       }
       s = r1[7];
       if (0.0 != s) {
          r2[7] -= m2 * s;
          r3[7] -= m3 * s;
       }

       /* choose pivot - or die */
       if (fabs(r3[2]) > fabs(r2[2]))
          SWAP_ROWS(r3, r2);
       if (0.0 == r2[2])
          return false;

       /* eliminate third variable */
       m3 = r3[2] / r2[2];
       r3[3] -= m3 * r2[3], r3[4] -= m3 * r2[4],
       r3[5] -= m3 * r2[5], r3[6] -= m3 * r2[6], r3[7] -= m3 * r2[7];

       /* last check */
       if (0.0 == r3[3])
          return false;

       s = 1.0 / r3[3];		/* now back substitute row 3 */
       r3[4] *= s;
       r3[5] *= s;
       r3[6] *= s;
       r3[7] *= s;

       m2 = r2[3];			/* now back substitute row 2 */
       s = 1.0 / r2[2];
       r2[4] = s * (r2[4] - r3[4] * m2), r2[5] = s * (r2[5] - r3[5] * m2),
       r2[6] = s * (r2[6] - r3[6] * m2), r2[7] = s * (r2[7] - r3[7] * m2);
       m1 = r1[3];
       r1[4] -= r3[4] * m1, r1[5] -= r3[5] * m1,
       r1[6] -= r3[6] * m1, r1[7] -= r3[7] * m1;
       m0 = r0[3];
       r0[4] -= r3[4] * m0, r0[5] -= r3[5] * m0,
       r0[6] -= r3[6] * m0, r0[7] -= r3[7] * m0;

       m1 = r1[2];			/* now back substitute row 1 */
       s = 1.0 / r1[1];
       r1[4] = s * (r1[4] - r2[4] * m1), r1[5] = s * (r1[5] - r2[5] * m1),
       r1[6] = s * (r1[6] - r2[6] * m1), r1[7] = s * (r1[7] - r2[7] * m1);
       m0 = r0[2];
       r0[4] -= r2[4] * m0, r0[5] -= r2[5] * m0,
       r0[6] -= r2[6] * m0, r0[7] -= r2[7] * m0;

       m0 = r0[1];			/* now back substitute row 0 */
       s = 1.0 / r0[0];
       r0[4] = s * (r0[4] - r1[4] * m0), r0[5] = s * (r0[5] - r1[5] * m0),
       r0[6] = s * (r0[6] - r1[6] * m0), r0[7] = s * (r0[7] - r1[7] * m0);

       MAT(out, 0, 0) = r0[4];
       MAT(out, 0, 1) = r0[5], MAT(out, 0, 2) = r0[6];
       MAT(out, 0, 3) = r0[7], MAT(out, 1, 0) = r1[4];
       MAT(out, 1, 1) = r1[5], MAT(out, 1, 2) = r1[6];
       MAT(out, 1, 3) = r1[7], MAT(out, 2, 0) = r2[4];
       MAT(out, 2, 1) = r2[5], MAT(out, 2, 2) = r2[6];
       MAT(out, 2, 3) = r2[7], MAT(out, 3, 0) = r3[4];
       MAT(out, 3, 1) = r3[5], MAT(out, 3, 2) = r3[6];
       MAT(out, 3, 3) = r3[7];

       return true;
    #undef SWAP_ROWS
    }

    #undef m11
    #undef m12
    #undef m13
    #undef m14
    #undef m21
    #undef m22
    #undef m23
    #undef m24
    #undef m31
    #undef m32
    #undef m33
    #undef m34
    #undef m41
    #undef m42
    #undef m43
    #undef m44
    #undef MAT

    //
    // end of copied code :p
    //////////////////////////////////////////////////////////////////////////
  }

  real Matrix4D::determinant() const {
    return Detail::determinant(m_mat);
  }

  Matrix4D& Matrix4D::invert() {
    Detail::invert(m_mat, m_mat);
    return *this;
  }

  Matrix4D Matrix4D::inverse() const {
    return Matrix4D(*this).invert();
  }

  //////////////////////////////////////////////////////////////////////////
  // static methods used to create transform matrices

  Matrix4D Matrix4D::create_translate_matrix(const Vector3D& v) {
    Matrix4D ret_val;
    ret_val(3, 0) = v(0);
    ret_val(3, 1) = v(1);
    ret_val(3, 2) = v(2);
    return ret_val;
  }

  Matrix4D Matrix4D::create_scale_matrix(const Vector3D& v) {
    Matrix4D ret_val;
    ret_val(0, 0) = v(0);
    ret_val(1, 1) = v(1);
    ret_val(2, 2) = v(2);
    return ret_val;
  }

  Matrix4D Matrix4D::create_scale_matrix(real sf) {
    Matrix4D ret_val;
    ret_val(0, 0) = sf;
    ret_val(1, 1) = sf;
    ret_val(2, 2) = sf;
    return ret_val;
  }

  //
  // the matrix is from
  //   Computer Graphics, Principles and Practice, Second Edition in C
  //     Exercise 5.15
  // the implementation referenced the codes of GTL in math/matrix4.cpp
  //
  Matrix4D Matrix4D::create_rotate_matrix(const Vector3D& axis, real angle) {
	  Matrix4D ret_val;

	  real s = sin(angle);
	  real c = cos(angle);
	  real t = 1.0 - c;

	  Vector3D ax(axis);
    ax.normalize();

	  real x = ax(0);
	  real y = ax(1);
	  real z = ax(2);

	  ret_val(0, 0) = x*x*t+c;
	  ret_val(0, 1) = x*y*t+z*s;
	  ret_val(0, 2) = z*x*t-y*s;

	  ret_val(1, 0) = x*y*t-z*s;
	  ret_val(1, 1) = y*y*t+c;
	  ret_val(1, 2) = t*z*y+s*x;

	  ret_val(2, 0) = z*x*t+y*s;
	  ret_val(2, 1) = y*z*t-x*s;
	  ret_val(2, 2) = z*z*t+c;

	  return ret_val;
  }

  Matrix4D Matrix4D::create_rotate_matrix(const Vector3D& point,
                                          const Vector3D& axis, real angle) {
    return create_translate_matrix(-point) *
           create_rotate_matrix(axis, angle) *
           create_translate_matrix(point);
  }

  Matrix4D Matrix4D::create_orient_matrix(const Vector3D& x,
                                          const Vector3D& y,
                                          const Vector3D& z) {
    Matrix4D ret_val;

    ret_val(0, 0) = x(0);
    ret_val(1, 0) = x(1);
    ret_val(2, 0) = x(2);

    ret_val(0, 1) = y(0);
    ret_val(1, 1) = y(1);
    ret_val(2, 1) = y(2);

    ret_val(0, 2) = z(0);
    ret_val(1, 2) = z(1);
    ret_val(2, 2) = z(2);

    return ret_val;
  }

  Matrix4D Matrix4D::create_orient_matrix(const Vector3D& direction,
                                          const Vector3D& up) {
    Matrix4D ret_val;

	  Vector3D d(direction);
	  d.normalize();

	  Vector3D u(up);
	  u.normalize();

	  return create_orient_matrix(u.cross_product(d),u,d);
  }
}
