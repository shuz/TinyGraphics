#ifndef WORLD_3D_INCLUDED__
#define WORLD_3D_INCLUDED__

#include "Real.h"

namespace TinyGraphics {

  class Object3D;
  class Light;
  class Point3D;
  class ColorRGB;
  class Ray;
  class Vector3D;

  class World3D {
  public:
    World3D();
    ~World3D();

    class ObjectIterator {
    public:
      friend class World3D;

      ObjectIterator(const ObjectIterator&);
      ObjectIterator& operator=(const ObjectIterator&);

      ~ObjectIterator();

      bool has_next() const;
      Object3D *next();

    private:
      struct Impl;
      Impl *pimpl;

      ObjectIterator(Impl *pimpl);
    };

    class LightIterator {
    public:
      friend class World3D;

      LightIterator(const LightIterator&);
      LightIterator& operator=(const LightIterator&);

      ~LightIterator();

      bool has_next() const;
      Light *next();

    private:
      struct Impl;
      Impl *pimpl;

      LightIterator(Impl *pimpl);
    };

    // add objects to the world
    // note: World3D will take over the cleaning up of the object
    void add(Object3D* shape);
    void add(Light *light);

    // remove object from the world
    // note: World3D will return the control of the object to the
    //       caller, so that the caller should do clean up herself
    void remove(Object3D* shape);
    void remove(Light *light);

    const ColorRGB& get_ambient_color() const;
    void set_ambient_color(const ColorRGB& color);

    const ColorRGB& get_background_color() const;
    void set_background_color(const ColorRGB& color);

    real get_refraction_index() const;
    void set_refraction_index(real ri);

    // iterate the world
    ObjectIterator get_object_iterator() const;
    LightIterator  get_light_iterator() const;


    // compute the first hit point of the ray in the world.
    //
    // params:
    //   ray: the ray from which the hit point is computed
    //   hit_point:
    //     output parameter,
    //     ray.point_at(hit_point) is the hit point
    //     if hit_point <= 0, there is no hit point
    //   normal:
    //     output parameter,
    //     set to be the unit normal vector of the hit point
    //   plane:idx:
    //     output parameter,
    //     used to in Object3D::get_plane_coord
    // returns:
    //   the object the ray hits. return 0 if nothing hit.
    // note:
    //   return value == 0 indicates there is no hit point,
    //   and the hit_point and the normal becomes invalid in this situation.
    Object3D *intersect(const Ray& ray, real& hit_point,
                        Vector3D& normal, int& plane_idx) const;

    // get the first object that contains the point
    // returns:
    //   the first object that contains the point.
    //   return 0 if no object found.
    Object3D *contain(const Point3D& point) const;

    // clear everything in the world
    void clear();

    void clear_objects();
    void clear_lights();

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
