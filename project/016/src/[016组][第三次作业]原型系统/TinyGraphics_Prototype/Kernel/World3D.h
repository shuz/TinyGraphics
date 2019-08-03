#ifndef WORLD_3D_INCLUDED__
#define WORLD_3D_INCLUDED__

class Object3D;
class Graphics3D;

class World3D {
public:
  World3D();
  ~World3D();

  class Iterator {
    friend class World3D;
    ~Iterator();

    bool has_next();
    Object3D *next();

  private:
    struct Impl;
    Impl *pimpl;

    Iterator(Impl *pimpl);
    Iterator(const Iterator&);             // not implemented
    Iterator& operator=(const Iterator&);  // not implemented
  };

  // add objects to the world
  // note: World3D will take over the cleaning up of the shape
  void add(Object3D* shape);

  // remove object from the world
  // note: World3D will return the control of the object to the
  //       caller, so that the caller should do clean up herself
  void remove(Object3D* shape);

  // draw the objects in the painter
  void draw(Graphics3D *painter) const;

  // iterate the world
  Iterator get_iterator();

  // clear everything in the world
  void clear();

private:
  struct Impl;
  Impl *pimpl;
};

#endif
