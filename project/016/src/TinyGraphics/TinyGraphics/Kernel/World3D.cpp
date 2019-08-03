#include "World3D.h"
#include "Object3D.h"
#include "Light.h"
#include "ColorRGB.h"
#include "Vector3D.h"

#include <list>
using namespace std;

namespace TinyGraphics {

  struct World3D::Impl {
    typedef list<Object3D *> ObjectContainer;
    typedef ObjectContainer::iterator       iterator;
    typedef ObjectContainer::const_iterator const_iterator;

    typedef list<Light *> LightContainer;
    typedef LightContainer::iterator       light_iterator;
    typedef LightContainer::const_iterator const_light_iterator;

    ObjectContainer objects;
    LightContainer lights;

    ColorRGB ambient_color;
    ColorRGB background_color;
    real refraction_index;

    template <class Container>
    static void clean_up(Container& c) {
      typedef Container::iterator Itor;
      Itor i = c.begin(),
           end = c.end();
      for (; i != end; ++i) {
        delete *i;
      }
      c.swap(Container());  // clear the content using the swap trick
    }

    void clear() {
      clean_up(objects);
      clean_up(lights);
    }

    Impl() {
      refraction_index = 1;
    }

    ~Impl() {
      clear();
    }
  };


  World3D::World3D()
    : pimpl(new Impl) {}

  World3D::~World3D() {
    delete pimpl;
  }

  void World3D::add(Object3D* shape) {
    pimpl->objects.push_back(shape);
  }

  void World3D::remove(Object3D* shape) {
    pimpl->objects.remove(shape);
  }

  void World3D::add(Light* light) {
    pimpl->lights.push_back(light);
  }

  void World3D::remove(Light* light) {
    pimpl->lights.remove(light);
  }

  const ColorRGB& World3D::get_ambient_color() const {
    return pimpl->ambient_color;
  }

  void World3D::set_ambient_color(const ColorRGB& color) {
    pimpl->ambient_color = color;
  }

  const ColorRGB& World3D::get_background_color() const {
    return pimpl->background_color;
  }

  void World3D::set_background_color(const ColorRGB& color) {
    pimpl->background_color = color;
  }

  real World3D::get_refraction_index() const {
    return pimpl->refraction_index;
  }

  void World3D::set_refraction_index(real ri) {
    pimpl->refraction_index = ri;
  }

  Object3D *World3D::intersect(const Ray& ray, real& min_dist,
                               Vector3D& normal, int& plane_idx) const {
    min_dist = numeric_limits<real>::infinity();
    Object3D *nearest_obj = 0;

    Impl::const_iterator i = pimpl->objects.begin(),
                         end = pimpl->objects.end();

    for (; i != end; ++i) {
      Vector3D n;
      real dist;
      int idx;
      dist = (*i)->intersect(ray, n, idx);
      if (dist > TG_EPSILON && dist < min_dist) {
        min_dist = dist;
        nearest_obj = (*i);
        normal = n;
        plane_idx = idx;
      }
    }

    return nearest_obj;
  }

  Object3D *World3D::contain(const Point3D& point) const {
    Object3D *nearest_obj = 0;

    Impl::const_iterator i = pimpl->objects.begin(),
                         end = pimpl->objects.end();

    for (; i != end; ++i) {
      if ((*i)->contain(point)) return (*i);
    }

    return 0;
  }

  // clear everything in the world
  void World3D::clear() {
    pimpl->clear();
  }

  void World3D::clear_lights() {
    pimpl->clean_up(pimpl->lights);
  }

  void World3D::clear_objects() {
    pimpl->clean_up(pimpl->objects);
  }


  //////////////////////////////////////////////////////////////////////////
  // ObjectIterator implementation

  struct World3D::ObjectIterator::Impl {
    typedef list<Object3D *> ObjectContainer;
    typedef ObjectContainer::iterator iterator;

    iterator cur;
    iterator end;

    Impl *clone() {
      Impl *rtv = new Impl(cur, end);
      return rtv;
    }

    Impl(const iterator& cur, const iterator& end) 
      : cur(cur), end(end) {}
  };

  World3D::ObjectIterator World3D::get_object_iterator() const {
    return ObjectIterator(
      new ObjectIterator::Impl(
        pimpl->objects.begin(),
        pimpl->objects.end()
      )
    );
  }

  World3D::ObjectIterator::ObjectIterator(Impl *pimpl)
    : pimpl(pimpl) {}

  World3D::ObjectIterator::ObjectIterator(const ObjectIterator& obj)
    : pimpl(obj.pimpl->clone()) {}

  World3D::ObjectIterator& World3D::ObjectIterator::operator=(const ObjectIterator& rhs) {
    Impl *new_pimpl = rhs.pimpl->clone();
    delete pimpl;
    pimpl = new_pimpl;
    return *this;
  }

  World3D::ObjectIterator::~ObjectIterator() {
    delete pimpl;
  }

  bool World3D::ObjectIterator::has_next() const {
    return pimpl->cur != pimpl->end;
  }

  Object3D *World3D::ObjectIterator::next() {
    return *pimpl->cur++;
  }


  //////////////////////////////////////////////////////////////////////////
  // LightIterator implementation

  struct World3D::LightIterator::Impl {
    typedef list<Light *> LightContainer;
    typedef LightContainer::iterator iterator;

    iterator cur;
    iterator end;

    Impl *clone() {
      Impl *rtv = new Impl(cur, end);
      return rtv;
    }

    Impl(const iterator& cur, const iterator& end) 
      : cur(cur), end(end) {}
  };

  World3D::LightIterator World3D::get_light_iterator() const {
    return LightIterator(
      new LightIterator::Impl(
        pimpl->lights.begin(),
        pimpl->lights.end()
      )
    );
  }

  World3D::LightIterator::LightIterator(Impl *pimpl)
    : pimpl(pimpl) {}

  World3D::LightIterator::LightIterator(const LightIterator& obj)
    : pimpl(obj.pimpl->clone()) {}

  World3D::LightIterator& World3D::LightIterator::operator=(const LightIterator& rhs) {
    Impl *new_pimpl = rhs.pimpl->clone();
    delete pimpl;
    pimpl = new_pimpl;
    return *this;
  }

  World3D::LightIterator::~LightIterator() {
    delete pimpl;
  }

  bool World3D::LightIterator::has_next() const {
    return pimpl->cur != pimpl->end;
  }

  Light *World3D::LightIterator::next() {
    return *pimpl->cur++;
  }
}
