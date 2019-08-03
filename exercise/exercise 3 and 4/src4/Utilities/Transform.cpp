#include "Matrix4D.h"
#include "Primitive3D.h"
#include <cmath>
using namespace std;

//////////////////////////////////////////////////////////////////////
// standard transform matrices

void Identity(Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(1, 0, 0, 0), 
    Vector4D(0, 1, 0, 0),
    Vector4D(0, 0, 1, 0),
    Vector4D(0, 0, 0, 1),
  };
  static Matrix4D identity(v);

  m = v;
}

void Zero(Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(0, 0, 0, 0), 
    Vector4D(0, 0, 0, 0),
    Vector4D(0, 0, 0, 0),
    Vector4D(0, 0, 0, 0),
  };
  static Matrix4D zero(v);

  m = v;
}

void Transfer(double dx, double dy, double dz, Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(1, 0, 0, 0), 
    Vector4D(0, 1, 0, 0),
    Vector4D(0, 0, 1, 0),
  };
  m[0] = v[0];
  m[1] = v[1];
  m[2] = v[2];
  m[3] = Vector4D(dx, dy, dz, 1);
}

void Scale(double sx, double sy, double sz, Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(0, 0, 0, 1),
  };
  m[0] = Vector4D(sx, 0, 0, 0);
  m[1] = Vector4D(0, sy, 0, 0);
  m[2] = Vector4D(0, 0, sz, 0);
  m[3] = v[0];
}

void RotateX(double theta, Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(1, 0, 0, 0),
    Vector4D(0, 0, 0, 1),
  };
  double cos_theta = cos(theta);
  double sin_theta = sin(theta);
  m[0] = v[0];
  m[1] = Vector4D(0, cos_theta, sin_theta, 0);
  m[2] = Vector4D(0, -sin_theta, cos_theta, 0);
  m[3] = v[1];
}

void RotateY(double theta, Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(0, 1, 0, 0),
    Vector4D(0, 0, 0, 1),
  };
  double cos_theta = cos(theta);
  double sin_theta = sin(theta);
  m[0] = Vector4D(cos_theta, 0, -sin_theta, 0);
  m[1] = v[0];
  m[2] = Vector4D(sin_theta, 0, cos_theta, 0);
  m[3] = v[1];
}

void RotateZ(double theta, Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(0, 0, 1, 0),
    Vector4D(0, 0, 0, 1),
  };
  double cos_theta = cos(theta);
  double sin_theta = sin(theta);
  m[0] = Vector4D(cos_theta, sin_theta, 0, 0);
  m[1] = Vector4D(-sin_theta, cos_theta, 0, 0);
  m[2] = v[0];
  m[3] = v[1];
}

void ShearXY(double shx, double shy, Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(1, 0, 0, 0),
    Vector4D(0, 1, 0, 0),
    Vector4D(0, 0, 0, 1),
  };
  m[0] = v[0];
  m[1] = v[1];
  m[2] = Vector4D(shx, shy, 1, 0);
  m[3] = v[2];
}

void ParallelProject(double zp, Point3D& d, Matrix4D& m) {
  static Vector4D v[] = {
    Vector4D(1, 0, 0, 0),
    Vector4D(0, 1, 0, 0),
  };

  double dxodz = d.x() / d.z();
  double dyodz = d.y() / d.z();
  m[0] = v[0];
  m[1] = v[1];
  m[2] = Vector4D(-dxodz, -dyodz, 0, 0);
  m[3] = Vector4D(zp * dxodz, zp * dyodz, zp, 1);
}
