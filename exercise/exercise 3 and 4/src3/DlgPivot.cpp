// DlgPivot.cpp : implementation file
//

#include "stdafx.h"
#include "CGFramework.h"
#include "DlgPivot.h"
#include "Utilities/Primitive3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgPivot dialog


CDlgPivot::CDlgPivot(Line3D& lastLine, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgPivot::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgPivot)
	m_x0 = lastLine.begin.x();
	m_x1 = lastLine.end.x();
	m_y0 = lastLine.begin.y();
	m_y1 = lastLine.end.y();
	m_z0 = lastLine.begin.z();
	m_z1 = lastLine.end.z();
	//}}AFX_DATA_INIT
}


void CDlgPivot::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgPivot)
	DDX_Text(pDX, IDC_EDIT_X0, m_x0);
	DDX_Text(pDX, IDC_EDIT_X1, m_x1);
	DDX_Text(pDX, IDC_EDIT_Y0, m_y0);
	DDX_Text(pDX, IDC_EDIT_Y1, m_y1);
	DDX_Text(pDX, IDC_EDIT_Z0, m_z0);
	DDX_Text(pDX, IDC_EDIT_Z1, m_z1);
	//}}AFX_DATA_MAP

  if (m_x0 == m_x1 && m_y0 == m_y1 && m_z0 == m_z1) {
    MessageBox("Two Points can't be equal.", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
}


BEGIN_MESSAGE_MAP(CDlgPivot, CDialog)
	//{{AFX_MSG_MAP(CDlgPivot)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgPivot message handlers
