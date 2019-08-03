#ifndef WORLD_3D_INCLUDED__
#define WORLD_3D_INCLUDED__

class Matrix4D;
class Shape3D;
class SpecialShape3D;
class Painter3D;
struct Point3D;


// note: since Matrix4D doesn't take the const semantic,
//       all Matrix4D& here means const Matrix4D&, with value
//       passing semantic. reference passing semantic is presented
//       by passing a pointer.

struct World3D_impl;


// note: the world passes the information about how the object will
//       be transformed and the view direction to the object so that
//       it can draw itself properly. however, the world will do the 
//       transformation when non-absolute objects draws in the painter.
//       so the non-absolute objects should not transform itself before
//       draw. however, the info can be used to decide the hidden surface.
//       to absolute objects, it can choose how to use it arbitrary
class World3D {
public:
  World3D();
  ~World3D();

  // add objects with absolute position that are not affected by
  // the world transform matrix and transformObject method
  // used to add something like axes to the world
  // note: World3D will take over the cleaning up of the shape
  void addAbsolute(Shape3D* shape);

  // remove "absolute object" from the world
  // note: World3D will return the control of the object to the
  //       caller, so that the caller should do clean up herself
  void removeAbsolute(Shape3D* shape);

  // add objects to the world
  // note: World3D will take over the cleaning up of the shape
  void add(Shape3D* shape);

  // remove object from the world
  // note: World3D will return the control of the object to the
  //       caller, so that the caller should do clean up herself
  void remove(Shape3D* shape);

  // the following methods transform the world
  // by multiplying a matrix on output to the controller,
  // but the objects in the world are left unchanged.
  void setWorldTransformer(Matrix4D& m);
  Matrix4D getWorldTransformer();
  void transformWorld(Matrix4D& m);

  // transform each objects in the world
  void transformObject(Matrix4D& m);

  // set the view direction
  void setViewDirection(Point3D& v);

  // draw the objects in the painter
  void draw(Painter3D *painter);

  // clear everything in the world
  void clear();
  
private:
  World3D_impl *pImpl;
};

#endif
