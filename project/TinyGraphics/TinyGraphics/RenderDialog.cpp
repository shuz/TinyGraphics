// RenderDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "CDCGraphics2D.h"
#include "RenderDialog.h"


// CRenderDialog dialog

IMPLEMENT_DYNAMIC(CRenderDialog, CDialog)
CRenderDialog::CRenderDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRenderDialog::IDD, pParent)
{
}

CRenderDialog::CRenderDialog(WorldViewer *viewer, int x, int y,
                             int cx, int cy, CWnd* pParent /*= NULL*/)
	: CDialog(CRenderDialog::IDD, pParent), m_viewer(viewer),
    x(x), y(y), cx(cx), cy(cy)
{
}

CRenderDialog::~CRenderDialog()
{
}

void CRenderDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRenderDialog, CDialog)
  ON_WM_PAINT()
  ON_WM_TIMER()
  ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// Work thread function

static UINT ThreadFunc(LPVOID pParam)
{
  CRenderDialog::DrawInfo *info = (CRenderDialog::DrawInfo *)pParam;
  CDC dc;
  dc.Attach(info->hDC);
  CDCGraphics2D g2d(&dc);
  g2d.set_window_ext(info->width, info->height);

  info->viewer->draw(&g2d);
  dc.Detach();
  *info->bDrawing = false;
  return 0;
}

// CRenderDialog message handlers

BOOL CRenderDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  SetWindowPos(&CWnd::wndTop, x - 3, y - 10, cx + 6, cy + 25, SWP_SHOWWINDOW);

  CClientDC dc(this);
  CDC screenBuffer;
  screenBuffer.CreateCompatibleDC(&dc);
  m_screenBuffer = screenBuffer.m_hDC;
  CBitmap bitmap;
  bitmap.CreateCompatibleBitmap(&dc, cx, cy);
  screenBuffer.SelectObject(bitmap);
  CRect rect(0, 0, cx, cy);
  screenBuffer.FillRect(rect, &CBrush(RGB(0, 0, 0)));
  dc.FillRect(rect, &CBrush(RGB(0, 0, 0)));
  SetTimer(0, 100, NULL);
  screenBuffer.Detach();

  info.hDC = m_screenBuffer;
  info.width = cx;
  info.height = cy;
  info.viewer = m_viewer;
  info.bDrawing = &m_bDrawing;
  m_pThread = AfxBeginThread(ThreadFunc, &info, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
  m_pThread->m_bAutoDelete = FALSE;
  m_pThread->ResumeThread();

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CRenderDialog::OnPaint()
{
  CPaintDC dc(this); // device context for painting
  // TODO: Add your message handler code here
  // Do not call CDialog::OnPaint() for painting messages
  CDC screenBuffer;
  screenBuffer.Attach(m_screenBuffer);
  dc.BitBlt(0, 0, cx, cy, &screenBuffer, 0, 0, SRCCOPY);
  screenBuffer.Detach();
}

void CRenderDialog::OnTimer(UINT nIDEvent)
{
  // TODO: Add your message handler code here and/or call default
  Invalidate(FALSE);

  if (!m_bDrawing) {
    KillTimer(0);
    delete m_pThread;
  }

  CDialog::OnTimer(nIDEvent);
}

BOOL CRenderDialog::OnEraseBkgnd(CDC* pDC)
{
  // TODO: Add your message handler code here and/or call default

  // return CDialog::OnEraseBkgnd(pDC);
  return TRUE;
}

void CRenderDialog::OnCancel()
{
  // TODO: Add your specialized code here and/or call the base class

  if (m_bDrawing) {
    return;
  }

  CDialog::OnCancel();
}
