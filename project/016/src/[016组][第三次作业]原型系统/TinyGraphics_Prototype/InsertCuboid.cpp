// InsertCuboid.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "InsertCuboid.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInsertCuboid dialog


CInsertCuboid::CInsertCuboid(CWnd* pParent /*=NULL*/)
	: CDialog(CInsertCuboid::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInsertCuboid)
	m_height = 1.0;
	m_length = 1.0;
	m_width = 1.0;
	m_x = 1.0;
	m_y = 1.0;
	m_z = 1.0;
	//}}AFX_DATA_INIT
}


void CInsertCuboid::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInsertCuboid)
	DDX_Text(pDX, IDC_EDIT_HEIGHT, m_height);
	DDX_Text(pDX, IDC_EDIT_LENGTH, m_length);
	DDX_Text(pDX, IDC_EDIT_WIDTH, m_width);
	DDX_Text(pDX, IDC_EDIT_X, m_x);
	DDX_Text(pDX, IDC_EDIT_Y, m_y);
	DDX_Text(pDX, IDC_EDIT_Z, m_z);
	//}}AFX_DATA_MAP

  if (m_length <=0 || m_width <=0 || m_height <= 0) {
    MessageBox("Error: Dimensions of the cuboid <= 0.", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
}


BEGIN_MESSAGE_MAP(CInsertCuboid, CDialog)
	//{{AFX_MSG_MAP(CInsertCuboid)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInsertCuboid message handlers
