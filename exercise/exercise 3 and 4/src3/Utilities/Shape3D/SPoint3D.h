#ifndef SPOINT_3D_INCLUDED__
#define SPOINT_3D_INCLUDED__

#include "../Shape3D.h"
#include "../Primitive3D.h"

// note: since Matrix4D, Line3D and Point3D don't take the const semantic,
//       all Matrix4D, Line3D& and Point3D& here means const refrence passing,
//       with value passing semantic.

class SPoint3D : public Shape3D  
{
public:
	SPoint3D(Point3D& point, unsigned int color = 0);
	virtual ~SPoint3D();

  virtual void draw(Painter3D *p, WorldInfo *info);
  virtual void transform(Matrix4D& m);

private:
  Point3D m_point;
  unsigned int m_color;
};

#endif
