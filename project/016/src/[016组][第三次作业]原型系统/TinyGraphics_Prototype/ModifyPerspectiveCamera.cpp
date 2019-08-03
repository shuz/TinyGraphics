// ModifyPerspectiveCamera.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "ModifyPerspectiveCamera.h"

#include "Kernel/Primitive3D.h"
#include "Kernel/Vector3D.h"
#include "Kernel/PerspectiveCamera.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModifyPerspectiveCamera dialog


CModifyPerspectiveCamera::CModifyPerspectiveCamera(PerspectiveCamera *camera,
                                                   CWnd* pParent /*=NULL*/)
	: CDialog(CModifyPerspectiveCamera::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModifyPerspectiveCamera)
  //}}AFX_DATA_INIT
	m_copX = camera->get_cop().x;
	m_copY = camera->get_cop().y;
	m_copZ = camera->get_cop().z;
	m_vpnX = camera->get_vpn()(0);
	m_vpnY = camera->get_vpn()(1);
	m_vpnZ = camera->get_vpn()(2);
	m_vrpX = camera->get_vrp().x;
	m_vrpY = camera->get_vrp().y;
	m_vrpZ = camera->get_vrp().z;
	m_vupX = camera->get_vup()(0);
	m_vupY = camera->get_vup()(1);
	m_vupZ = camera->get_vup()(2);
	camera->get_vpw(m_umin, m_umax, m_vmin, m_vmax);

  m_camera = camera;
}


void CModifyPerspectiveCamera::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModifyPerspectiveCamera)
	DDX_Text(pDX, IDC_EDIT_COP_X, m_copX);
	DDX_Text(pDX, IDC_EDIT_COP_Y, m_copY);
	DDX_Text(pDX, IDC_EDIT_COP_Z, m_copZ);
	DDX_Text(pDX, IDC_EDIT_U_MAX, m_umax);
	DDX_Text(pDX, IDC_EDIT_U_MIN, m_umin);
	DDX_Text(pDX, IDC_EDIT_V_MAX, m_vmax);
	DDX_Text(pDX, IDC_EDIT_V_MIN, m_vmin);
	DDX_Text(pDX, IDC_EDIT_VPN_X, m_vpnX);
	DDX_Text(pDX, IDC_EDIT_VPN_Y, m_vpnY);
	DDX_Text(pDX, IDC_EDIT_VPN_Z, m_vpnZ);
	DDX_Text(pDX, IDC_EDIT_VRP_X, m_vrpX);
	DDX_Text(pDX, IDC_EDIT_VRP_Y, m_vrpY);
	DDX_Text(pDX, IDC_EDIT_VRP_Z, m_vrpZ);
	DDX_Text(pDX, IDC_EDIT_VUP_X, m_vupX);
	DDX_Text(pDX, IDC_EDIT_VUP_Y, m_vupY);
	DDX_Text(pDX, IDC_EDIT_VUP_Z, m_vupZ);
	//}}AFX_DATA_MAP

  if (m_umin >= m_umax || m_vmin >= m_vmax) {
    MessageBox("Error: Window size error.", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
  if (Vector3D(m_vpnX, m_vpnY, m_vpnZ).cross_product(
        Vector3D(m_vupX, m_vupY, m_vupZ)) == Vector3D(0, 0, 0)) {
    MessageBox("Error: VUP is parellel to VPN", NULL, MB_OK | MB_ICONWARNING);
    pDX->Fail();
  }
}


BEGIN_MESSAGE_MAP(CModifyPerspectiveCamera, CDialog)
	//{{AFX_MSG_MAP(CModifyPerspectiveCamera)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModifyPerspectiveCamera message handlers

void CModifyPerspectiveCamera::OnOK() 
{
	// TODO: Add extra validation here
  UpdateData(TRUE);

  m_camera->set_vrp(Point3D (m_vrpX, m_vrpY, m_vrpZ));
  m_camera->set_cop(Point3D (m_copX, m_copY, m_copZ));
  m_camera->set_vpn(Vector3D(m_vpnX, m_vpnY, m_vpnZ));
  m_camera->set_vup(Vector3D(m_vupX, m_vupY, m_vupZ));
  m_camera->set_vpw(m_umin, m_umax, m_vmin, m_vmax);
  
	CDialog::OnOK();
}
