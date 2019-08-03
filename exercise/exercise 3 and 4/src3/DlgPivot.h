#if !defined(AFX_DLGPIVOT_H__B4BE4F60_7A64_4B39_BBCD_1C5A80A69C70__INCLUDED_)
#define AFX_DLGPIVOT_H__B4BE4F60_7A64_4B39_BBCD_1C5A80A69C70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgPivot.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgPivot dialog

struct Line3D;

class CDlgPivot : public CDialog
{
// Construction
public:
	CDlgPivot(Line3D& lastLine, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgPivot)
	enum { IDD = IDD_PIVOT };
	int		m_x0;
	int		m_x1;
	int		m_y0;
	int		m_y1;
	int		m_z0;
	int		m_z1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgPivot)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgPivot)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPIVOT_H__B4BE4F60_7A64_4B39_BBCD_1C5A80A69C70__INCLUDED_)
