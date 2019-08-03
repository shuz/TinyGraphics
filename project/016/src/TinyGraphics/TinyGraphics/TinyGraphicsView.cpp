// TinyGraphicsView.cpp : implementation of the CTinyGraphicsView class
//

#include "stdafx.h"
#include "TinyGraphics.h"

#include "CDCGraphics2D.h"

#include "CuboidAdaptor.h"
#include "ConeAdaptor.h"
#include "PlaneAdaptor.h"
#include "SphereAdaptor.h"
#include "CylinderAdaptor.h"
#include "PointLightAdaptor.h"
#include "ParallelLightAdaptor.h"

#include "RenderDialog.h"
#include "LightManagerDialog.h"
#include "ObjectManagerDialog.h"
#include "ShadingOptionsDialog.h"

#include "Kernel/LineFrameWorldViewer.h"
#include "Kernel/GouroudShadingWorldViewer.h"
#include "Kernel/RayTraceWorldViewer.h"
#include "Kernel/Primitive2D.h"
#include "Kernel/Position.h"
#include "Kernel/Ray.h"

#include "TinyGraphicsDoc.h"
#include "TinyGraphicsView.h"

using namespace TinyGraphics;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTinyGraphicsView

IMPLEMENT_DYNCREATE(CTinyGraphicsView, CView)

BEGIN_MESSAGE_MAP(CTinyGraphicsView, CView)
  ON_WM_ERASEBKGND()
  ON_WM_SIZE()
  ON_COMMAND(ID_VIEW_LINEFRAME, OnViewLineframe)
  ON_COMMAND(ID_VIEW_GOUROUDSHADING, OnViewGouroudshading)
  ON_COMMAND(ID_INSERT_CONE, OnInsertCone)
  ON_COMMAND(ID_INSERT_CUBOID, OnInsertCuboid)
  ON_COMMAND(ID_INSERT_CYLINDER, OnInsertCylinder)
  ON_COMMAND(ID_INSERT_PARALLELLIGHT, OnInsertParallellight)
  ON_COMMAND(ID_INSERT_PLANE, OnInsertPlane)
  ON_COMMAND(ID_INSERT_POINTLIGHT, OnInsertPointlight)
  ON_COMMAND(ID_INSERT_SPHERE, OnInsertSphere)
  ON_COMMAND(ID_VIEW_RENDER, OnViewRender)
  ON_WM_MOUSEMOVE()
  ON_WM_MOUSEWHEEL()
  ON_WM_LBUTTONDBLCLK()
  ON_WM_LBUTTONDOWN()
  ON_WM_RBUTTONDOWN()
  ON_WM_KEYDOWN()
  ON_COMMAND(ID_OBJECTS_DELETE, OnObjectsDelete)
  ON_UPDATE_COMMAND_UI(ID_OBJECTS_DELETE, OnUpdateUIObjects)
  ON_UPDATE_COMMAND_UI(ID_OBJECTS_EDIT, OnUpdateUIObjects)
  ON_COMMAND(ID_OBJECTS_EDIT, OnObjectsEdit)
  ON_COMMAND(ID_VIEW_X, OnViewXY)
  ON_COMMAND(ID_VIEW_Y, OnViewYZ)
  ON_COMMAND(ID_VIEW_Z, OnViewZX)
  ON_COMMAND(ID_VIEW_CAMERASETUP, OnViewCameraSetup)
  ON_COMMAND(ID_OBJECT_WORLDSETUP, OnObjectWorldsetup)
  ON_COMMAND(ID_LIGHT_LIGHTMANAGER, OnLightLightmanager)
  ON_COMMAND(ID_OBJECTS_OBJECTMANAGER, OnObjectsObjectmanager)
  ON_COMMAND(ID_VIEW_OPTIONS, OnViewOptions)
END_MESSAGE_MAP()

// CTinyGraphicsView construction/destruction

CTinyGraphicsView::CTinyGraphicsView()
{
	// TODO: add construction code here
  m_worldViewer = 0;
  m_paCamera = 0;
  m_peCamera = 0;
  ResetCamera();
  m_needUpdate = true;
  m_selectedAdaptor = 0;
}

CTinyGraphicsView::~CTinyGraphicsView()
{
  delete m_worldViewer;
  delete m_paCamera;
  delete m_peCamera;
}

BOOL CTinyGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTinyGraphicsView drawing

