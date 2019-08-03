#pragma once
#include "afxwin.h"

#include "TinyGraphicsDoc.h"

// CObjectManagerDialog dialog

class CObjectManagerDialog : public CDialog
{
	DECLARE_DYNAMIC(CObjectManagerDialog)

public:
	CObjectManagerDialog(CWnd* pParent = NULL);   // standard constructor
  CObjectManagerDialog(CTinyGraphicsDoc *pDoc, CWnd* pParent = NULL);
	virtual ~CObjectManagerDialog();

// Dialog Data
	enum { IDD = IDD_OBJECT_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  afx_msg void OnLbnSelcancelObjectList();
  afx_msg void OnLbnSelchangeObjectList();
  afx_msg void OnBnClickedBtnEdit();
  afx_msg void OnBnClickedBtnRemove();
  afx_msg void OnBnClickedBtnAdd();

	DECLARE_MESSAGE_MAP()

public:
  CTinyGraphicsDoc *pDoc;
  virtual BOOL OnInitDialog();
  CListBox m_listbox;
  
  CButton m_btnRemove;
  CButton m_btnEdit;

  void FillList();
};
