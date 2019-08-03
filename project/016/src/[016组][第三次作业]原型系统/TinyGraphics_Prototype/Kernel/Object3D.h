#ifndef OBJECT_3D_INCLUDED__
#define OBJECT_3D_INCLUDED__

class Graphics3D;

class Object3D {
public:
  virtual
  ~Object3D() = 0;

  virtual
  void draw(Graphics3D *graphics) const = 0;

protected:
  Object3D();

private:
  Object3D(const Object3D&);              // not implemented
  Object3D& operator=(const Object3D&);   // not implemented
};

#endif