void CTinyGraphicsView::OnDraw(CDC* pDC)
{
	CTinyGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	// TODO: add draw code for native data here
  CRect rect;
  GetClientRect(&rect);
  int cx = rect.right, cy = rect.bottom;
  if (cx <= 0 || cy <= 0) return;

  int lx, ly;
  Camera *camera = pDoc->m_pCamera->GetCamera();
  camera->get_vpw_resolution(lx, ly);

  if (cx != lx || cy != ly) {
    double ratio = double(cy) / double(cx);
    camera->adjust_aspect_ratio(ratio);
    camera->set_vpw_resolution(cx, cy);

    CreateBuffer(pDC, cx, cy);
    m_needUpdate = true;
  }

  if (m_needUpdate) DrawWorld(&m_screenBuffer, cx, cy);

  pDC->BitBlt(0, 0, cx, cy, &m_screenBuffer, 0, 0, SRCCOPY);
}

void CTinyGraphicsView::CreateBuffer(CDC *pDC, int width, int height)
{
  m_screenBuffer.DeleteDC();
  m_screenBuffer.CreateCompatibleDC(pDC);
  CBitmap bitmap;
  bitmap.CreateCompatibleBitmap(pDC, width, height);

  m_screenBuffer.SelectObject(bitmap);
}

void CTinyGraphicsView::DrawWorld(CDC *pDC, int width, int height)
{
  CDCGraphics2D g2d(pDC);
  g2d.set_window_ext(width, height);

  m_worldViewer->draw(&g2d);
  m_needUpdate = false;
}

void CTinyGraphicsView::Refresh()
{
  m_needUpdate = true;
  Invalidate(FALSE);
}

void CTinyGraphicsView::ResetCamera()
{
  m_paCamera = new ParallelCamera();
  m_peCamera = new PerspectiveCamera();
  Position pos(Vector3D(0, 0, 5));
  m_paCamera->set_position(pos);
  m_peCamera->set_position(pos);

  m_paCamera->set_vpw(5, 5);
}

// CTinyGraphicsView diagnostics

#ifdef _DEBUG
void CTinyGraphicsView::AssertValid() const
{
	CView::AssertValid();
}

void CTinyGraphicsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTinyGraphicsDoc* CTinyGraphicsView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTinyGraphicsDoc)));
	return (CTinyGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG


// CTinyGraphicsView message handlers

BOOL CTinyGraphicsView::OnEraseBkgnd(CDC* pDC)
{
  // TODO: Add your message handler code here and/or call default

  // return CView::OnEraseBkgnd(pDC);

  return TRUE;    // no erase
}

void CTinyGraphicsView::OnInitialUpdate()
{
  CView::OnInitialUpdate();

  // TODO: Add your specialized code here and/or call the base class
  delete m_worldViewer;
  delete m_paCamera;
  delete m_peCamera;

  CTinyGraphicsDoc* pDoc = GetDocument();
  if (pDoc->m_pCamera == 0) {
    ResetCamera();
    pDoc->m_pCamera = new CCameraAdaptor(m_paCamera, m_peCamera, false);
    PointLight *light = new PointLight();
    light->location.assign(5, 5, 5);
    pDoc->AddLight(new CPointLightAdaptor(light, "Default Light"));
    pDoc->m_world->set_ambient_color(ColorRGB(0.1, 0.1, 0.1));
  } else {
    m_paCamera = pDoc->m_pCamera->parallelCamera;
    m_peCamera = pDoc->m_pCamera->perspectiveCamera;
  }

  m_worldViewer = new GouroudShadingWorldViewer(pDoc->m_world, pDoc->m_pCamera->GetCamera());
  m_currentViewerIndex = ID_VIEW_GOUROUDSHADING;
}

void CTinyGraphicsView::OnViewLineframe()
{
  // TODO: Add your command handler code here
  if (m_currentViewerIndex != ID_VIEW_LINEFRAME) {
    CTinyGraphicsDoc* pDoc = GetDocument();

    WorldViewer *new_viewer
      = new LineFrameWorldViewer(pDoc->m_world, pDoc->m_pCamera->GetCamera());
    delete m_worldViewer;
    m_worldViewer = new_viewer;

    CMenu *pMenu = GetParent()->GetMenu();
    pMenu->CheckMenuItem(m_currentViewerIndex, MF_UNCHECKED);
    pMenu->CheckMenuItem(ID_VIEW_LINEFRAME, MF_CHECKED);
    m_currentViewerIndex = ID_VIEW_LINEFRAME;
    Refresh();
  }
}

void CTinyGraphicsView::OnViewGouroudshading()
{
  // TODO: Add your command handler code here
  if (m_currentViewerIndex != ID_VIEW_GOUROUDSHADING) {
    CTinyGraphicsDoc* pDoc = GetDocument();

    WorldViewer *new_viewer
      = new GouroudShadingWorldViewer(pDoc->m_world, pDoc->m_pCamera->GetCamera(),
                                      pDoc->m_useMaterial);
    delete m_worldViewer;
    m_worldViewer = new_viewer;

    CMenu *pMenu = GetParent()->GetMenu();
    pMenu->CheckMenuItem(m_currentViewerIndex, MF_UNCHECKED);
    pMenu->CheckMenuItem(ID_VIEW_GOUROUDSHADING, MF_CHECKED);
    m_currentViewerIndex = ID_VIEW_GOUROUDSHADING;
    Refresh();
  }
}

void CTinyGraphicsView::OnViewRender()
{
  // TODO: Add your command handler code here

  CTinyGraphicsDoc* pDoc = GetDocument();

  RayTraceWorldViewer viewer(pDoc->m_world, pDoc->m_pCamera->GetCamera(),
                             pDoc->m_reflectDepth, pDoc->m_refractDepth);

  CRect rect;
  GetClientRect(&rect);
  ClientToScreen(&rect);

  CRenderDialog dialog(&viewer, rect.left, rect.top, rect.Width(), rect.Height());
  dialog.DoModal();
}

void CTinyGraphicsView::OnInsertPointlight()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();

  PointLight *light = new PointLight();
  light->location.assign(5, 5, 5);
  CString name;
  name.Format("Point Light %d", pDoc->GetNextObjNum());
  CLightAdaptor *adaptor = new CPointLightAdaptor(light, name);
  pDoc->AddLight(adaptor);
  if (adaptor->EditObject()) {
    Refresh();
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveLight(adaptor);
  }
}

