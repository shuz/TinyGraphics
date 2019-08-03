#ifndef POINT_LIGHT_INCLUDED__
#define POINT_LIGHT_INCLUDED__

#include "Light.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "ColorRGB.h"
#include "Real.h"

namespace TinyGraphics {

  class PointLight : public Light {
  public:
    PointLight();
    ~PointLight();

    Point3D location;
	  real intensity;
	  ColorRGB color;
	  
    // f_att = 1 / (vec(0) + vec(1)*r + vec(2)*r*r)
	  Vector3D attenuation;

    bool illuminate(const Point3D& point, Ray& ray) const;
  };
}

#endif
