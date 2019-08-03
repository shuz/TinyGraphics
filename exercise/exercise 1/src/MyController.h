#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "ControllerBase.h"
#include <vector>

struct Point {
  int x, y;
  Point() {}
  Point(int xx, int yy) : x(xx), y(yy) {}
};

struct Line {
  Point begin, end;
  unsigned int color;
  Line() 
    : color(RGB(0, 0, 0)) {}
  Line(Point b, Point e, unsigned int c)
    : begin(b), end(e), color(c) {}
};


//////////////////////////////////////////////////////////////////////////
// 示例控制器
class CMyController : public CControllerBase  
{
	DECLARE_DYNCREATE( CMyController );
	
public:
	CMyController();
	virtual ~CMyController();

	virtual void OnMouseMove( int x, int y );   // 鼠标移动时的回调函数
	virtual void OnLButtonDown( int x, int y );	// 鼠标左键按下时的回调函数
	virtual void OnKeyPress( char key );        // 键盘按下时的回调函数
	virtual void OnPaint();                     // 窗口重绘时的回调函数
	virtual void OnCustomerMenu(unsigned int id);	// 菜单点击时的回调函数
	virtual void Init();                          // 初始化函数
	virtual char* GetName();                      // 提供对本控制器的描述

private:
	std::vector<Line> m_lines;
  std::vector<Point> m_points;
  int m_curMenu;
  bool m_isDrawing;

  void DrawGrid();
  void AddLineWithGrid(Line l);
	void AddPixelWithGrid(int x, int y);
};

#endif // #ifndef MYCONTROLLER_H
