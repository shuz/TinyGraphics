#ifndef PARALLEL_LIGHT_INCLUDED__
#define PARALLEL_LIGHT_INCLUDED__

#include "Light.h"
#include "Primitive3D.h"
#include "Vector3D.h"
#include "ColorRGB.h"
#include "Real.h"

namespace TinyGraphics {

  class ParallelLight : public Light {
  public:
    ParallelLight();
    ~ParallelLight();  

    // location and direction determine a plane
    Point3D location;
    // assumed to be a unit vector
    Vector3D direction;

	  real intensity;
	  ColorRGB color;
	  
    // f_att = 1 / (vec(0) + vec(1)*r + vec(2)*r*r)
	  Vector3D attenuation;

    // true if the distance from point to plane is positive
    bool illuminate(const Point3D& point, Ray& ray) const;
  };
}

#endif
