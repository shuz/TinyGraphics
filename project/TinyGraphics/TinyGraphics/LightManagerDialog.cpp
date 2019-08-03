// LightManagerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "AddLightDialog.h"
#include "LightManagerDialog.h"
#include ".\lightmanagerdialog.h"


// CLightManagerDialog dialog

IMPLEMENT_DYNAMIC(CLightManagerDialog, CDialog)
CLightManagerDialog::CLightManagerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CLightManagerDialog::IDD, pParent), pDoc(pDoc)
{
}

CLightManagerDialog::CLightManagerDialog(CTinyGraphicsDoc *pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CLightManagerDialog::IDD, pParent), pDoc(pDoc)
{
}

CLightManagerDialog::~CLightManagerDialog()
{
}

void CLightManagerDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_LIGHT_LIST, m_listbox);
  DDX_Control(pDX, ID_BTN_REMOVE, m_btnRemove);
  DDX_Control(pDX, ID_BTN_EDIT, m_btnEdit);
}


BEGIN_MESSAGE_MAP(CLightManagerDialog, CDialog)
  ON_LBN_SELCANCEL(IDC_LIGHT_LIST, OnLbnSelcancelLightList)
  ON_LBN_SELCHANGE(IDC_LIGHT_LIST, OnLbnSelchangeLightList)
  ON_BN_CLICKED(ID_BTN_EDIT, OnBnClickedBtnEdit)
  ON_BN_CLICKED(ID_BTN_REMOVE, OnBnClickedBtnRemove)
  ON_BN_CLICKED(ID_BTN_ADD, OnBnClickedBtnAdd)
END_MESSAGE_MAP()


// CLightManagerDialog message handlers

BOOL CLightManagerDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  FillList();

  m_btnEdit.EnableWindow(FALSE);
  m_btnRemove.EnableWindow(FALSE);

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


void CLightManagerDialog::OnLbnSelcancelLightList()
{
  // TODO: Add your control notification handler code here
  m_btnEdit.EnableWindow(FALSE);
  m_btnRemove.EnableWindow(FALSE);
}

void CLightManagerDialog::OnLbnSelchangeLightList()
{
  // TODO: Add your control notification handler code here
  m_btnEdit.EnableWindow(TRUE);
  m_btnRemove.EnableWindow(TRUE);
}

void CLightManagerDialog::OnBnClickedBtnEdit()
{
  // TODO: Add your control notification handler code here
  int i = m_listbox.GetCurSel();
  if (i == LB_ERR) return;
  if (((CLightAdaptor *)m_listbox.GetItemDataPtr(i))->EditObject())
    pDoc->SetModifiedFlag();
}

void CLightManagerDialog::OnBnClickedBtnRemove()
{
  // TODO: Add your control notification handler code here
  int i = m_listbox.GetCurSel();
  if (i == LB_ERR) return;
  pDoc->RemoveLight((CLightAdaptor *)m_listbox.GetItemDataPtr(i));
  m_listbox.DeleteString(i);
  pDoc->SetModifiedFlag();
}

void CLightManagerDialog::OnBnClickedBtnAdd()
{
  // TODO: Add your control notification handler code here
  CAddLightDialog dialog(pDoc);
  if (IDOK == dialog.DoModal()) {
    m_listbox.ResetContent();
    FillList();
  }
}

void CLightManagerDialog::FillList()
{
  int i = 0;
  POSITION pos = pDoc->m_lights.GetStartPosition();
  CLightAdaptor *adaptor;
  Light *object;
  while (pos != 0)
  {
    pDoc->m_lights.GetNextAssoc(pos, object, adaptor);
    m_listbox.InsertString(i, adaptor->name);
    m_listbox.SetItemDataPtr(i, adaptor);
    ++i;
  }
}
