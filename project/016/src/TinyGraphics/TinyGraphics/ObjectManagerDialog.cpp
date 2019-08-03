// ObjectManagerDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TinyGraphics.h"
#include "AddObjectDialog.h"
#include "ObjectManagerDialog.h"


// CObjectManagerDialog dialog

IMPLEMENT_DYNAMIC(CObjectManagerDialog, CDialog)
CObjectManagerDialog::CObjectManagerDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CObjectManagerDialog::IDD, pParent), pDoc(pDoc)
{
}

CObjectManagerDialog::CObjectManagerDialog(CTinyGraphicsDoc *pDoc, CWnd* pParent /*=NULL*/)
	: CDialog(CObjectManagerDialog::IDD, pParent), pDoc(pDoc)
{
}

CObjectManagerDialog::~CObjectManagerDialog()
{
}

void CObjectManagerDialog::DoDataExchange(CDataExchange* pDX)
{
  CDialog::DoDataExchange(pDX);
  DDX_Control(pDX, IDC_OBJECT_LIST, m_listbox);
  DDX_Control(pDX, ID_BTN_REMOVE, m_btnRemove);
  DDX_Control(pDX, ID_BTN_EDIT, m_btnEdit);
}


BEGIN_MESSAGE_MAP(CObjectManagerDialog, CDialog)
  ON_LBN_SELCANCEL(IDC_OBJECT_LIST, OnLbnSelcancelObjectList)
  ON_LBN_SELCHANGE(IDC_OBJECT_LIST, OnLbnSelchangeObjectList)
  ON_BN_CLICKED(ID_BTN_EDIT, OnBnClickedBtnEdit)
  ON_BN_CLICKED(ID_BTN_REMOVE, OnBnClickedBtnRemove)
  ON_BN_CLICKED(ID_BTN_ADD, OnBnClickedBtnAdd)
END_MESSAGE_MAP()


// CObjectManagerDialog message handlers

BOOL CObjectManagerDialog::OnInitDialog()
{
  CDialog::OnInitDialog();

  // TODO:  Add extra initialization here
  FillList();

  m_btnEdit.EnableWindow(FALSE);
  m_btnRemove.EnableWindow(FALSE);

  return TRUE;  // return TRUE unless you set the focus to a control
  // EXCEPTION: OCX Property Pages should return FALSE
}


void CObjectManagerDialog::OnLbnSelcancelObjectList()
{
  // TODO: Add your control notification handler code here
  m_btnEdit.EnableWindow(FALSE);
  m_btnRemove.EnableWindow(FALSE);
}

void CObjectManagerDialog::OnLbnSelchangeObjectList()
{
  // TODO: Add your control notification handler code here
  m_btnEdit.EnableWindow(TRUE);
  m_btnRemove.EnableWindow(TRUE);
}

void CObjectManagerDialog::OnBnClickedBtnEdit()
{
  // TODO: Add your control notification handler code here
  int i = m_listbox.GetCurSel();
  if (i == LB_ERR) return;
  if (((CObject3DAdaptor *)m_listbox.GetItemDataPtr(i))->EditObject())
    pDoc->SetModifiedFlag();
}

void CObjectManagerDialog::OnBnClickedBtnRemove()
{
  // TODO: Add your control notification handler code here
  int i = m_listbox.GetCurSel();
  if (i == LB_ERR) return;
  pDoc->RemoveObject((CObject3DAdaptor *)m_listbox.GetItemDataPtr(i));
  m_listbox.DeleteString(i);
  pDoc->SetModifiedFlag();
}

void CObjectManagerDialog::OnBnClickedBtnAdd()
{
  // TODO: Add your control notification handler code here
  CAddObjectDialog dialog(pDoc);
  if (IDOK == dialog.DoModal()) {
    m_listbox.ResetContent();
    FillList();
  }
}

void CObjectManagerDialog::FillList()
{
  int i = 0;
  POSITION pos = pDoc->m_objects.GetStartPosition();
  CObject3DAdaptor *adaptor;
  Object3D *object;
  while (pos != 0)
  {
    pDoc->m_objects.GetNextAssoc(pos, object, adaptor);
    m_listbox.InsertString(i, adaptor->name);
    m_listbox.SetItemDataPtr(i, adaptor);
    ++i;
  }
}
