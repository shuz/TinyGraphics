#include "ProjectPainter3D.h"
#include "Matrix4D.h"
#include "Transform.h"
#include "Primitive3D.h"
#include "Primitive2D.h"
#include "Painter.h"

struct ProjectPainter3D_impl {
  Matrix4D projector;
  Painter *painter2d;
};

ProjectPainter3D::ProjectPainter3D(Painter *painter)
  : pImpl(new ProjectPainter3D_impl) {

  pImpl->painter2d = painter;
  Identity(pImpl->projector);
}

ProjectPainter3D::~ProjectPainter3D() {
  delete pImpl;
}

// the following matrices determine the projection 
// of the world to the controller
void ProjectPainter3D::setProjector(Matrix4D& m) {
  pImpl->projector = m;
}

Matrix4D ProjectPainter3D::getProjector() {
  return pImpl->projector;
}

void ProjectPainter3D::transformProjector(Matrix4D& m) {
  pImpl->projector = pImpl->projector * m;
}

void ProjectPainter3D::drawLine(Line3D& line, unsigned int color) {
  Line line2d;
  Line3D line3d(line);

  line3d.transform(pImpl->projector);

  line2d.begin.x = line3d.begin.x();
  line2d.begin.y = line3d.begin.y();
  
  line2d.end.x = line3d.end.x();
  line2d.end.y = line3d.end.y();

  pImpl->painter2d->drawLine(line2d, color);
}

void ProjectPainter3D::drawPixel(Point3D& point, unsigned int color) {
  Point point2d;
  Point3D point3d(point);

  point3d.transform(pImpl->projector);
  point2d.x = point3d.x();
  point2d.y = point3d.y();

  pImpl->painter2d->drawPixel(point2d, color);
}
