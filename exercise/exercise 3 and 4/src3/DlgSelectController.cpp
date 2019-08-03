// DlgSelectController.cpp : implementation file
//

#include "stdafx.h"
#include "CGFramework.h"
#include "DlgSelectController.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectController dialog


CDlgSelectController::CDlgSelectController(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgSelectController::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgSelectController)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDlgSelectController::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgSelectController)
	DDX_Control(pDX, IDC_CONTROLLERS, m_ctrlControllers);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgSelectController, CDialog)
	//{{AFX_MSG_MAP(CDlgSelectController)
	ON_LBN_DBLCLK(IDC_CONTROLLERS, OnDblclkControllers)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgSelectController message handlers

void CDlgSelectController::OnOK()
{
	if( m_ctrlControllers.GetCurSel() >= 0 )
	{
		m_pCurRuntimeClass = (CRuntimeClass*)m_ctrlControllers.GetItemDataPtr( m_ctrlControllers.GetCurSel() );
		CDialog::OnOK();
	}
	else
	{
		// do nothing
	}
}

void CDlgSelectController::OnCancel()
{

}

BOOL CDlgSelectController::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	int iIndex = 0;
	for( CRuntimeClassList::iterator it = g_RuntimeClassList.begin(); it != g_RuntimeClassList.end(); it++ )
	{
		m_ctrlControllers.InsertString( iIndex, (*it)->m_lpszClassName );
		m_ctrlControllers.SetItemDataPtr( iIndex, (*it) );
		iIndex++;
	}

	if( m_ctrlControllers.GetCount() == 0 )
	{
		MessageBox( "当前没有注册的控制器!", "错误", MB_OK );
		exit( 0 );
	}
	
	m_ctrlControllers.SetCurSel( 0 );
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgSelectController::OnDblclkControllers() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}
