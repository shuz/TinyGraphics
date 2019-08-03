#if !defined(AFX_DLGSELECTCONTROLLER_H__4CA51FA7_9C93_4DA7_BDAB_A24F90ED43D8__INCLUDED_)
#define AFX_DLGSELECTCONTROLLER_H__4CA51FA7_9C93_4DA7_BDAB_A24F90ED43D8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSelectController.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectController dialog

class CDlgSelectController : public CDialog
{
// Construction
public:
	CRuntimeClass* m_pCurRuntimeClass;
	void OnCancel();
	void OnOK();
	CDlgSelectController(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSelectController)
	enum { IDD = IDD_SELECT_CONTROLLER };
	CListBox	m_ctrlControllers;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSelectController)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSelectController)
	virtual BOOL OnInitDialog();
	afx_msg void OnDblclkControllers();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSELECTCONTROLLER_H__4CA51FA7_9C93_4DA7_BDAB_A24F90ED43D8__INCLUDED_)