void CTinyGraphicsView::OnInsertParallellight()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();

  ParallelLight *light = new ParallelLight();
  light->location.assign(5, 5, 5);
  CString name;
  name.Format("Parallel Light %d", pDoc->GetNextObjNum());
  CLightAdaptor *adaptor = new CParallelLightAdaptor(light, name);
  pDoc->AddLight(adaptor);
  if (adaptor->EditObject()) {
    Refresh();
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveLight(adaptor);
  }
}

void CTinyGraphicsView::OnInsertCone()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();

  CString name;
  name.Format("Cone %d", pDoc->GetNextObjNum());
  CObject3DAdaptor *adaptor = new CConeAdaptor(new Cone(), name);
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    Refresh();
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CTinyGraphicsView::OnInsertCuboid()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();

  CString name;
  name.Format("Cuboid %d", pDoc->GetNextObjNum());
  CObject3DAdaptor *adaptor = new CCuboidAdaptor(new Cuboid(), name);
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    Refresh();
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CTinyGraphicsView::OnInsertCylinder()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();

  CString name;
  name.Format("Cylinder %d", pDoc->GetNextObjNum());
  CObject3DAdaptor *adaptor = new CCylinderAdaptor(new Cylinder(), name);
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    Refresh();
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CTinyGraphicsView::OnInsertPlane()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();

  CString name;
  name.Format("Plane %d", pDoc->GetNextObjNum());
  CObject3DAdaptor *adaptor = new CPlaneAdaptor(new Plane(), name);
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    Refresh();
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CTinyGraphicsView::OnInsertSphere()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();
  
  CString name;
  name.Format("Sphere %d", pDoc->GetNextObjNum());
  CObject3DAdaptor *adaptor = new CSphereAdaptor(new Sphere(), name);
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    Refresh();
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}


