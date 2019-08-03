#ifndef LINE_FRAME_WORLD_VIEWER_INCLUDED__
#define LINE_FRAME_WORLD_VIEWER_INCLUDED__

#include "WorldViewer.h"

namespace TinyGraphics {

  class World3D;
  class Camera;

  class LineFrameWorldViewer : public WorldViewer {
  public:
    LineFrameWorldViewer(const World3D *world, const Camera *camera);
    ~LineFrameWorldViewer();

    void draw(Graphics2D *g2d) const;
    const Camera *get_camera() const;
    void set_camera(const Camera *camera);

  private:
    // the following members are not implemented
    LineFrameWorldViewer(const LineFrameWorldViewer&);
    LineFrameWorldViewer& operator=(const LineFrameWorldViewer&);

  private:
    struct Impl;
    Impl *pimpl;
  };
}

#endif
