// MyController.cpp: implementation of the CMyController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CGFramework.h"
#include "MyController.h"
#include <algorithm>
#include <cassert>

//////////////////////////////////////////////////////////////////////
// local functions
//////////////////////////////////////////////////////////////////////
static inline
int round(double v) {
  return int(v + 0.5);
}

static inline
int sgn(int n) {
  if (n > 0)
    return +1;
  if (n < 0)
    return -1;
  return 0;
}

static inline 
int abs(int n) {
  return n>=0 ? n : -n;
}

static inline 
void DrawPoint(CControllerBase *c, Point p,
               unsigned int color = RGB(0, 0, 0), int size = 2) {
  c->DrawPixel(p.x, p.y, color, size);
}

static inline
void DrawLine(CControllerBase *c, Line l, int width = 1) {
  c->DrawLine(l.begin.x, l.begin.y, l.end.x, l.end.y, l.color, width);
}

// end local functions
//////////////////////////////////////////////////////////////////////



// 请务必添加下面这句话，第一个参数是你的类名，第二个是基类类名
// Be sure to add this macro. the first parameter is your class name, and the second the base class name
IMPLEMENT_DYNCREATE( CMyController, CControllerBase );

// 这里定义菜单项ID，请以CGF_MENU_ID为起始值顺序累加，累加值不要超过100
// Here define menu ID, please based on CGF_MENU_ID
#define MYMENU_LINE		CGF_MENU_ID
#define MYMENU_CLIP   CGF_MENU_ID + 1
#define MYMENU_CLEAR  CGF_MENU_ID + 2

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

const int xmin = 100;
const int xmax = 400;
const int ymin = 100;
const int ymax = 300;

CMyController::CMyController()
{
	m_isDrawing = false;
  m_curMenu = MYMENU_LINE;
  unsigned int borderColor = RGB(0, 0, 0xFF);
  m_clipBorder[0] = Line(Point(xmin, ymin), Point(xmin, ymax), borderColor);
  m_clipBorder[1] = Line(Point(xmin, ymax), Point(xmax, ymax), borderColor);
  m_clipBorder[2] = Line(Point(xmax, ymax), Point(xmax, ymin), borderColor);
  m_clipBorder[3] = Line(Point(xmax, ymin), Point(xmin, ymin), borderColor);
}

CMyController::~CMyController()
{
}

char* CMyController::GetName()
{
	return "Line Controller";
}

void CMyController::Init()
{
	// 在这里插入所需的菜单项
	// Here insert customer menu
	InsertMenu(MYMENU_LINE, "Draw &Line");
  InsertMenu(MYMENU_CLIP, "C&lip");
  InsertMenu(MYMENU_CLEAR, "&Clear");
}

void CMyController::OnCustomerMenu(unsigned int id)
{
	// 在这里响应菜单项，现在所做的是在画点与画线之间切换状态
	// Respond to menu action. here the task is switch state between draw pixel and line
	if( id == MYMENU_LINE )
	{
		m_curMenu = MYMENU_LINE;
		Refresh();
  } else
  if (id == MYMENU_CLIP) {
    int i, n;
    for (i = 0, n = m_lines.size(); i < n; ++i) {
      Clip(m_lines[i]);
    }
    Refresh();
  } else
  if (id == MYMENU_CLEAR) {
    m_lines.clear();
    Refresh();
  }
}

void CMyController::OnPaint()
{
	DrawClipBorder();
  DrawText(10, 10, "用菜单中的Clip命令进行裁减", RGB(0xFF, 0, 0));

  int i, n;
  for (i = 0, n = m_lines.size(); i < n; ++i) {
    if (m_lines[i].visible)
      ::DrawLine(this, m_lines[i]);
  }
}

void CMyController::OnKeyPress(char key)
{
}

void CMyController::OnLButtonDown(int x, int y)
{
	// 鼠标点击
	// mouse left button down

  if( m_curMenu == MYMENU_LINE )
	{
		// 画线分两阶段，用m_bDrawing作为标志，这里演示了橡皮筋技术
		// drawing line has two phase, m_bDrawing is the flag indication whether the first point has been got
		if( m_isDrawing )
		{
			m_isDrawing = false;
		}
		else
		{
      Line line;
			line.begin.x = line.end.x = x;
			line.begin.y = line.end.y = y;
      line.color = RGB(0xFF, 0, 0);
      m_lines.push_back(line);
      m_isDrawing = true;
		}
	}
}

void CMyController::OnMouseMove( int x, int y )
{
	if( m_curMenu == MYMENU_LINE )
	{
		// 橡皮筋：如果画线的第一个点已经被按下，则只要鼠标移动就会更新第二个点的坐标
		if( m_isDrawing )
		{
			m_lines.back().end.x = x;
			m_lines.back().end.y = y;
			Refresh();
		}
	}
}

void CMyController::DrawClipBorder() {
  for (int i = 0; i < 4; ++i) 
    ::DrawLine(this, m_clipBorder[i]);
}


static bool CLIPt(double denom, double num, double *tE, double *tL) {
  double t;

  if (denom > 0) {
    t = num / denom;
    if (t > *tL)
      return false;
    else
    if (t > *tE)
      *tE = t;
  } else
  if (denom < 0) {
    t = num / denom;
    if (t < *tE)
      return false;
    else
    if (t < *tL)
      *tL = t;
  } else
  if (num > 0)
    return false;
  return true;
}

void CMyController::Clip(Line& line)
{
  double dx = line.end.x - line.begin.x;
  double dy = line.end.y - line.begin.y;
  assert(dx != 0 && dy != 0);

  line.visible = false;

  double tE = 0.0;
  double tL = 1.0;
  if (CLIPt(dx, xmin-line.begin.x, &tE, &tL))
    if (CLIPt(-dx, line.begin.x-xmax, &tE, &tL))
      if (CLIPt(dy, ymin-line.begin.y, &tE, &tL))
        if (CLIPt(-dy, line.begin.y-ymax, &tE, &tL)) {
          line.visible = true;
          if (tL < 1) {
            line.end.x = line.begin.x + tL * dx;
            line.end.y = line.begin.y + tL * dy;
          }
          if (tE > 0) {
            line.begin.x += tE * dx;
            line.begin.y += tE * dy;
          }
        }
}