void CTinyGraphicsView::OnMouseMove(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default
  CRect rect;
  GetClientRect(&rect);

  const double SCALE_FACTOR = 100.0;
  double dx = (point.x - m_lastPos.x) / SCALE_FACTOR;
  double dy = (point.y - m_lastPos.y) / SCALE_FACTOR;
  real screen_width = rect.right / SCALE_FACTOR;
  real screen_height = rect.bottom / SCALE_FACTOR;

  CTinyGraphicsDoc *pDoc = GetDocument();
  Camera *camera = pDoc->m_pCamera->GetCamera();

  const Vector3D& y_axis = camera->get_up_vector();
  const Vector3D& z_axis = camera->get_front_vector();
  Vector3D x_axis = y_axis.cross_product(z_axis);

  bool shift = ((nFlags & MK_SHIFT) != 0);
  if (nFlags & MK_LBUTTON) {              // rotate
    if (nFlags & MK_CONTROL) {            // rotate y z axes
      if (m_selectedAdaptor == 0) {
        Position pos = camera->get_position();
        pos.rotate(y_axis, dx * TG_2PI / screen_width);
        pos.rotate(z_axis, dy * TG_2PI / screen_height);
        camera->set_position(pos);
      } else {
        if (shift) {                      // rotate object
          Object3D *obj = m_selectedAdaptor->GetObject3D();
          obj->rotate(y_axis, dx * TG_2PI / screen_width);
          obj->rotate(z_axis, dy * TG_2PI / screen_height);
        } else {                          // rotate camera
          Object3D *obj = m_selectedAdaptor->GetObject3D();
          Position pos =  camera->get_position();
          pos.rotate(obj->get_location(), y_axis, -dx * TG_2PI / screen_width);
          pos.rotate(obj->get_location(), z_axis, -dy * TG_2PI / screen_height);
          camera->set_position(pos);
        }
      }
    }
    else
    {                               // rotate x y axes
      if (m_selectedAdaptor == 0) {
        Position pos = camera->get_position();
        pos.rotate(y_axis, dx * TG_2PI / screen_width);
        pos.rotate(x_axis, dy * TG_2PI / screen_height);
        camera->set_position(pos);
      } else {
        if (shift) {                // rotate object
          Object3D *obj = m_selectedAdaptor->GetObject3D();
          obj->rotate(y_axis, dx * TG_2PI / screen_width);
          obj->rotate(x_axis, dy * TG_2PI / screen_height);
        } else {
          Object3D *obj = m_selectedAdaptor->GetObject3D();
          Position pos =  camera->get_position();
          pos.rotate(obj->get_location(), y_axis, -dx * TG_2PI / screen_width);
          pos.rotate(obj->get_location(), x_axis, -dy * TG_2PI / screen_height);
          camera->set_position(pos);
        }
      }
    }
    Refresh();
    m_lastPos = point;
  } else
  if (nFlags & MK_RBUTTON) {              // translate
    if (nFlags & MK_CONTROL) {            // translate in x-z plane
      Vector3D vec(dx, 0, dy);
      vec.transform(camera->get_position().get_transformer_inv());
      if (m_selectedAdaptor == 0) {
        camera->translate(vec);
      } else {
        Object3D *obj = m_selectedAdaptor->GetObject3D();
        obj->translate(vec);
      }
    } else {                              // translate in x-y plane
      Vector3D vec(dx, -dy, 0);
      vec.transform(camera->get_position().get_transformer_inv());
      if (m_selectedAdaptor == 0) {
        camera->translate(vec);
      } else {
        Object3D *obj = m_selectedAdaptor->GetObject3D();
        obj->translate(vec);
      }
    }
    Refresh();
    m_lastPos = point;
  }

  CView::OnMouseMove(nFlags, point);
}

BOOL CTinyGraphicsView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
  // TODO: Add your message handler code here and/or call default

  UpdateSelection(pt);

  CTinyGraphicsDoc *pDoc = GetDocument();
  Camera *camera = pDoc->m_pCamera->GetCamera();

  real scale_factor = pow(0.9, zDelta / WHEEL_DELTA);
  camera->scale(scale_factor);
  Refresh();

  return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CTinyGraphicsView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default

  UpdateSelection(point);
  OnObjectsEdit();

  CView::OnLButtonDblClk(nFlags, point);
}

void CTinyGraphicsView::OnLButtonDown(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default

  UpdateSelection(point);
  m_lastPos = point;

  CView::OnLButtonDown(nFlags, point);
}

void CTinyGraphicsView::OnRButtonDown(UINT nFlags, CPoint point)
{
  // TODO: Add your message handler code here and/or call default

  UpdateSelection(point);
  m_lastPos = point;

  CView::OnRButtonDown(nFlags, point);
}

void CTinyGraphicsView::UpdateSelection(CPoint point) {
  CTinyGraphicsDoc* pDoc = GetDocument();

  CRect rect;
  GetClientRect(&rect);
  Camera *camera = pDoc->m_pCamera->GetCamera();

  Ray ray = camera->get_ray(point.x, rect.bottom - point.y);
  real hit_point;  Vector3D normal;  int plane_idx;
  Object3D *obj = pDoc->m_world->intersect(ray, hit_point, normal, plane_idx);
  if (obj != 0) {
    CObject3DAdaptor *adaptor = pDoc->LookupAdaptor(obj);
    m_selectedAdaptor = adaptor;
  } else {
    m_selectedAdaptor = 0;
  }
}

