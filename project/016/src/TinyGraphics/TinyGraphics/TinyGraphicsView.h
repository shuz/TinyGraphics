// TinyGraphicsView.h : interface of the CTinyGraphicsView class
//

#pragma once

#include "Kernel/ParallelCamera.h"
#include "Kernel/PerspectiveCamera.h"
#include "Kernel/WorldViewer.h"

using namespace TinyGraphics;

class Object3DAdaptor;

class CTinyGraphicsView : public CView
{
protected: // create from serialization only
	CTinyGraphicsView();
	DECLARE_DYNCREATE(CTinyGraphicsView)

// Attributes
public:
	CTinyGraphicsDoc* GetDocument() const;
  WorldViewer *m_worldViewer;
  ParallelCamera *m_paCamera;
  PerspectiveCamera *m_peCamera;

private:
  CDC m_screenBuffer;
  UINT m_currentViewerIndex;
  bool m_needUpdate;
  CObject3DAdaptor *m_selectedAdaptor;
  CPoint m_lastPos;

// Operations
public:
  void CreateBuffer(CDC *pDC, int width, int height);
  void DrawWorld(CDC *pDC, int width, int height);
  void Refresh();

  void ResetCamera();
  void UpdateSelection(CPoint point);

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
  virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CTinyGraphicsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
  afx_msg BOOL OnEraseBkgnd(CDC* pDC);
  virtual void OnInitialUpdate();
  afx_msg void OnViewLineframe();
  afx_msg void OnViewGouroudshading();
  afx_msg void OnInsertCone();
  afx_msg void OnInsertCuboid();
  afx_msg void OnInsertCylinder();
  afx_msg void OnInsertParallellight();
  afx_msg void OnInsertPlane();
  afx_msg void OnInsertPointlight();
  afx_msg void OnInsertSphere();
  afx_msg void OnViewRender();
  afx_msg void OnMouseMove(UINT nFlags, CPoint point);
  afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
  afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
  afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
  afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  afx_msg void OnObjectsDelete();
  afx_msg void OnUpdateUIObjects(CCmdUI *pCmdUI);
  afx_msg void OnObjectsEdit();
  afx_msg void OnViewXY();
  afx_msg void OnViewYZ();
  afx_msg void OnViewZX();
  afx_msg void OnViewCameraSetup();
  afx_msg void OnObjectWorldsetup();
  afx_msg void OnLightLightmanager();
  afx_msg void OnObjectsObjectmanager();
  afx_msg void OnViewOptions();
};

#ifndef _DEBUG  // debug version in TinyGraphicsView.cpp
inline CTinyGraphicsDoc* CTinyGraphicsView::GetDocument() const
   { return reinterpret_cast<CTinyGraphicsDoc*>(m_pDocument); }
#endif
