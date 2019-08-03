#ifndef SHAPE_3D_INCLUDED__
#define SHAPE_3D_INCLUDED__

class Matrix4D;
class Painter3D;
struct Point3D;

// note: since Matrix4D doesn't take the const semantic,
//       all Matrix4D& here means const Matrix4D&, with value
//       passing semantic. reference passing semantic is presented
//       by passing a pointer.

struct WorldInfo {
  Matrix4D& transformer;    // valid in draw() only
  Point3D& viewDirection;   // valid in draw() only
  WorldInfo(Matrix4D& m, Point3D& p)
    : transformer(m), viewDirection(p) {}
};

class Shape3D {
public:
  Shape3D();
  virtual ~Shape3D() = 0;

  virtual void draw(Painter3D *p, WorldInfo *info) = 0;
  virtual void transform(Matrix4D& m) = 0;
};

#endif
