#ifndef PAINTER_INCLUDED__
#define PAINTER_INCLUDED__

struct Line;
struct Point;

// note: since Line and Point don't take the const semantic,
//       all Line& and Point& here means const refrence passing,
//       with value passing semantic.

class Painter {
public:
  Painter();
  virtual ~Painter() = 0;

  virtual void drawLine(Line& line, unsigned int color = 0) = 0;
  virtual void drawPixel(Point& point, unsigned int color = 0) = 0;
};

#endif
