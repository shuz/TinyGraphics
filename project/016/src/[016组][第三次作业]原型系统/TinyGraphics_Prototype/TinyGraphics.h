// TinyGraphics.h : main header file for the TINYGRAPHICS application
//

#if !defined(AFX_TINYGRAPHICS_H__11B22EA4_3234_4C0F_8EAF_A6AA55D74B06__INCLUDED_)
#define AFX_TINYGRAPHICS_H__11B22EA4_3234_4C0F_8EAF_A6AA55D74B06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsApp:
// See TinyGraphics.cpp for the implementation of this class
//

class CTinyGraphicsApp : public CWinApp
{
public:
	CTinyGraphicsApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTinyGraphicsApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CTinyGraphicsApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TINYGRAPHICS_H__11B22EA4_3234_4C0F_8EAF_A6AA55D74B06__INCLUDED_)
