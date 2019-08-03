// ShadingOptionsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "ShadingOptionsDialog.h"


// CShadingOptionsDialog dialog

IMPLEMENT_DYNAMIC(CShadingOptionsDialog, CDialog)
CShadingOptionsDialog::CShadingOptionsDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CShadingOptionsDialog::IDD, pParent)
  , m_reflectDepth(0)
  , m_refractDepth(0)
  , m_useMaterial(false)
{
}

CShadingOptionsDialog::CShadingOptionsDialog(int rld, int rrd, bool um,
                                             CWnd* pParent /*=NULL*/)
	: CDialog(CShadingOptionsDialog::IDD, pParent)
  , m_reflectDepth(rld)
  , m_refractDepth(rrd)
  , m_useMaterial(um)
{
}

CShadingOptionsDialog::~CShadingOptionsDialog()
{
}

void CShadingOptionsDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_EDIT_SPEC_DEPTH, m_reflectDepth);
  DDX_Text(pDX, IDC_EDIT_TRANS_DEPTH, m_refractDepth);
  int i_useMaterial = m_useMaterial;
  DDX_Check(pDX, IDC_CHK_USE_MATERIAL, i_useMaterial);
  m_useMaterial = (i_useMaterial != 0);
}


BEGIN_MESSAGE_MAP(CShadingOptionsDialog, CDialog)
END_MESSAGE_MAP()


// CShadingOptionsDialog message handlers
