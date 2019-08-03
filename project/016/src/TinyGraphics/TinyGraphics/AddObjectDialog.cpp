// AddObjectDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "CuboidAdaptor.h"
#include "ConeAdaptor.h"
#include "PlaneAdaptor.h"
#include "SphereAdaptor.h"
#include "CylinderAdaptor.h"
#include "AddObjectDialog.h"

// CAddObjectDialog dialog

IMPLEMENT_DYNAMIC(CAddObjectDialog, CDialog)
CAddObjectDialog::CAddObjectDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAddObjectDialog::IDD, pParent)
{
}

CAddObjectDialog::CAddObjectDialog(CTinyGraphicsDoc *pDoc, CWnd *pParent /*=NULL*/)
	: CDialog(CAddObjectDialog::IDD, pParent), pDoc(pDoc)
{
}

CAddObjectDialog::~CAddObjectDialog()
{
}

void CAddObjectDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddObjectDialog, CDialog)
  ON_BN_CLICKED(ID_ADD_CONE, OnBnClickedAddCone)
  ON_BN_CLICKED(ID_ADD_CUBOID, OnBnClickedAddCuboid)
  ON_BN_CLICKED(ID_ADD_CYLINDER, OnBnClickedAddCylinder)
  ON_BN_CLICKED(ID_ADD_PLANE, OnBnClickedAddPlane)
  ON_BN_CLICKED(ID_ADD_SPHERE, OnBnClickedAddSphere)
END_MESSAGE_MAP()


// CAddObjectDialog message handlers

void CAddObjectDialog::OnBnClickedAddCone()
{
  // TODO: Add your control notification handler code here
  CObject3DAdaptor *adaptor = new CConeAdaptor(new Cone(), "Cone");
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    EndDialog(IDOK);
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CAddObjectDialog::OnBnClickedAddCuboid()
{
  // TODO: Add your control notification handler code here
  CObject3DAdaptor *adaptor = new CCuboidAdaptor(new Cuboid(), "Cuboid");
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    EndDialog(IDOK);
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CAddObjectDialog::OnBnClickedAddCylinder()
{
  // TODO: Add your control notification handler code here
  CObject3DAdaptor *adaptor = new CCylinderAdaptor(new Cylinder(), "Cylinder");
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    EndDialog(IDOK);
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CAddObjectDialog::OnBnClickedAddPlane()
{
  // TODO: Add your control notification handler code here
  CObject3DAdaptor *adaptor = new CPlaneAdaptor(new Plane(), "Plane");
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    EndDialog(IDOK);
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

void CAddObjectDialog::OnBnClickedAddSphere()
{
  // TODO: Add your control notification handler code here
  CObject3DAdaptor *adaptor = new CSphereAdaptor(new Sphere(), "Sphere");
  pDoc->AddObject(adaptor);
  if (adaptor->EditObject()) {
    EndDialog(IDOK);
    pDoc->SetModifiedFlag();
  } else {
    pDoc->RemoveObject(adaptor);
  }
}

