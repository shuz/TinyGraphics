#ifndef PRIMITIVE_2D_INCLUDED__
#define PRIMITIVE_2D_INCLUDED__

struct Point {
  int x, y;
  Point() {}
  Point(int xx, int yy) : x(xx), y(yy) {}

  void assign(int xx, int yy) {
    x = xx;  y = yy;
  }
};

struct Line {
  Point begin, end;

  Line() {}
  Line(Point b, Point e)
    : begin(b), end(e) {}
};

#endif
