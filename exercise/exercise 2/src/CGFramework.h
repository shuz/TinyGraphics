// CGFramework.h : main header file for the CGFRAMEWORK application
//

#if !defined(AFX_CGFRAMEWORK_H__5190E75F_639A_4133_89A5_6001807CB3C6__INCLUDED_)
#define AFX_CGFRAMEWORK_H__5190E75F_639A_4133_89A5_6001807CB3C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

#include <vector>

#define CGF_MENU_ID		50000

typedef std::vector<CRuntimeClass*> CRuntimeClassList;

void	CGFInit();

BOOL	CGFRegisterController( CRuntimeClass* pControllerClass );

extern	CRuntimeClassList g_RuntimeClassList;
/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkApp:
// See CGFramework.cpp for the implementation of this class
//
class CCGFrameworkApp : public CWinApp
{
public:
	CCGFrameworkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGFrameworkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CCGFrameworkApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGFRAMEWORK_H__5190E75F_639A_4133_89A5_6001807CB3C6__INCLUDED_)
