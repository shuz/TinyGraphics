// EditObjectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "Utilities.h"
#include "EditObjectDialog.h"
#include ".\editobjectdialog.h"

// CEditObjectDialog dialog

IMPLEMENT_DYNAMIC(CEditObjectDialog, CDialog)

CEditObjectDialog::CEditObjectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditObjectDialog::IDD, pParent)
{
}

CEditObjectDialog::CEditObjectDialog(const Position& position, const Material& material,
                                     double l, double w, double h, double r, int lx,
                                     CString name, CWnd *pParent /*= NULL*/)
  : CDialog(CEditObjectDialog::IDD, pParent),
    location(position.get_location()), vf(position.get_front_vector()), vup(position.get_up_vector()),
    material(material), l(l), w(w), h(h), r(r), lx(lx), name(name),
    enable_precision(lx >= 0),
    enable_length(l > 0), enable_width(w > 0),
    enable_height(h > 0), enable_radius(r > 0)
{
}

CEditObjectDialog::~CEditObjectDialog()
{
  delete material.texture;
}

void CEditObjectDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_EDIT_LOCATION_X, location.x);
  DDX_Text(pDX, IDC_EDIT_LOCATION_Y, location.y);
  DDX_Text(pDX, IDC_EDIT_LOCATION_Z, location.z);

  DDX_Text(pDX, IDC_EDIT_VF_X, vf(0));
  DDX_Text(pDX, IDC_EDIT_VF_Y, vf(1));
  DDX_Text(pDX, IDC_EDIT_VF_Z, vf(2));

  DDX_Text(pDX, IDC_EDIT_VUP_X, vup(0));
  DDX_Text(pDX, IDC_EDIT_VUP_Y, vup(1));
  DDX_Text(pDX, IDC_EDIT_VUP_Z, vup(2));

  DDX_Text(pDX, IDC_EDIT_PRECISION, lx);
  DDX_Text(pDX, IDC_EDIT_AMBIENT,     material.k_ambient);
  DDX_Text(pDX, IDC_EDIT_DIFFUSE,     material.k_diffuse);
  DDX_Text(pDX, IDC_EDIT_SPECULAR,    material.k_specular);
  DDX_Text(pDX, IDC_EDIT_SHINENESS,   material.shininess);
  DDX_Text(pDX, IDC_EDIT_TRANSMIT,    material.k_transparency);
  DDX_Text(pDX, IDC_EDIT_REFRACT_IDX, material.refraction_index);

  DDX_Text(pDX, IDC_EDIT_LENGTH, l);
  DDX_Text(pDX, IDC_EDIT_WIDTH,  w);
  DDX_Text(pDX, IDC_EDIT_HEIGHT, h);
  DDX_Text(pDX, IDC_EDIT_RADIUS, r);

  DDX_Text(pDX, IDC_EDIT_NAME, name);

  DDX_Control(pDX, IDC_EDIT_PRECISION, m_precisionEdit);
  DDX_Control(pDX, IDC_EDIT_LENGTH, m_lengthEdit);
  DDX_Control(pDX, IDC_EDIT_WIDTH,  m_widthEdit);
  DDX_Control(pDX, IDC_EDIT_HEIGHT, m_heightEdit);
  DDX_Control(pDX, IDC_EDIT_RADIUS, m_radiusEdit);

  if (enable_precision) DDV_MinMaxInt(pDX, lx, 0, INT_MAX);
  if (enable_length && l <= 0) {
    MessageBox("Warning: length <= 0", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
  if (enable_width && w <= 0) {
    MessageBox("Warning: width <= 0", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
  if (enable_height && h <= 0) {
    MessageBox("Warning: height <= 0", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
  if (enable_radius && r <= 0) {
    MessageBox("Warning: radius <= 0", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }

  DDV_MinMaxDouble(pDX, material.k_ambient,  0, 1);
  DDV_MinMaxDouble(pDX, material.k_diffuse,  0, 1);
  DDV_MinMaxDouble(pDX, material.k_specular, 0, 1);
  DDV_MinMaxInt   (pDX, material.shininess,  1, INT_MAX);
  DDV_MinMaxDouble(pDX, material.k_transparency,    0, 1);
  DDV_MinMaxDouble(pDX, material.refraction_index,  1, DBL_MAX);

  if (name == "") {
    MessageBox("Warning: name empty", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }

  if (abs(abs(vf.dot_product(vup)) - 1) <= TG_EPSILON) {
    MessageBox("Warning: VUP is parallel to VF", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
  DDX_Control(pDX, IDC_TEXTURE, m_texture);
}


BEGIN_MESSAGE_MAP(CEditObjectDialog, CDialog)
  ON_BN_CLICKED(IDC_EDIT_BTN_COLOR, OnBnClickedEditBtnColor)
  ON_BN_CLICKED(ID_TEXTURE_ATTACH, OnBnClickedTextureAttach)
  ON_BN_CLICKED(ID_TEXTURE_REMOVE, OnBnClickedTextureRemove)
  ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
  ON_WM_PAINT()
END_MESSAGE_MAP()


// CEditObjectDialog message handlers

BOOL CEditObjectDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  m_precisionEdit.EnableWindow(enable_precision);
  m_lengthEdit.EnableWindow(enable_length);
  m_widthEdit.EnableWindow(enable_width);
  m_heightEdit.EnableWindow(enable_height);
  m_radiusEdit.EnableWindow(enable_radius);

  COLORREF color = convert_color(material.color);
  m_btnColor.Attach(IDC_EDIT_BTN_COLOR, this, color, color, color);

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditObjectDialog::OnBnClickedEditBtnColor()
{
  // TODO: Add your control notification handler code here
	CColorDialog dialog(convert_color(material.color), CC_FULLOPEN);
	if (IDOK == dialog.DoModal())	{
    COLORREF color = dialog.GetColor();
    material.color = convert_color(color);
		m_btnColor.SetColor(color, color);
	}
}

void CEditObjectDialog::OnBnClickedTextureAttach()
{
  // TODO: Add your control notification handler code here
  static char szFilter[] = "Picture Files |*.bmp; *.jpg; *.gif; *.png|All Files (*.*)|*.*||";

  CFileDialog dialog(TRUE, NULL, NULL, OFN_HIDEREADONLY, szFilter);
  if (IDOK == dialog.DoModal()) try {
    if (material.texture != 0) {
      delete material.texture;
      material.texture = 0;
    }
    CImageTexture *texture =  new CImageTexture(dialog.GetPathName());
    material.texture = texture;
    DrawTexture(texture);
  } catch (const CImageTexture::LoadFailure& except) {
    MessageBox(CString("Error: ") + except.what(), NULL, MB_OK | MB_ICONERROR);
  }
}

void CEditObjectDialog::OnBnClickedTextureRemove()
{
  // TODO: Add your control notification handler code here
  if (material.texture != 0) {
    m_texture.ShowWindow(SW_HIDE);
    delete material.texture;
    material.texture = 0;
  }
}

void CEditObjectDialog::DrawTexture(CImageTexture *texture)
{
  m_texture.ShowWindow(SW_SHOW);
  CRect destRect;
  m_texture.GetClientRect(&destRect);
  CClientDC textureDC(&m_texture);
  texture->get_image()->StretchBlt(textureDC.m_hDC, destRect);
}

Material CEditObjectDialog::GetMaterial()
{
  Material rtv(material);
  material.texture = 0;
  return rtv;
}

void CEditObjectDialog::OnBnClickedCancel()
{
  // TODO: Add your control notification handler code here
  material.texture = 0;
  OnCancel();
}

void CEditObjectDialog::OnPaint()
{
  CPaintDC dc(this); // device context for painting
  // TODO: Add your message handler code here
  // Do not call CDialog::OnPaint() for painting messages
  
  if (material.texture != 0) {
    DrawTexture((CImageTexture *)material.texture);
  }
}
