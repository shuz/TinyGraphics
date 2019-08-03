// EditCameraDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"

#include "EditCameraDialog.h"

// CEditCameraDialog dialog

IMPLEMENT_DYNAMIC(CEditCameraDialog, CDialog)
CEditCameraDialog::CEditCameraDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEditCameraDialog::IDD, pParent)
{
}

CEditCameraDialog::CEditCameraDialog(const ParallelCamera *c0,
                                     const PerspectiveCamera *c1,
                                     bool ip, CWnd* pParent /*= NULL*/)
	: CDialog(CEditCameraDialog::IDD, pParent)
{
  location[0] = c0->get_location();
  location[1] = c1->get_location();

  vf[0] = c0->get_front_vector();
  vf[1] = c1->get_front_vector();

  vup[0] = c0->get_up_vector();
  vup[1] = c1->get_up_vector();

  pd[0] = c0->get_project_direction();
  pd[1] = c1->get_project_direction();

  real vpw_width, vpw_height;

  c0->get_vpw(vpw_width, vpw_height);
  vpw[0] = vpw_width;
  ar[0] = vpw_height / vpw_width;

  c1->get_vpw(vpw_width, vpw_height);
  vpw[1] = vpw_width;
  ar[1] = vpw_height / vpw_width;

  real cop_dist = c1->get_cop_distance();
  cop = Point3D(pd[1] * cop_dist);

  is_parallel = ip;
  i = is_parallel ? 0 : 1;
}

CEditCameraDialog::~CEditCameraDialog()
{
}

void CEditCameraDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);

  DDX_Text(pDX, IDC_EDIT_LOCATION_X, location[i].x);
  DDX_Text(pDX, IDC_EDIT_LOCATION_Y, location[i].y);
  DDX_Text(pDX, IDC_EDIT_LOCATION_Z, location[i].z);

  DDX_Text(pDX, IDC_EDIT_VF_X, vf[i](0));
  DDX_Text(pDX, IDC_EDIT_VF_Y, vf[i](1));
  DDX_Text(pDX, IDC_EDIT_VF_Z, vf[i](2));

  DDX_Text(pDX, IDC_EDIT_VUP_X, vup[i](0));
  DDX_Text(pDX, IDC_EDIT_VUP_Y, vup[i](1));
  DDX_Text(pDX, IDC_EDIT_VUP_Z, vup[i](2));

  DDX_Text(pDX, IDC_EDIT_PD_U, pd[i](0));
  DDX_Text(pDX, IDC_EDIT_PD_V, pd[i](1));
  DDX_Text(pDX, IDC_EDIT_PD_N, pd[i](2));

  DDX_Text(pDX, IDC_EDIT_COP_U, cop.x);
  DDX_Text(pDX, IDC_EDIT_COP_V, cop.y);
  DDX_Text(pDX, IDC_EDIT_COP_N, cop.z);

  DDX_Text(pDX, IDC_EDIT_VPW, vpw[i]);

  DDX_Control(pDX, IDC_EDIT_COP_U, m_copuEdit);
  DDX_Control(pDX, IDC_EDIT_COP_V, m_copvEdit);
  DDX_Control(pDX, IDC_EDIT_COP_N, m_copnEdit);

  if (abs(abs(vf[i].dot_product(vup[i])) - 1) <= TG_EPSILON) {
    MessageBox("Warning: VUP is parallel to VF", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }

  if (abs(abs(pd[i].dot_product(Vector3D::Y_AXIS)) - 1) <= TG_EPSILON) {
    MessageBox("Warning: PD is parallel to V axis", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }

  if (!is_parallel && abs(cop.z) <= TG_EPSILON) {
    MessageBox("Warning: COP is on X-Y plane", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }

  DDX_Radio(pDX, IDC_RADIO_PARALLEL_CAMERA, i);
  is_parallel = (i == 0);
}


BEGIN_MESSAGE_MAP(CEditCameraDialog, CDialog)
  ON_BN_CLICKED(IDC_RADIO_PARALLEL_CAMERA, OnBnClickedRadioParallelCamera)
  ON_BN_CLICKED(IDC_RADIO_PERSPECTIVE_CAMERA, OnBnClickedRadioPerspectiveCamera)
END_MESSAGE_MAP()


// CEditCameraDialog message handlers

BOOL CEditCameraDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  if (is_parallel) {
    m_copuEdit.EnableWindow(FALSE);
    m_copvEdit.EnableWindow(FALSE);
    m_copnEdit.EnableWindow(FALSE);
  }

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}

void CEditCameraDialog::OnBnClickedRadioParallelCamera()
{
  // TODO: Add your control notification handler code here
  if (!is_parallel) {
    m_copuEdit.EnableWindow(FALSE);
    m_copvEdit.EnableWindow(FALSE);
    m_copnEdit.EnableWindow(FALSE);
    UpdateData(TRUE);
    i = 0;
    UpdateData(FALSE);
  }
}

void CEditCameraDialog::OnBnClickedRadioPerspectiveCamera()
{
  // TODO: Add your control notification handler code here
  if (is_parallel) {
    m_copuEdit.EnableWindow(TRUE);
    m_copvEdit.EnableWindow(TRUE);
    m_copnEdit.EnableWindow(TRUE);
    UpdateData(TRUE);
    i = 1;
    UpdateData(FALSE);
  }
}
