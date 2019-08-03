#ifndef SURFACE_HIDDEN_CUBOID_INCLUDED__
#define SURFACE_HIDDEN_CUBOID_INCLUDED__

#include "../Shape3D.h"
#include "../Primitive3D.h"

// note: since Matrix4D, Line3D and Point3D don't take the const semantic,
//       all Matrix4D, Line3D& and Point3D& here means const refrence passing,
//       with value passing semantic.


// this Cuboid class does self surface hiding
class SurfaceHiddenCuboid : public Shape3D  
{
public:

  // construct the Cuboid by the vertices specified by the array.
  // the correctness on whether they really structure a Cuboid
  // is not checked. The code used here represents something more 
  // generic. I'll rename it when I need the feature of building a
  // non-cuboid using the same codes here.
  // v[0] to v[3] structure the one surface anti-clockwise
  // v[4] to v[7] structure the another surface anti-clockwise
	SurfaceHiddenCuboid(Point3D vertices[], unsigned int color = 0);
	virtual ~SurfaceHiddenCuboid();

  virtual void draw(Painter3D *p, WorldInfo *info);
  virtual void transform(Matrix4D& m);

private:
  Point3D m_vertices[8];
  unsigned int m_color;
};

#endif
