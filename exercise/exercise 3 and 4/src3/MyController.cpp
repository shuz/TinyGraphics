// MyController.cpp: implementation of the CMyController class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CGFramework.h"
#include "MyController.h"
#include "DlgPivot.h"

#include "Utilities/Matrix4D.h"
#include "Utilities/Transform.h"
#include "Utilities/Primitive2D.h"
#include "Utilities/Painter.h"
#include "Utilities/ProjectPainter3D.h"
#include "Utilities/World3D.h"
#include "Utilities/Shape3D/SLine3D.h"

#include <cmath>
#include <algorithm>
using namespace std;

#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

const double PI = asin(1) * 2;

struct ControllerPainter : Painter {
  
  ControllerPainter(CControllerBase *controller,
                    Point origin = Point(0, 0))
    : m_pController(controller), m_origin(origin) {}

  void setOrigin(Point o) {
    m_origin = o;
  }

  virtual ~ControllerPainter() {}

  virtual void drawLine(Line& line, unsigned int color = 0) {
    m_pController->DrawLine(m_origin.x + line.begin.x,
                            m_origin.y - line.begin.y,
                            m_origin.x + line.end.x,
                            m_origin.y - line.end.y,
                            color);
  }
  
  virtual void drawPixel(Point& point, unsigned int color = 0) {
    m_pController->DrawPixel(m_origin.x + point.x,
                             m_origin.y - point.y, color, 1);
  }

private:
  CControllerBase *m_pController;
  Point m_origin;
};

const double dtheta = PI/256;

struct CMyController_impl {
  Point lastPos;          // last mouse position

  ControllerPainter painter2d;
  ProjectPainter3D painter;
  World3D world;

  SLine3D *pivot;         // the current pivot that is stored in the world
                          // used when removing it from the world

  Line3D pivotLine;
  double theta;

  double alpha;           // the current angle that the object has turned
  Matrix4D t_ry_rx,       // buffered matrices that will not change with
           rx_ry_t;       // the same pivot

  bool buttonDown;

  CMyController_impl(CControllerBase *c) 
    : lastPos(0, 0), painter2d(c),
      painter(&painter2d), buttonDown(false)
  {
    resetWorld();
  }

  ~CMyController_impl() {
    // need not delete pivot since the dtor of the world will manage it
  }

  void resetWorld() {     // reset the world to its origin state
    pivot = 0;    // need not delete pivot since the world.clear() will manage it
    alpha = 0;
    theta = dtheta;
    buttonDown = false;

    double x, y, z;
    double dx, dy, dz;
    x = 100; y = 100; z = 100;
    dx = 160; dy = 80; dz = 100;

    Line3D object[] = {       // objects to rotate
      Line3D(Point3D(x, y, z), Point3D(x+dx, y, z)),
      Line3D(Point3D(x, y, z), Point3D(x, y+dy, z)),
      Line3D(Point3D(x, y, z), Point3D(x, y, z+dz)),
    };

    Line3D axes[] = {                     // x, y, z
      Line3D(Point3D(0, 0, 0), Point3D(1000, 0, 0)),
      Line3D(Point3D(0, 0, 0), Point3D(0, 1000, 0)),
      Line3D(Point3D(0, 0, 0), Point3D(0, 0, 1000)),
    };

    Matrix4D m;

    const double CABI_ALPHA = PI/6;
    Point3D d(-cos(CABI_ALPHA) / 2, -sin(CABI_ALPHA) / 2, -1);
    ::ParallelProject(100, d, m);         // project to the screen

    Matrix4D px, py, pz;
    ::Identity(px);  px[0][0] = 0;        // project to x=0;
    ::Identity(py);  py[1][1] = 0;        // project to y=0;
    ::Identity(pz);  pz[2][2] = 0;        // project to z=0;

    world.clear();
    unsigned int objectColor = RGB(0, 0, 0xFF);
    SLine3D* lines[] = {
      new SLine3D(object[0], objectColor),
      new SLine3D(object[1], objectColor),
      new SLine3D(object[2], objectColor),
    };

    int i;
    for (i = 0; i < ARRAYSIZE(lines); ++i) {
      world.add(lines[i]);
    }
    
    unsigned int axesColor = RGB(0, 0, 0);
    world.addAbsolute(new SLine3D(axes[0], axesColor));
    world.addAbsolute(new SLine3D(axes[1], axesColor));
    world.addAbsolute(new SLine3D(axes[2], axesColor));

    painter.setProjector(m);

    setupPivot(Line3D(Point3D(0, 0, 0), Point3D(0, 1000, 0)));
  }

  void rotate(double dtheta) {
    Matrix4D m;

    alpha += dtheta;
    ::RotateY(alpha, m);

    m = t_ry_rx * m * rx_ry_t;
    world.setWorldTransformer(m);
  }

  void setupPivot(Line3D& line) {
    SLine3D *newPivot = new SLine3D(line, RGB(0xFF, 0, 0));

    setupTransformMatrices(line);
    world.removeAbsolute(pivot);
    delete pivot;
    pivot = newPivot;
    world.addAbsolute(pivot);

    pivotLine = line;
  }

