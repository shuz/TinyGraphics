#if !defined(AFX_INSERTCUBOID_H__1B8B9912_7F52_4B72_A1D4_11EEEE5E4503__INCLUDED_)
#define AFX_INSERTCUBOID_H__1B8B9912_7F52_4B72_A1D4_11EEEE5E4503__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InsertCuboid.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInsertCuboid dialog

class CInsertCuboid : public CDialog
{
// Construction
public:
	CInsertCuboid(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInsertCuboid)
	enum { IDD = IDD_INSERT_CUBOID };
	double	m_height;
	double	m_length;
	double	m_width;
	double	m_x;
	double	m_y;
	double	m_z;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInsertCuboid)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInsertCuboid)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSERTCUBOID_H__1B8B9912_7F52_4B72_A1D4_11EEEE5E4503__INCLUDED_)
