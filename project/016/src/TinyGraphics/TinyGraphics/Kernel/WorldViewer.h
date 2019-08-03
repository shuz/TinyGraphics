#ifndef WORLD_VIEWER_INCLUDED__
#define WORLD_VIEWER_INCLUDED__

namespace TinyGraphics {

  class Graphics2D;
  class Camera;

  class WorldViewer {
  public:
    virtual
    ~WorldViewer() = 0;

    virtual
    void draw(Graphics2D *g2d) const = 0;

    virtual
    const Camera *get_camera() const = 0;

    virtual
    void set_camera(const Camera *camera) = 0;

  protected:
    WorldViewer();

  private:
    WorldViewer(const WorldViewer&);              // not implemented
    WorldViewer& operator=(const WorldViewer&);   // not implemented
  };
}

#endif
