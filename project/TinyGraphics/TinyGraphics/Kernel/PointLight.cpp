#include "PointLight.h"
#include "Ray.h"

namespace TinyGraphics {

  PointLight::PointLight() 
    : intensity(1), color(ColorRGB::WHITE), 
      attenuation(1, 0, 0) {}

  PointLight::~PointLight() {}

  bool PointLight::illuminate(const Point3D& point, Ray& ray) const {
    ray.origin = location;
    ray.direction = point - location;
    real dist = ray.direction.norm();     // get the distance

    if (dist == 0) return false;          // the singular point, can't be illuminated

    ray.direction.normalize();

    real fatt = attenuation(0) + 
                attenuation(1) * dist +
                attenuation(2) * dist * dist;
    ray.color = this->color;
    if (fatt > 1.0) ray.color.scale(intensity/fatt);

    return true;
  }
}
