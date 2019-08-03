 // CGFrameworkView.cpp : implementation of the CCGFrameworkView class
//

#include "stdafx.h"
#include "CGFramework.h"

#include "CGFrameworkDoc.h"
#include "CGFrameworkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkView

IMPLEMENT_DYNCREATE(CCGFrameworkView, CView)

BEGIN_MESSAGE_MAP(CCGFrameworkView, CView)
	//{{AFX_MSG_MAP(CCGFrameworkView)
	ON_WM_DESTROY()
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND_RANGE( CGF_MENU_ID, CGF_MENU_ID + 100, OnCustomerMenu )
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkView construction/destruction

CCGFrameworkView::CCGFrameworkView()
{
	// TODO: add construction code here
}

CCGFrameworkView::~CCGFrameworkView()
{
}

BOOL CCGFrameworkView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkView drawing

void CCGFrameworkView::OnDraw(CDC* pDC)
{
	//////////////////////////////////////////////////////////////////////////
	// 为消除产闪烁而添加的代码
	CDC MemDC;
	CBitmap MemBitmap;
	CRect rect;

	GetClientRect( &rect );
	MemDC.CreateCompatibleDC( pDC );
	MemBitmap.CreateCompatibleBitmap( pDC, rect.Width(), rect.Height() );
	CBitmap *pOldBitmap = MemDC.SelectObject( &MemBitmap );
	MemDC.FillRect( rect, &CBrush(RGB( 255, 255, 255 ) ) );	//先涂一遍背景色

	CCGFrameworkDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	m_pController->m_pDC = &MemDC;
	m_pController->OnPaint();
	m_pController->m_pDC = NULL;

	//////////////////////////////////////////////////////////////////////////
	// 为消除产闪烁而添加的代码
	pDC->BitBlt( 0, 0, rect.Width() ,rect.Height(), &MemDC, 0, 0, SRCCOPY );
	MemDC.SelectObject( pOldBitmap );
}

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkView printing

BOOL CCGFrameworkView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CCGFrameworkView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CCGFrameworkView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkView diagnostics

#ifdef _DEBUG
void CCGFrameworkView::AssertValid() const
{
	CView::AssertValid();
}

void CCGFrameworkView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGFrameworkDoc* CCGFrameworkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGFrameworkDoc)));
	return (CCGFrameworkDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkView message handlers

void CCGFrameworkView::OnInitialUpdate() 
{
	CView::OnInitialUpdate();
	
	// TODO: Add your specialized code here and/or call the base class
	if( g_RuntimeClassList.size() > 1 )
	{
		m_dlgSelectController.DoModal();
		m_pController = (CControllerBase*)m_dlgSelectController.m_pCurRuntimeClass->m_pfnCreateObject();
	}
	else
	{
		m_pController = (CControllerBase*)((*(g_RuntimeClassList.begin()))->m_pfnCreateObject());
	}
	ASSERT( m_pController != NULL );
	m_pController->m_pView = this;
	m_pController->Init();

	CString s = m_pController->GetName();
	GetDocument()->SetTitle( s );
}

void CCGFrameworkView::OnDestroy() 
{
	CView::OnDestroy();
	
	// TODO: Add your message handler code here
	delete m_pController;
}


void CCGFrameworkView::OnCustomerMenu(UINT id)
{
	m_pController->OnCustomerMenu( id );
}

void CCGFrameworkView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	m_pController->OnKeyPress( nChar );

	CView::OnChar(nChar, nRepCnt, nFlags);
}

void CCGFrameworkView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pController->OnLButtonDown( point.x, point.y );
	
	CView::OnLButtonDown(nFlags, point);
}

void CCGFrameworkView::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pController->OnRButtonDown( point.x, point.y );
	
	CView::OnRButtonDown(nFlags, point);
}

void CCGFrameworkView::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pController->OnLButtonUp( point.x, point.y );
	
	CView::OnLButtonUp(nFlags, point);
}

void CCGFrameworkView::OnRButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pController->OnRButtonUp( point.x, point.y );
	
	CView::OnRButtonUp(nFlags, point);
}

void CCGFrameworkView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	m_pController->OnMouseMove( point.x, point.y );
	
	CView::OnMouseMove(nFlags, point);
}

BOOL CCGFrameworkView::OnEraseBkgnd(CDC* pDC) 
{
	// TODO: Add your message handler code here and/or call default
	
	return TRUE;
}
