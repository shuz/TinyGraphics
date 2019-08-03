// EditWorldDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "EditWorldDialog.h"
#include "Utilities.h"
#include ".\editworlddialog.h"

// CEditWorldDialog dialog

IMPLEMENT_DYNAMIC(CEditWorldDialog, CDialog)
CEditWorldDialog::CEditWorldDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditWorldDialog::IDD, pParent)
{
}

CEditWorldDialog::CEditWorldDialog(const ColorRGB& ac, const ColorRGB& bc,
                                   real ri, int non, CWnd* pParent /*= NULL*/)
	: CDialog(CEditWorldDialog::IDD, pParent)
{
  ambientColor = ac;
  backgroundColor = bc;
  refract_idx = ri;
  next_obj_num = non;
}

CEditWorldDialog::~CEditWorldDialog()
{
}

void CEditWorldDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_EDIT_REFRACT_IDX, refract_idx);
  DDX_Text(pDX, IDC_EDIT_NEXT_OBJNUM, next_obj_num);
  DDV_MinMaxDouble(pDX, refract_idx,  0, DBL_MAX);
}


BEGIN_MESSAGE_MAP(CEditWorldDialog, CDialog)
  ON_BN_CLICKED(IDC_EDIT_BTN_AMBIENT_COLOR, OnBnClickedEditBtnAmbientColor)
  ON_BN_CLICKED(IDC_EDIT_BTN_BKGND_COLOR, OnBnClickedEditBtnBkgndColor)
END_MESSAGE_MAP()


// CEditWorldDialog message handlers

void CEditWorldDialog::OnBnClickedEditBtnAmbientColor()
{
  // TODO: Add your control notification handler code here
	CColorDialog dialog(convert_color(ambientColor), CC_FULLOPEN);
	if (IDOK == dialog.DoModal())	{
    COLORREF color = dialog.GetColor();
    ambientColor = convert_color(color);
		m_btnAmbient.SetColor(color, color);
	}
}

void CEditWorldDialog::OnBnClickedEditBtnBkgndColor()
{
  // TODO: Add your control notification handler code here
	CColorDialog dialog(convert_color(backgroundColor), CC_FULLOPEN);
	if (IDOK == dialog.DoModal()) {
    COLORREF color = dialog.GetColor();
    backgroundColor = convert_color(color);
		m_btnBkgnd.SetColor(color, color);
	}
}

BOOL CEditWorldDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here 
  COLORREF ambColor = convert_color(ambientColor);
  COLORREF bkgColor = convert_color(backgroundColor);
  m_btnAmbient.Attach(IDC_EDIT_BTN_AMBIENT_COLOR, this, ambColor, ambColor, ambColor);
  m_btnBkgnd.Attach(IDC_EDIT_BTN_BKGND_COLOR, this, bkgColor, bkgColor, bkgColor);

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}
