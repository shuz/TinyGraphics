// TinyGraphics.h : main header file for the TinyGraphics application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// CTinyGraphicsApp:
// See TinyGraphics.cpp for the implementation of this class
//

class CTinyGraphicsApp : public CWinApp
{
public:
	CTinyGraphicsApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTinyGraphicsApp theApp;