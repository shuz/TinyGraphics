#ifndef GOUROUD_SHADING_WORLD_VIEWER_INCLUDED__
#define GOUROUD_SHADING_WORLD_VIEWER_INCLUDED__

#include "WorldViewer.h"

namespace TinyGraphics {
  class World3D;
  class Camera;

  class GouroudShadingWorldViewer : public WorldViewer {
  public:
    // use_material:
    //   shading will use material.k_diffuse and k_ambient if true
    //   use the color only if false
    GouroudShadingWorldViewer(const World3D *world, const Camera *camera,
                              bool use_material = false);
    ~GouroudShadingWorldViewer();

    void draw(Graphics2D *g2d) const;
    const Camera *get_camera() const;
    void set_camera(const Camera *camera);

  private:
    // the following members are not implemented
    GouroudShadingWorldViewer(const GouroudShadingWorldViewer&);
    GouroudShadingWorldViewer& operator=(const GouroudShadingWorldViewer&);

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