void CTinyGraphicsView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
  // TODO: Add your message handler code here and/or call default

  if (nChar == VK_DELETE && m_selectedAdaptor != 0) {
    OnObjectsDelete();
  }

  CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CTinyGraphicsView::OnObjectsDelete()
{
  // TODO: Add your command handler code here

  if (m_selectedAdaptor != 0) {
    CTinyGraphicsDoc* pDoc = GetDocument();
    pDoc->RemoveObject(m_selectedAdaptor);
    Refresh();
  }
}

void CTinyGraphicsView::OnUpdateUIObjects(CCmdUI *pCmdUI)
{
  // TODO: Add your command update UI handler code here

  pCmdUI->Enable(m_selectedAdaptor != 0);
}

void CTinyGraphicsView::OnObjectsEdit()
{
  // TODO: Add your command handler code here

  if (m_selectedAdaptor != 0) {
    if (m_selectedAdaptor->EditObject()) {
      GetDocument()->SetModifiedFlag();
      Refresh();
    }
  }
}

void CTinyGraphicsView::OnViewXY()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc *pDoc = GetDocument();
  Camera *camera = pDoc->m_pCamera->GetCamera();

  Point3D loc = camera->get_location();
  real dist = loc.to_vec3d().norm();

  Position pos(Point3D(0, 0, dist));
  camera->set_position(pos);
  camera->set_project_direction(Vector3D::Z_AXIS);
  Refresh();
}

void CTinyGraphicsView::OnViewYZ()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc *pDoc = GetDocument();
  Camera *camera = pDoc->m_pCamera->GetCamera();

  Point3D loc = camera->get_location();
  real dist = loc.to_vec3d().norm();

  Position pos(Point3D(dist, 0, 0), Vector3D::X_AXIS, Vector3D::Y_AXIS);
  camera->set_position(pos);
  camera->set_project_direction(Vector3D::Z_AXIS);
  Refresh();
}

void CTinyGraphicsView::OnViewZX()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc *pDoc = GetDocument();
  Camera *camera = pDoc->m_pCamera->GetCamera();

  Point3D loc = camera->get_location();
  real dist = loc.to_vec3d().norm();

  Position pos(Point3D(0, dist, 0), Vector3D::Y_AXIS, Vector3D::Z_AXIS);
  camera->set_position(pos);
  camera->set_project_direction(Vector3D::Z_AXIS);
  Refresh();
}

void CTinyGraphicsView::OnViewCameraSetup()
{
  // TODO: Add your command handler code here

  CTinyGraphicsDoc* pDoc = GetDocument();
  if (pDoc->m_pCamera->EditObject()) {
    m_paCamera = pDoc->m_pCamera->parallelCamera;
    m_peCamera = pDoc->m_pCamera->perspectiveCamera;

    m_worldViewer->set_camera(pDoc->m_pCamera->GetCamera());
    Refresh();
  }
}

void CTinyGraphicsView::OnObjectWorldsetup()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc* pDoc = GetDocument();
  if (pDoc->m_worldAdaptor.EditObject()) {
    pDoc->SetModifiedFlag();
    Refresh();
  }
}

void CTinyGraphicsView::OnLightLightmanager()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc *pDoc = GetDocument();
  CLightManagerDialog dialog(pDoc);
  dialog.DoModal();
  Refresh();
}

void CTinyGraphicsView::OnObjectsObjectmanager()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc *pDoc = GetDocument();
  CObjectManagerDialog dialog(pDoc);
  dialog.DoModal();
  Refresh();
}

void CTinyGraphicsView::OnViewOptions()
{
  // TODO: Add your command handler code here
  CTinyGraphicsDoc *pDoc = GetDocument();
  CShadingOptionsDialog dialog(pDoc->m_reflectDepth, pDoc->m_refractDepth, pDoc->m_useMaterial);
  if (IDOK == dialog.DoModal()) {
    pDoc->m_reflectDepth = dialog.m_reflectDepth;
    pDoc->m_refractDepth = dialog.m_refractDepth;
    pDoc->m_useMaterial = dialog.m_useMaterial;
    if (m_currentViewerIndex == ID_VIEW_GOUROUDSHADING) {
      WorldViewer *new_viewer
        = new GouroudShadingWorldViewer(pDoc->m_world, pDoc->m_pCamera->GetCamera(),
                                        pDoc->m_useMaterial);
      delete m_worldViewer;
      m_worldViewer = new_viewer;
      Refresh();
    }
    pDoc->SetModifiedFlag();
  }
}
