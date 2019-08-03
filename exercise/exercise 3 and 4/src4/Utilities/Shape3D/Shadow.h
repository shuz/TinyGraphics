#ifndef SHADOW_INCLUDED__
#define SHADOW_INCLUDED__

#include "../Shape3D.h"
#include "../Primitive3D.h"
#include "../Matrix4D.h"

// note: since Matrix4D, Line3D and Point3D don't take the const semantic,
//       all Matrix4D, Line3D& and Point3D& here means const refrence passing,
//       with value passing semantic.

class Shadow : public Shape3D {
public:

  // construct the shadow of the shape projected by proj
	Shadow(Shape3D *shape, Matrix4D& proj, 
         Point3D& viewDir, unsigned int color = 0);
	virtual ~Shadow();

  virtual void draw(Painter3D *p, WorldInfo *info);
  virtual void transform(Matrix4D& m);

private:
  Shape3D *m_shape;
  Matrix4D m_proj;
  Point3D m_viewDir;
  unsigned int m_color;
};

#endif
