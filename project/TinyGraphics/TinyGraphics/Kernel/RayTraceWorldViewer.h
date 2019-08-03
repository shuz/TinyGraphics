#ifndef RAY_TRACE_WORLD_VIEWER_INCLUDED__
#define RAY_TRACE_WORLD_VIEWER_INCLUDED__

#include "WorldViewer.h"

namespace TinyGraphics {

  class World3D;
  class Camera;
  class ColorRGB;
  class Ray;

  class RayTraceWorldViewer : public WorldViewer {
  public:
    RayTraceWorldViewer(const World3D *world, const Camera *camera,
                        int reflect_depth, int refract_depth);
    ~RayTraceWorldViewer();

    void draw(Graphics2D *g2d) const;
    const Camera *get_camera() const;
    void set_camera(const Camera *camera);

  private:
    RayTraceWorldViewer(const RayTraceWorldViewer&);             // not implemented
    RayTraceWorldViewer& operator=(const RayTraceWorldViewer&);  // not implemented

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
