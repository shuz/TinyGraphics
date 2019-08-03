#ifndef MATRIX_4D_INCLUDED__
#define MATRIX_4D_INCLUDED__

#include <assert.h>
#include "Real.h"

namespace TinyGraphics {

  class Vector3D;
  class Vector4D;

  #define CHECK_RANGE(n)        \
    do {                        \
      assert(0 <= n && n < 4);  \
    } while (false)

  class Matrix4D {
  private:
    real m_mat[4*4];

  public:
    Matrix4D() {
      (*this) = IDENTITY;
    }

    Matrix4D(real m00, real m01, real m02, real m03,
             real m10, real m11, real m12, real m13,
             real m20, real m21, real m22, real m23,
             real m30, real m31, real m32, real m33) {
      assign(m00, m01, m02, m03,
             m10, m11, m12, m13,
             m20, m21, m22, m23,
             m30, m31, m32, m33);
    }

    real& operator()(int r, int c) {
      CHECK_RANGE(r);
      CHECK_RANGE(c);
      return m_mat[4*r + c];
    }

    real operator()(int r, int c) const {
      CHECK_RANGE(r);
      CHECK_RANGE(c);
      return m_mat[4*r + c];
    }

    void assign(real m00, real m01, real m02, real m03,
                real m10, real m11, real m12, real m13,
                real m20, real m21, real m22, real m23,
                real m30, real m31, real m32, real m33);
  
    Matrix4D& operator*=(const Matrix4D& rhs);
    Matrix4D operator*(const Matrix4D& rhs) const;

    bool operator==(const Matrix4D& rhs) const;
    bool operator!=(const Matrix4D& rhs) const;

    bool is_identity() const;

    Matrix4D transpose() const;

    Matrix4D inverse() const;
    Matrix4D& invert();

    real determinant() const;

    static const Matrix4D IDENTITY;
    static const Matrix4D ZERO;

    // create a translate matrix
    // translate x, y, z by v[0], v[1], v[2] respectively
    static
    Matrix4D create_translate_matrix(const Vector3D& v);

    // create a scale matrix
    // scale x, y, z by sf
    static
    Matrix4D create_scale_matrix(real sf);

    // create a scale matrix
    // scale x, y, z by v[0], v[1], v[2] respectively
    static 
    Matrix4D create_scale_matrix(const Vector3D& v);

    // create a rotate matrix
    // rotate around axis starting from the origin by angle
    static
    Matrix4D create_rotate_matrix(const Vector3D& axis, real angle);
  
    // create a rotate matrix
    // rotate around axis starting from the point by angle
    static
    Matrix4D create_rotate_matrix(const Vector3D& v, const Vector3D& axis, real angle);

    // create an orientation matrix
    // transform the axes to new x, y, z
    // params x, y, z are new orientations,
    // and length units as well,
    // for +x, +y, +z respectively
    static
    Matrix4D create_orient_matrix(const Vector3D& x,
                                  const Vector3D& y,
                                  const Vector3D& z);

	  // create an orientation matrix
	  // direction: new orientation for +z
	  // up:        new orientation for +y
    //
    // note: the vectors are normalized before used
    //       to generate the new +x, +y, +z.
    //       so the new axes share the same length unit
    //       with the old ones
    static
    Matrix4D create_orient_matrix(const Vector3D& direction, const Vector3D& up);

  };

  // a row vector multiplies a matrix
  Vector4D operator*(const Vector4D& v, const Matrix4D& m);
  Vector4D& operator*=(Vector4D& v, const Matrix4D& m);

  // convert the 3d-vector to its corresponding homogeneous 4d-vector
  // and then compute using the operations of 4d-vectors
  Vector3D operator*(const Vector3D& v, const Matrix4D& m);
  Vector3D& operator*=(Vector3D& v, const Matrix4D& m);

  #undef CHECK_RANGE
}

#endif
