#include "World3D.h"
#include "Matrix4D.h"
#include "Shape3D.h"
#include "Painter3D.h"
#include "Transform.h"
#include "Primitive3D.h"

#include <list>
using namespace std;


// decorator of Painter so that it performs a transform before painting
class TransformPainter : public Painter3D {
public:
  TransformPainter(Painter3D *painter, Matrix4D& m) 
    : m_painter(painter), m_trans(m) {}

  virtual ~TransformPainter() {}

  virtual void drawLine(Line3D& line, unsigned int color = 0) {
    Line3D copyline(line);        // avoid changing the original line
    copyline.transform(m_trans);
    m_painter->drawLine(copyline, color);
  }
  
  virtual void drawPixel(Point3D& point, unsigned int color = 0) {
    Point3D copypoint(point);     // avoid changing the original point
    copypoint.transform(m_trans);
    m_painter->drawPixel(copypoint, color);
  }

private:
  Painter3D *m_painter;
  Matrix4D m_trans;
};


struct World3D_impl {
  typedef list<Shape3D *> ShapeContainer;
  typedef ShapeContainer::iterator       SItor;  
  typedef ShapeContainer::const_iterator SCItor;

  ShapeContainer absoluteObjects,
                 objects;
  Matrix4D transformer;
  Point3D viewDirection;

  template <class Container>
  static void cleanUp(Container& c) {
    typedef Container::iterator Itor;
    for (Itor i = c.begin(); i != c.end(); ++i) {
      delete *i;
    }
    c.swap(Container());  // clear the content using the swap trick
  }

  void clear() {
    cleanUp(absoluteObjects);
    cleanUp(objects);
    viewDirection.assign(0, 0, -1);
    Identity(transformer);
  }

  World3D_impl() 
    : viewDirection(0, 0, -1) {
    Identity(transformer);
  }

  ~World3D_impl() {
    clear();
  }
};

World3D::World3D()
  : pImpl(new World3D_impl) {}

World3D::~World3D() {
  delete pImpl;
}


// add objects with absolute position that are not affected by
// the world transform matrix and transformObject method
// used to add something like axes to the world
// note: World3D will take over the cleaning up of the shape
void World3D::addAbsolute(Shape3D* shape) {
  pImpl->absoluteObjects.push_back(shape);
}

// remove "absolute object" from the world
// note: World3D will return the control of the object to the
//       caller, so that the caller should do clean up herself
void World3D::removeAbsolute(Shape3D* shape) {
  pImpl->absoluteObjects.remove(shape);
}

// add objects to the world
// note: World3D will take over the cleaning up of the shape
void World3D::add(Shape3D* shape) {
  pImpl->objects.push_back(shape);
}

// remove object from the world
// note: World3D will return the control of the object to the
//       caller, so that the caller should do clean up herself
void World3D::remove(Shape3D* shape) {
  pImpl->objects.remove(shape);
}

// the following methods transform the world
// by multiplying a matrix on output to the controller,
// but the objects in the world are left unchanged.
void World3D::setWorldTransformer(Matrix4D& m) {
  pImpl->transformer = m;
}

Matrix4D World3D::getWorldTransformer() {
  return pImpl->transformer;
}

void World3D::transformWorld(Matrix4D& m) {
  pImpl->transformer = pImpl->transformer * m;
}

// transform each objects in the world
void World3D::transformObject(Matrix4D& m) {
  typedef World3D_impl::SItor Itor;
  for (Itor i = pImpl->objects.begin();
            i != pImpl->objects.end(); ++i) {
    (*i)->transform(m);
  }
}

void World3D::setViewDirection(Point3D& v) {
  pImpl->viewDirection = v;
}

// draw the objects in the painter
void World3D::draw(Painter3D *painter) {
  typedef World3D_impl::SItor SItor;
  SItor i;

  WorldInfo info(pImpl->transformer, pImpl->viewDirection);

  for (i = pImpl->absoluteObjects.begin();
       i != pImpl->absoluteObjects.end(); ++i) {
    (*i)->draw(painter, &info);
  }

  TransformPainter tpainter(painter, pImpl->transformer);
  for (i = pImpl->objects.begin();
            i != pImpl->objects.end(); ++i) {
    (*i)->draw(&tpainter, &info);
  }
}

// clear everything in the world
void World3D::clear() {
  pImpl->clear();
}
