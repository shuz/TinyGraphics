// AddLightDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "ParallelLightAdaptor.h"
#include "PointLightAdaptor.h"
#include "AddLightDialog.h"
#include ".\addlightdialog.h"


// CAddLightDialog dialog

IMPLEMENT_DYNAMIC(CAddLightDialog, CDialog)
CAddLightDialog::CAddLightDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAddLightDialog::IDD, pParent)
{
}

CAddLightDialog::CAddLightDialog(CTinyGraphicsDoc *pDoc, CWnd *pParent /*=NULL*/)
	: CDialog(CAddLightDialog::IDD, pParent), pDoc(pDoc)
{
}

CAddLightDialog::~CAddLightDialog()
{
}

void CAddLightDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAddLightDialog, CDialog)
  ON_BN_CLICKED(ID_ADD_PARALLEL, OnBnClickedAddParallel)
  ON_BN_CLICKED(ID_ADD_POINT, OnBnClickedAddPoint)
END_MESSAGE_MAP()


// CAddLightDialog message handlers

void CAddLightDialog::OnBnClickedAddParallel()
{
  // TODO: Add your control notification handler code here

  ParallelLight *light = new ParallelLight();
  light->location.assign(5, 5, 5);
  CLightAdaptor *adaptor = new CParallelLightAdaptor(light, "Parallel Light");
  pDoc->AddLight(adaptor);
  if (adaptor->EditObject()) {
    pDoc->SetModifiedFlag();
    EndDialog(IDOK);
  } else {
    pDoc->RemoveLight(adaptor);
  }
}

void CAddLightDialog::OnBnClickedAddPoint()
{
  // TODO: Add your control notification handler code here
  
  PointLight *light = new PointLight();
  light->location.assign(5, 5, 5);
  CLightAdaptor *adaptor = new CPointLightAdaptor(light, "Point Light");
  pDoc->AddLight(adaptor);
  if (adaptor->EditObject()) {
    pDoc->SetModifiedFlag();
    EndDialog(IDOK);
  } else {
    pDoc->RemoveLight(adaptor);
  }
}
