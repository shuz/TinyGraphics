#include "World3D.h"
#include "Matrix4D.h"
#include "Graphics3D.h"
#include "Primitive3D.h"
#include "Object3D.h"

#include <list>
using namespace std;

struct World3D::Impl {
  typedef list<Object3D *> ShapeContainer;
  typedef ShapeContainer::iterator       iterator;
  typedef ShapeContainer::const_iterator const_iterator;

  ShapeContainer objects;

  template <class Container>
  static void clean_up(Container& c) {
    typedef Container::iterator Itor;
    for (Itor i = c.begin(); i != c.end(); ++i) {
      delete *i;
    }
    c.swap(Container());  // clear the content using the swap trick
  }

  void clear() {
    clean_up(objects);
  }

  Impl() {}

  ~Impl() {
    clear();
  }
};


struct World3D::Iterator::Impl {
  typedef list<Object3D *> ShapeContainer;
  typedef ShapeContainer::iterator iterator;

  iterator cur;
  iterator end;

  Impl(const iterator& cur, const iterator& end) 
    : cur(cur), end(end) {}
};

World3D::World3D()
  : pimpl(new Impl) {}

World3D::~World3D() {
  delete pimpl;
}

// add objects to the world
// note: World3D will take over the cleaning up of the shape
void World3D::add(Object3D* shape) {
  pimpl->objects.push_back(shape);
}

// remove object from the world
// note: World3D will return the control of the object to the
//       caller, so that the caller should do clean up herself
void World3D::remove(Object3D* shape) {
  pimpl->objects.remove(shape);
}

World3D::Iterator World3D::get_iterator() {
  return Iterator(
    new Iterator::Impl(
      pimpl->objects.begin(),
      pimpl->objects.end()
    )
  );
}

// draw the objects in the painter
void World3D::draw(Graphics3D *graphics) const {
  typedef Impl::const_iterator const_iterator;
  const_iterator i;

  for (i = pimpl->objects.begin();
       i != pimpl->objects.end();
       ++i) {
    (*i)->draw(graphics);
  }
}

// clear everything in the world
void World3D::clear() {
  pimpl->clear();
}


World3D::Iterator::Iterator(Impl *pimpl)
  : pimpl(pimpl) {}

World3D::Iterator::~Iterator() {
  delete pimpl;
}

bool World3D::Iterator::has_next() {
  return pimpl->cur != pimpl->end;
}

Object3D *World3D::Iterator::next() {
  return *pimpl->cur++;
}
