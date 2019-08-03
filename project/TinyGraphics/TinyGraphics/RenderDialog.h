#pragma once

#include "Kernel/WorldViewer.h"

using namespace TinyGraphics;

// CRenderDialog dialog

class CRenderDialog : public CDialog
{
	DECLARE_DYNAMIC(CRenderDialog)

public:
	CRenderDialog(CWnd* pParent = NULL);   // standard constructor
  CRenderDialog(WorldViewer *viewer, int x, int y, int cx, int cy,
                CWnd* pParent = NULL);
	virtual ~CRenderDialog();

// Dialog Data
	enum { IDD = IDD_RENDER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  virtual BOOL OnInitDialog();
  afx_msg void OnPaint();
  afx_msg void OnTimer(UINT nIDEvent);
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);

  struct DrawInfo {
    HDC hDC;
    int width, height;
    WorldViewer *viewer;
    volatile bool *bDrawing;
  };
  DrawInfo info;
  volatile bool m_bDrawing;
  CWinThread *m_pThread;

  WorldViewer *m_viewer;
  int x, y, cx, cy;
  HDC m_screenBuffer;
protected:
  virtual void OnCancel();
};
