#include "Matrix4D.h"
#include "Vector3D.h"
#include "Vector4D.h"

#include <memory.h>
#include <stdexcept>

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


// From Mesa-2.2/src/glu/project.c
//
// Compute the inverse of a 4x4 matrix.  Contributed by scotter@lafn.org
//
static
void invert_general(real *out, const real *m) {
  real det;
  real d12, d13, d23, d24, d34, d41;
  real tmp[16]; /* Allow out == in. */

  /* Inverse = adjoint / det. (See linear algebra texts.)*/

  /* pre-compute 2x2 dets for last two rows when computing */
  /* cofactors of first two rows. */
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

  /* Compute determinant as early as possible using these cofactors. */
  det = m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2] + m14 * tmp[3];

  /* Run singularity test. */
  if (det == 0.0) {
    throw std::invalid_argument("invert_matrix: error: singular matrix.");
  }
  else {
    real invDet = 1.0 / det;
    /* Compute rest of inverse. */
    tmp[0] *= invDet;
    tmp[1] *= invDet;
    tmp[2] *= invDet;
    tmp[3] *= invDet;

    tmp[4] = -(m12 * d34 - m13 * d24 + m14 * d23) * invDet;
    tmp[5] =  (m11 * d34 + m13 * d41 + m14 * d13) * invDet;
    tmp[6] = -(m11 * d24 + m12 * d41 + m14 * d12) * invDet;
    tmp[7] =  (m11 * d23 - m12 * d13 + m13 * d12) * invDet;

    /* Pre-compute 2x2 dets for first two rows when computing */
    /* cofactors of last two rows. */
    d12 = m11*m22-m21*m12;
    d13 = m11*m23-m21*m13;
    d23 = m12*m23-m22*m13;
    d24 = m12*m24-m22*m14;
    d34 = m13*m24-m23*m14;
    d41 = m14*m21-m24*m11;

    tmp[8] =  (m42 * d34 - m43 * d24 + m44 * d23) * invDet;
    tmp[9] = -(m41 * d34 + m43 * d41 + m44 * d13) * invDet;
    tmp[10] =  (m41 * d24 + m42 * d41 + m44 * d12) * invDet;
    tmp[11] = -(m41 * d23 - m42 * d13 + m43 * d12) * invDet;
    tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23) * invDet;
    tmp[13] =  (m31 * d34 + m33 * d41 + m34 * d13) * invDet;
    tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12) * invDet;
    tmp[15] =  (m31 * d23 - m32 * d13 + m33 * d12) * invDet;

    memcpy(out, tmp, MAT_SIZE);
  }
}


//
// Invert matrix m.  This algorithm contributed by Stephane Rehel
// <rehel@worldnet.fr>
//
static
void invert(real *out, const real *m) {
  register real det;
  real tmp[16]; /* Allow out == in. */

  if( m41 != 0. || m42 != 0. || m43 != 0. || m44 != 1. ) {
    invert_general(out, m);
    return;
  }

  /* Inverse = adjoint / det. (See linear algebra texts.)*/

  tmp[0]= m22 * m33 - m23 * m32;
  tmp[1]= m23 * m31 - m21 * m33;
  tmp[2]= m21 * m32 - m22 * m31;

  /* Compute determinant as early as possible using these cofactors. */
  det= m11 * tmp[0] + m12 * tmp[1] + m13 * tmp[2];

  /* Run singularity test. */
  if (det == 0.0) {
    throw std::invalid_argument("invert_matrix: error: Singular matrix.");
  }
  else {
    real d12, d13, d23, d24, d34, d41;
    register real im11, im12, im13, im14;

    det= 1. / det;

    /* Compute rest of inverse. */
    tmp[0] *= det;
    tmp[1] *= det;
    tmp[2] *= det;
    tmp[3]  = 0.;

    im11= m11 * det;
    im12= m12 * det;
    im13= m13 * det;
    im14= m14 * det;
    tmp[4] = im13 * m32 - im12 * m33;
    tmp[5] = im11 * m33 - im13 * m31;
    tmp[6] = im12 * m31 - im11 * m32;
    tmp[7] = 0.;

    /* Pre-compute 2x2 dets for first two rows when computing */
    /* cofactors of last two rows. */
    d12 = im11*m22 - m21*im12;
    d13 = im11*m23 - m21*im13;
    d23 = im12*m23 - m22*im13;
    d24 = im12*m24 - m22*im14;
    d34 = im13*m24 - m23*im14;
    d41 = im14*m21 - m24*im11;

    tmp[8] =  d23;
    tmp[9] = -d13;
    tmp[10] = d12;
    tmp[11] = 0.;

    tmp[12] = -(m32 * d34 - m33 * d24 + m34 * d23);
    tmp[13] =  (m31 * d34 + m33 * d41 + m34 * d13);
    tmp[14] = -(m31 * d24 + m32 * d41 + m34 * d12);
    tmp[15] =  1.;

    memcpy(out, tmp, MAT_SIZE);
  }
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


real Matrix4D::determinant() const {
  return ::determinant(m_mat);
}

Matrix4D& Matrix4D::invert() {
  ::invert(m_mat, m_mat);
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

Matrix4D Matrix4D::create_orient_matrix(const Vector3D& x,
                                        const Vector3D& y,
                                        const Vector3D& z) {
  Matrix4D ret_val;

  ret_val(0, 0) = x(0);
  ret_val(0, 1) = x(1);
  ret_val(0, 2) = x(2);

  ret_val(1, 0) = y(0);
  ret_val(1, 1) = y(1);
  ret_val(1, 2) = y(2);

  ret_val(2, 0) = z(0);
  ret_val(2, 1) = z(1);
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
