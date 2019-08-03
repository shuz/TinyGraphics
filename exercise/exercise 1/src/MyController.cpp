// MyController.cpp: implementation of the CMyController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CGFramework.h"
#include "MyController.h"
#include <algorithm>

const int GRID_GAP = 30;
const int PIXSIZE = 10;

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

static inline
Line RoundEndPoints(Line l) {
  double xs, xe, ys, ye;
  xs = l.begin.x / (double)GRID_GAP;
  xe = l.end.x   / (double)GRID_GAP;
  ys = l.begin.y / (double)GRID_GAP;
  ye = l.end.y   / (double)GRID_GAP;

  double dx = xs - xe;
  double dy = ys - ye;

  Line ret;
  ret.color = l.color;

  if (dx == 0 || dy == 0) {
    ret.begin.x = round(xs);
    ret.begin.y = round(ys);
    ret.end.x = round(xe);
    ret.end.y = round(ye);
    return ret;
  }

  double k = dy / dx;

  bool isSwaped = false;
  if (k < -1 || k > 1) {
    std::swap(dx, dy);
    std::swap(xs, ys);
    std::swap(xe, ye);
    k = dy / dx;
    isSwaped = true;
  }

  int ixs, ixe;
  ixs = round(xs);
  ixe = round(xe);

  ret.begin.x = round(ixs);
  ret.begin.y = round(k * (ixs - xs) + ys);
  ret.end.x = round(ixe);
  ret.end.y = round(k * (ixe - xe) + ye);

  if (isSwaped) {
    std::swap(ret.begin.x, ret.begin.y);
    std::swap(ret.end.x, ret.end.y);
  }
  ret.color = l.color;
  return ret;
}

static inline
Line GridToPixel(Line line) {
  Line ret;
  ret.begin.x = line.begin.x * GRID_GAP;
  ret.begin.y = line.begin.y * GRID_GAP;
  ret.end.x = line.end.x * GRID_GAP;
  ret.end.y = line.end.y * GRID_GAP;
  ret.color = line.color;
  return ret;
}

// end local functions
//////////////////////////////////////////////////////////////////////



// 请务必添加下面这句话，第一个参数是你的类名，第二个是基类类名
// Be sure to add this macro. the first parameter is your class name, and the second the base class name
IMPLEMENT_DYNCREATE( CMyController, CControllerBase );

// 这里定义菜单项ID，请以CGF_MENU_ID为起始值顺序累加，累加值不要超过100
// Here define menu ID, please based on CGF_MENU_ID
#define MYMENU_LINE		CGF_MENU_ID
#define MYMENU_CLEAR  CGF_MENU_ID + 1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyController::CMyController()
{
	m_isDrawing = false;
  m_curMenu = MYMENU_LINE;
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
  if (id == MYMENU_CLEAR) {
    m_lines.clear();
    m_points.clear();
    Refresh();
  }
}

void CMyController::OnPaint()
{
	DrawGrid();

  int i, n;
  for (i = 0, n = m_points.size(); i < n; ++i) {
    ::DrawPoint(this, m_points[i], RGB(0, 0xFF, 0), PIXSIZE);
  }

  for (i = 0, n = m_lines.size(); i < n; ++i) {
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
      Line intLine = ::RoundEndPoints(m_lines.back());
      Line oriCord = ::GridToPixel(intLine);
      oriCord.color = RGB(0xFF, 0, 0);
      m_lines.push_back(oriCord);
      AddLineWithGrid(intLine);
		}
		else
		{
      Line line;
			line.begin.x = line.end.x = x;
			line.begin.y = line.end.y = y;
      line.color = RGB(0, 0, 0xFF);
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

void CMyController::DrawGrid() {
  RECT rect;
  m_pView->GetClientRect(&rect);

  int i;
  Line line;
  line.color = RGB(0, 0, 0xFF);
  line.begin.x = rect.left;
  line.end.x = rect.right;
  for (i = rect.top; i < rect.bottom; i += GRID_GAP) {
    line.begin.y = line.end.y = i;
    ::DrawLine(this, line);
  }

  line.begin.y = rect.top;
  line.end.y = rect.bottom;
  for (i = rect.left; i < rect.right; i += GRID_GAP) {
    line.begin.x = line.end.x = i;
    ::DrawLine(this, line);
  }
}

void CMyController::AddLineWithGrid(Line line) {
  int dx = line.end.x - line.begin.x;
  int dy = line.end.y - line.begin.y;
  int incrX = sgn(dx);
  int incrY = sgn(dy);
  dx = abs(dx);
  dy = abs(dy);

  bool flag = false;
  if (dx < dy) {
    flag = true;
    std::swap(dx, dy);
  }

  int error = 2 * dy - dx;
  int incr1 = 2 * (dy - dx),
      incr2 = 2 * dy;
  int x = line.begin.x;
  int y = line.begin.y;
  for (int i = 0; i <= dx; ++i) {
    AddPixelWithGrid(x, y);
    if (error >= 0) {
      x += incrX;
      y += incrY;
      error += incr1;
    } else {
      if (flag) 
        y += incrY;
      else 
        x += incrX;
      error += incr2;
    }
  }
  Refresh();
}

void CMyController::AddPixelWithGrid(int x, int y)
{
  Point p;
  p.x = GRID_GAP * x;
  p.y = GRID_GAP * y;
  m_points.push_back(p);
}
