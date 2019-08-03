// EditLightDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "EditLightDialog.h"
#include "Utilities.h"


// CEditLightDialog dialog

IMPLEMENT_DYNAMIC(CEditLightDialog, CDialog)
CEditLightDialog::CEditLightDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditLightDialog::IDD, pParent)
{
}

CEditLightDialog::CEditLightDialog(const Point3D& point, const Vector3D& dir, const Vector3D& att, real intensity,
                                   const ColorRGB& color, bool is_point, CString name, CWnd* pParent /*=NULL*/)
	: CDialog(CEditLightDialog::IDD, pParent),
    location(point), direction(dir), attenuation(att), intensity(intensity),
    color(color), is_point(is_point), name(name)
{
}

CEditLightDialog::~CEditLightDialog()
{
}

void CEditLightDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_EDIT_LOCATION_X, location.x);
  DDX_Text(pDX, IDC_EDIT_LOCATION_Y, location.y);
  DDX_Text(pDX, IDC_EDIT_LOCATION_Z, location.z);

  DDX_Text(pDX, IDC_EDIT_VF_X, direction(0));
  DDX_Text(pDX, IDC_EDIT_VF_Y, direction(1));
  DDX_Text(pDX, IDC_EDIT_VF_Z, direction(2));

  DDX_Text(pDX, IDC_EDIT_VUP_X, attenuation(0));
  DDX_Text(pDX, IDC_EDIT_VUP_Y, attenuation(1));
  DDX_Text(pDX, IDC_EDIT_VUP_Z, attenuation(2));

  DDX_Text(pDX, IDC_EDIT_INTENSITY, intensity);
  DDX_Text(pDX, IDC_EDIT_NAME, name);

  DDX_Control(pDX, IDC_EDIT_VF_X, m_dirxEdit);
  DDX_Control(pDX, IDC_EDIT_VF_Y, m_diryEdit);
  DDX_Control(pDX, IDC_EDIT_VF_Z, m_dirzEdit);

  if (abs(attenuation.norm()) <= TG_EPSILON) {
    MessageBox("Warning: attenuation nearly 0", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }

  if (name == "") {
    MessageBox("Warning: name empty", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
}


BEGIN_MESSAGE_MAP(CEditLightDialog, CDialog)
  ON_BN_CLICKED(IDC_EDIT_BTN_COLOR, OnBnClickedEditBtnColor)
END_MESSAGE_MAP()


// CEditLightDialog message handlers

BOOL CEditLightDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  if (is_point) {
    m_dirxEdit.EnableWindow(FALSE);
    m_diryEdit.EnableWindow(FALSE);
    m_dirzEdit.EnableWindow(FALSE);
  }

  COLORREF rcolor = convert_color(color);
  m_colorBtn.Attach(IDC_EDIT_BTN_COLOR, this, rcolor, rcolor, rcolor);

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditLightDialog::OnBnClickedEditBtnColor()
{
  // TODO: Add your control notification handler code here
  CColorDialog dialog(convert_color(color), CC_FULLOPEN);
	if (IDOK == dialog.DoModal()) {
    COLORREF rcolor = dialog.GetColor();
    color = convert_color(rcolor);
		m_colorBtn.SetColor(rcolor, rcolor);
	}
}
