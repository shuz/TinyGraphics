// TinyGraphicsView.cpp : implementation of the CTinyGraphicsView class
//

#include "stdafx.h"
#include "TinyGraphics.h"

#include "TinyGraphicsDoc.h"
#include "TinyGraphicsView.h"

#include "CDCGraphics2D.h"
#include "ModifyPerspectiveCamera.h"
#include "Kernel/PerspectiveCamera.h"
#include "Kernel/Object3D.h"
#include "Kernel/ViewingGraphics3D.h"
#include "Kernel/World3D.h"
#include "Kernel/Primitive3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsView

IMPLEMENT_DYNCREATE(CTinyGraphicsView, CView)

BEGIN_MESSAGE_MAP(CTinyGraphicsView, CView)
	//{{AFX_MSG_MAP(CTinyGraphicsView)
	ON_COMMAND(ID_MENU_CAMERA_ADJUST, OnMenuCameraAdjust)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsView construction/destruction

CTinyGraphicsView::CTinyGraphicsView()
{
	// TODO: add construction code here

  camera = new PerspectiveCamera;
  camera->set_vpw(-4, 4, -3, 3);
  camera->set_cop(Point3D(0, 0, 2));
}

CTinyGraphicsView::~CTinyGraphicsView()
{
}

BOOL CTinyGraphicsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsView drawing

void CTinyGraphicsView::OnDraw(CDC* pDC)
{
	CTinyGraphicsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

  CRect rect;
  GetClientRect (&rect);
  pDC->SetMapMode (MM_ANISOTROPIC);
  pDC->SetWindowExt (800, -600);
  pDC->SetViewportExt (rect.Width (), rect.Height ());
  pDC->SetViewportOrg (rect.Width () / 2, rect.Height () / 2);

  CDCGraphics2D g2d(pDC);
  g2d.set_window_ext(800, 600);
  ViewingGraphics3D graphics(camera, &g2d);
  pDoc->world->draw(&graphics);
}

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsView printing

BOOL CTinyGraphicsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTinyGraphicsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTinyGraphicsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
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

CTinyGraphicsDoc* CTinyGraphicsView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTinyGraphicsDoc)));
	return (CTinyGraphicsDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsView message handlers

void CTinyGraphicsView::OnMenuCameraAdjust() 
{
	// TODO: Add your command handler code here
	CModifyPerspectiveCamera dialog(camera);
  int retVal = dialog.DoModal();
  Invalidate();
}
