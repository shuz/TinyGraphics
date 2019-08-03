#ifndef LIGHT_INCLUDED__
#define LIGHT_INCLUDED__

namespace TinyGraphics {

  class Point3D;
  class Vector3D;
  class ColorRGB;
  class Ray;

  class Light {
  public:
    virtual
    ~Light() = 0;

    // get the effect of this light on the point, 
    // 
    // params:
    //   point:
    //     the point to illuminate
    //   ray:
    //     output parameter,
    //     ray.origin is the location of the light,
    //     ray.direction is the unit vector from the origin to the point
    //     ray.color is the color this light contributes on the point
    // returns:
    //   true if the light can reach the point
    // note:
    //   if the return value is false, the ray output is invalid.
    virtual
    bool illuminate(const Point3D& point, Ray& ray) const = 0;

  protected:
    Light();

  private:
    Light(const Light&);              // not implemented
    Light& operator=(const Light&);   // not implemented
  };
}

#endif

