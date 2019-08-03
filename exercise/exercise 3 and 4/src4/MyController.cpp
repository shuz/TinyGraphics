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
#include "Utilities/Shape3D/SurfaceHiddenCuboid.h"
#include "Utilities/Shape3D/Shadow.h"

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

  double alphaXZ, alphaY;   // accumulated angle that already
                            // rotated in x and y direction

  double vxz, vy;            // velocity on each direction

  Matrix4D t_ry_rx_XZ,      // buffered matrices for rotation by X
           rx_ry_t_XZ;
  Matrix4D t_ry_rx_Y,       // buffered matrices for rotation by Y
           rx_ry_t_Y;

  bool buttonDown;

  CMyController_impl(CControllerBase *c) 
    : lastPos(0, 0), painter2d(c),
      painter(&painter2d) {
    resetWorld();
  }

  ~CMyController_impl() {
    // need not delete pivot since the dtor of the world will manage it
  }

  void resetWorld() {     // reset the world to its origin state
    alphaXZ = 0; alphaY = 0;
    vy = dtheta; vxz = 0;
    buttonDown = false;

    double x, y, z;
    double dx, dy, dz;
    x = 250; y = 180; z = 400;
    dx = 120; dy = 60; dz = 70;

    Point3D vertices[] = {                // vertices of the cuboid
      Point3D(x, y, z),
      Point3D(x+dx, y, z),
      Point3D(x+dx, y, z+dz),
      Point3D(x, y, z+dz),
      Point3D(x, y+dy, z),
      Point3D(x+dx, y+dy, z),
      Point3D(x+dx, y+dy, z+dz),
      Point3D(x, y+dy, z+dz),
    };

    Line3D axes[] = {                     // x, y, z
      Line3D(Point3D(0, 0, 0), Point3D(1000, 0, 0)),
      Line3D(Point3D(0, 0, 0), Point3D(0, 1000, 0)),
      Line3D(Point3D(0, 0, 0), Point3D(0, 0, 1000)),
    };

    Line3D pivotXZ(Point3D(x, y + dy/2, z),
                   Point3D(x + dx, y + dy/2, z + dz));
    Line3D pivotY(Point3D(x + dx/2, y, z + dz/2),
                  Point3D(x + dx/2, y + dy, z + dz/2));

    setupTransformMatrices(pivotXZ, t_ry_rx_XZ, rx_ry_t_XZ);
    setupTransformMatrices(pivotY, t_ry_rx_Y, rx_ry_t_Y);

    Matrix4D m;

    const double CABI_ALPHA = PI/6;
    Point3D d(-cos(CABI_ALPHA) / 2, -sin(CABI_ALPHA) / 2, -1);
    ::ParallelProject(100, d, m);         // project to the screen

    Matrix4D px, py, pz;
    ::Identity(px);  px[0][0] = 0;        // project to x=0;
    ::Identity(py);  py[1][1] = 0;        // project to y=0;
    ::Identity(pz);  pz[2][2] = 0;        // project to z=0;
    Point3D vx(-1, 0, 0),
            vy(0, -1, 0),
            vz(0, 0, -1);

    world.clear();
    world.setViewDirection(d);
    unsigned int objectColor = RGB(0, 0, 0xFF);
    Shape3D *theCuboid
      = new SurfaceHiddenCuboid(vertices, objectColor);

    world.add(theCuboid);
    
    unsigned int axesColor = RGB(0, 0, 0);
    world.addAbsolute(new SLine3D(axes[0], axesColor));
    world.addAbsolute(new SLine3D(axes[1], axesColor));
    world.addAbsolute(new SLine3D(axes[2], axesColor));

    unsigned int shadowColor = RGB(0xFF, 0, 0);
    world.addAbsolute(new Shadow(theCuboid, px, vx, shadowColor));
    world.addAbsolute(new Shadow(theCuboid, py, vy, shadowColor));
    world.addAbsolute(new Shadow(theCuboid, pz, vz, shadowColor));

    painter.setProjector(m);
  }

  void getRotateMatrixXZ(double dtheta, Matrix4D& m) {
    alphaXZ += dtheta;
    ::RotateY(alphaXZ, m);

    m = t_ry_rx_XZ * m * rx_ry_t_XZ;
  }

  void getRotateMatrixY(double dtheta, Matrix4D& m) {
    alphaY += dtheta;
    ::RotateY(alphaY, m);

    m = t_ry_rx_Y * m * rx_ry_t_Y;
  }

  static
  void setupTransformMatrices(Line3D& line,
                              Matrix4D& t_ry_rx,
                              Matrix4D& rx_ry_t) {
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
#define MYMENU_RESET  CGF_MENU_ID

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
	return "Shadow Controller";
}

void CMyController::Init()
{

	// 在这里插入所需的菜单项
	// Here insert customer menu
  InsertMenu(MYMENU_RESET, "&Reset");
  ::SetTimer(m_pView->m_hWnd, 0, 15, NULL);
}

void CMyController::OnCustomerMenu(unsigned int id)
{
	// 在这里响应菜单项，现在所做的是在画点与画线之间切换状态
	// Respond to menu action. here the task is switch state between draw pixel and line
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

void CMyController::OnLButtonUp(int x, int y) 
{
  pImpl->buttonDown = false;
}

void CMyController::OnMouseMove( int x, int y )
{}

void CMyController::OnTimer(unsigned int nIDEvent) {
  if (pImpl->buttonDown) {
    CPoint pos;
    ::GetCursorPos(&pos);
    ::ScreenToClient(m_pView->m_hWnd, &pos);
    pImpl->vy = (pos.x - pImpl->lastPos.x) * dtheta;
    pImpl->vxz = (pos.y - pImpl->lastPos.y) * dtheta;
    pImpl->lastPos.assign(pos.x, pos.y);
  }

  Matrix4D m1, m2;

  pImpl->getRotateMatrixY(pImpl->vy, m1);
  pImpl->getRotateMatrixXZ(pImpl->vxz, m2);
  pImpl->world.setWorldTransformer(m1 * m2);

  if (pImpl->vxz || pImpl->vy)
    Refresh();
}
