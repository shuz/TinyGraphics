#ifndef SLINE_3D_INCLUDED__
#define SLINE_3D_INCLUDED__

#include "../Shape3D.h"
#include "../Primitive3D.h"

// note: since Matrix4D, Line3D and Point3D don't take the const semantic,
//       all Matrix4D, Line3D& and Point3D& here means const refrence passing,
//       with value passing semantic.

class SLine3D : public Shape3D  
{
public:
	SLine3D(Line3D& line, unsigned int color = 0);
	virtual ~SLine3D();

  virtual void draw(Painter3D *p, WorldInfo *info);
  virtual void transform(Matrix4D& m);

private:
  Line3D m_line;
  unsigned int m_color;
};

#endif
