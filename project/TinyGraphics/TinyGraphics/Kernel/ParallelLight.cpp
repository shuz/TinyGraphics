#include "ParallelLight.h"
#include "Ray.h"

namespace TinyGraphics {

  ParallelLight::ParallelLight() 
    : direction(1, 0, 0),
    intensity(1), color(ColorRGB::WHITE), 
      attenuation(1, 0, 0) {}

  ParallelLight::~ParallelLight() {}

  bool ParallelLight::illuminate(const Point3D& point, Ray& ray) const {
    real dist = direction.dot_product(point - location);
    if (dist <= 0) return false;          // can't be illuminated

    ray.origin = point + direction * (-dist);
    ray.direction = direction;

    real fatt = attenuation(0) + 
                attenuation(1) * dist +
                attenuation(2) * dist * dist;
    ray.color = this->color;
    if (fatt > 1.0) ray.color.scale(intensity/fatt);

    return true;
  }
}
