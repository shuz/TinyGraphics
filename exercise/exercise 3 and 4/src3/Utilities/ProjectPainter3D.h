#ifndef PROJECT_PAINTER_3D_INCLUDED__
#define PROJECT_PAINTER_3D_INCLUDED__

#include "Painter3D.h"

class Painter;
class Matrix4D;
struct Line3D;
struct Point3D;


// note: since Matrix4D doesn't take the const semantic,
//       all Matrix4D& here means const Matrix4D&, with value
//       passing semantic. reference passing semantic is presented
//       by passing a pointer.


struct ProjectPainter3D_impl;

class ProjectPainter3D : public Painter3D {
public:
  // ProjectPainter3D don't take care of the cleaning up
  // of the 2d painter passed in
  ProjectPainter3D(Painter *painter);
  virtual ~ProjectPainter3D();

  virtual void drawLine(Line3D& line, unsigned int color = 0);
  virtual void drawPixel(Point3D& point, unsigned int color = 0);  

  // the following matrices determine the projection 
  // of the world to the controller
  // note: since we use x and y coordinates only, there's
  //       no need to set z coordinates of objects to the same
  //       value. eg: you can use shearing matrix as project
  //       matrix as well.
  virtual Matrix4D getProjector();
  void setProjector(Matrix4D& m);
  void transformProjector(Matrix4D& m);

private:
  ProjectPainter3D_impl *pImpl;
};

#endif
