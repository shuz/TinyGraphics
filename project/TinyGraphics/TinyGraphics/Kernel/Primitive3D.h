#ifndef PRIMITIVE_3D_INCLUDED__
#define PRIMITIVE_3D_INCLUDED__

#include "Real.h"
#include "Vector3D.h"
#include "Matrix4D.h"
#include <vector>

namespace TinyGraphics {

  class Point3D {
  public:
    real x, y, z;

    Point3D() {
      assign(0, 0, 0);
    }

    Point3D(real x, real y, real z) {
      assign(x, y, z);
    }

    Point3D(const Vector3D& v) {
      from_vec3d(v);
    }

    void from_vec3d(const Vector3D& v) {
      assign(v(0), v(1), v(2));
    }

    Vector3D to_vec3d() const {
      return Vector3D(x, y, z);
    }

    void assign(real x, real y, real z) {
      this->x = x;
      this->y = y;
      this->z = z;
    }

    bool operator==(const Point3D& rhs) const {
      return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator!=(const Point3D& rhs) const {
      return x != rhs.x || y != rhs.y || z != rhs.z;
    }

    Vector3D operator-(const Point3D& rhs) const {
      return Vector3D(x - rhs.x, y - rhs.y, z - rhs.z);
    }

    Point3D& operator+=(const Vector3D& rhs) {
      x += rhs(0);  y += rhs(1); z += rhs(2);
      return *this;
    }

  
    Point3D& operator+=(const Point3D& rhs) {
      x += rhs.x;  y += rhs.y; z += rhs.z;
      return *this;
    }

    Point3D operator+(const Vector3D& rhs) const {
      return Point3D(*this) += rhs;
    }

    Point3D& operator*=(const Matrix4D& mat) {
      transform(mat);
      return *this;
    }

    Point3D operator*(const Matrix4D& mat) const {
      return Point3D(*this) *= mat;
    }

    void transform(const Matrix4D& mat) {
      Vector3D vec(x, y, z);
      vec *= mat;
      from_vec3d(vec);
    }

    static const Point3D ORIGIN;
  };

  class TriangleSet {
  public:
  
    struct Triangle {
      Triangle() {}
      Triangle(int a, int b, int c)
        : a(a), b(b), c(c) {}

      int a, b, c;      // indices of vertices in the triangle set

      void assign(int aa, int bb, int cc) {
        a = aa;  b = bb;  c = cc;
      }
    };

    typedef std::vector<Point3D> VertexContainer;
    typedef std::vector<Vector3D> NormalContainer;
    typedef std::vector<Triangle> TriangleContainer;

    VertexContainer vertices;
    NormalContainer normals;
    TriangleContainer triangles;

    void transform(const Matrix4D& rhs) {
      VertexContainer::iterator itor1 = vertices.begin(),
                                end1 = vertices.end();
      for (; itor1 != end1; ++itor1) {
        (*itor1).transform(rhs);
      }

      NormalContainer::iterator itor2 = normals.begin(),
                                end2 = normals.end();
      for (; itor2 != end2; ++itor2) {
        (*itor2).transform(rhs);
      }
    }

    void clear() {
      vertices.clear();
      normals.clear();
      triangles.clear();
    }
  };
}

#endif
