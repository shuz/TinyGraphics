#ifndef RECT_3D_INCLUDED__
#define RECT_3D_INCLUDED__

#include "../Shape3D.h"
#include "../Primitive3D.h"

// note: since Matrix4D, Line3D and Point3D don't take the const semantic,
//       all Matrix4D, Line3D& and Point3D& here means const refrence passing,
//       with value passing semantic.

class Rect3D : public Shape3D  
{
public:

  // construct the Rect3D by the vertices specified by the array.
  // the correctness on whether they really locate in the same plane
  // is not checked. The code used here represents something more 
  // generic. I'll rename it when I need the feature of building a
  // non-rect shape using the same code here.
  // v[0] to v[3] are used to structure the Rect
	Rect3D(Point3D vertices[], unsigned int color = 0);
	virtual ~Rect3D();

  virtual void draw(Painter3D *p, WorldInfo *info);
  virtual void transform(Matrix4D& m);

private:
  Point3D m_vertices[4];
  unsigned int m_color;
};

#endif
