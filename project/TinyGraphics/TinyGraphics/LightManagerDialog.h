#pragma once
#include "afxwin.h"

#include "TinyGraphicsDoc.h"

// CLightManagerDialog dialog

class CLightManagerDialog : public CDialog
{
	DECLARE_DYNAMIC(CLightManagerDialog)

public:
	CLightManagerDialog(CWnd* pParent = NULL);   // standard constructor
  CLightManagerDialog(CTinyGraphicsDoc *pDoc, CWnd* pParent = NULL);
	virtual ~CLightManagerDialog();

// Dialog Data
	enum { IDD = IDD_LIGHT_MANAGER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  afx_msg void OnLbnSelcancelLightList();
  afx_msg void OnLbnSelchangeLightList();
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