  void setupTransformMatrices(Line3D& line) {
    ASSERT(line.begin != line.end);

    double dx = line.end.x() - line.begin.x();
    double dy = line.end.y() - line.begin.y();
    double dz = line.end.z() - line.begin.z();

    double distXZ2 = dx*dx + dz*dz;     // x^2 + z^2
    double distXZ = sqrt(distXZ2);
    double distXYZ = sqrt(distXZ2 + dy*dy);  // sqrt(x^2 + y^2 + z^2)

    Matrix4D t, t_1;          // t and t^(-1)
    ::Transfer(-line.begin.x(), -line.begin.y(), -line.begin.z(), t);
    ::Transfer(line.begin.x(), line.begin.y(), line.begin.z(), t_1);

    if (distXZ2 == 0) {       // need not rotate anymore
      t_ry_rx = t;
      rx_ry_t = t_1;
      return;
    }

    double sinay = dx/distXZ,           // sin alphaY
           cosay = dz/distXZ;           // cos alphaY
    double sinax = distXZ/distXYZ,      // sin alphaX
           cosax = dy/distXYZ;          // cos alphaX

    Matrix4D rx, ry,          // rotate x and rotate y
             ry_rx, ry_rx_1;    // ry*rx and (rx*ry)^-1

    ::Identity(rx);
    ::Identity(ry);
    ry[0][0] = cosay;  ry[0][2] = sinay;
    ry[2][0] = -sinay;  ry[2][2] = cosay;

    rx[1][1] = cosax;  rx[1][2] = -sinax;
    rx[2][1] = sinax; rx[2][2] = cosax;

    multiply(ry_rx, ry, rx);
    transpose(ry_rx_1, ry_rx);    // ry_rx_1 = ry_rx ^ T

    t_ry_rx = t * ry_rx;
    rx_ry_t = ry_rx_1 * t_1;
  }
};


// 请务必添加下面这句话，第一个参数是你的类名，第二个是基类类名
// Be sure to add this macro. the first parameter is your class name, and the second the base class name
IMPLEMENT_DYNCREATE( CMyController, CControllerBase );

// 这里定义菜单项ID，请以CGF_MENU_ID为起始值顺序累加，累加值不要超过100
// Here define menu ID, please based on CGF_MENU_ID
#define MYMENU_PIVOT	CGF_MENU_ID
#define MYMENU_RESET  CGF_MENU_ID + 1

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMyController::CMyController()
{
  pImpl = new CMyController_impl(this);
}

CMyController::~CMyController()
{
}

char* CMyController::GetName()
{
	return "Rotate Controller";
}

void CMyController::Init()
{

	// 在这里插入所需的菜单项
	// Here insert customer menu
	InsertMenu(MYMENU_PIVOT, "Set &Pivot...");
  InsertMenu(MYMENU_RESET, "&Reset");
  ::SetTimer(m_pView->m_hWnd, 0, 15, NULL);
}

void CMyController::OnCustomerMenu(unsigned int id)
{
	// 在这里响应菜单项，现在所做的是在画点与画线之间切换状态
	// Respond to menu action. here the task is switch state between draw pixel and line
	if( id == MYMENU_PIVOT )
	{
		CDlgPivot dialog(pImpl->pivotLine);
    int sel = dialog.DoModal();
    if (sel == IDOK) {
      Line3D line(Point3D(dialog.m_x0, dialog.m_y0, dialog.m_z0),
                  Point3D(dialog.m_x1, dialog.m_y1, dialog.m_z1));
      pImpl->resetWorld();
      pImpl->setupPivot(line);
    }
  } else
  if (id == MYMENU_RESET) {
    pImpl->resetWorld();
  }
  Refresh();
}

void CMyController::OnPaint()
{
  DrawText(20, 20, "按住鼠标左键拖曳使其手动旋转，速度在放开鼠标后保留", RGB(0xFF, 0, 0));
  pImpl->world.draw(&pImpl->painter);
}

void CMyController::OnSize(unsigned int nType, int cx, int cy) {
  RECT rect;
  m_pView->GetClientRect(&rect);

  pImpl->painter2d.setOrigin(Point(rect.right / 3,
                                   rect.bottom - rect.bottom / 3));
}

void CMyController::OnKeyPress(char key)
{
}

void CMyController::OnLButtonDown(int x, int y)
{
  pImpl->buttonDown = true;
  pImpl->lastPos.assign(x, y);
}

void CMyController::OnLButtonUp(int x, int y) {
  pImpl->buttonDown = false;
}

// the macro below is used in OnMouseMove only
#define ROTATE(axis) do {                                   \
    pImpl->theta = (axis - pImpl->lastPos.axis) * dtheta;   \
    pImpl->rotate(pImpl->theta);                            \
    rotated = (pImpl->theta != 0);                          \
} while (0)

void CMyController::Move( int x, int y )
{
  if (pImpl->buttonDown) {
    double dx = pImpl->pivotLine.end.x() - pImpl->pivotLine.begin.x();
    double dy = pImpl->pivotLine.end.y() - pImpl->pivotLine.begin.y();
    bool rotated = false;

    if (dy < dx) {
      ROTATE(y);
      if (!rotated) {
        ROTATE(x);
      }
    } else {
      ROTATE(x);
      if (!rotated) {
        ROTATE(y);
      }
    }
    pImpl->lastPos.assign(x, y);
  }
}

void CMyController::OnTimer(unsigned int nIDEvent) {
  if (pImpl->buttonDown) {
    CPoint pos;
    ::GetCursorPos(&pos);
    ::ScreenToClient(m_pView->m_hWnd, &pos);
    Move(pos.x, pos.y);
  }

  pImpl->rotate(pImpl->theta);

  if (pImpl->theta != 0)
    Refresh();
}
