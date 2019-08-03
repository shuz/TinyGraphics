// CGFrameworkView.h : interface of the CCGFrameworkView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGFRAMEWORKVIEW_H__600A8465_E496_42E1_B912_408734D95175__INCLUDED_)
#define AFX_CGFRAMEWORKVIEW_H__600A8465_E496_42E1_B912_408734D95175__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ControllerBase.h"
#include "DlgSelectController.h"	// Added by ClassView

class CCGFrameworkView : public CView
{
protected: // create from serialization only
	CCGFrameworkView();
	DECLARE_DYNCREATE(CCGFrameworkView)

// Attributes
public:
	CCGFrameworkDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGFrameworkView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OnCustomerMenu( UINT id );
	CControllerBase* m_pController;
	CDlgSelectController m_dlgSelectController;
	virtual ~CCGFrameworkView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGFrameworkView)
	afx_msg void OnDestroy();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in CGFrameworkView.cpp
inline CCGFrameworkDoc* CCGFrameworkView::GetDocument()
   { return (CCGFrameworkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGFRAMEWORKVIEW_H__600A8465_E496_42E1_B912_408734D95175__INCLUDED_)
