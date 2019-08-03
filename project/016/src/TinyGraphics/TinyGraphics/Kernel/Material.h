#ifndef MATERIAL_INCLUDED__
#define MATERIAL_INCLUDED__

#include "ColorRGB.h"
#include "Real.h"

namespace TinyGraphics {

  class Texture;

  class Material {
  public:
    ColorRGB color;
    int shininess;
    real k_ambient;
    real k_specular;
    real k_diffuse;
    real k_transparency;
    real refraction_index;

    Texture *texture;

    Material() {
      color = ColorRGB::WHITE;
      shininess        = 5;
      k_ambient        = 1;
      k_specular       = 0.2;
      k_diffuse        = 0.8;
      k_transparency   = 0;
      refraction_index = 1;
      texture = 0;
    }
  };
}

#endif
