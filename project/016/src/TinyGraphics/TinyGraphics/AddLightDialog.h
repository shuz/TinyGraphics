#pragma once

#include "TinyGraphicsDoc.h"

// CAddLightDialog dialog

class CAddLightDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddLightDialog)

public:
	CAddLightDialog(CWnd* pParent = NULL);   // standard constructor
  CAddLightDialog(CTinyGraphicsDoc *pDoc, CWnd* pParent = NULL);
	virtual ~CAddLightDialog();

// Dialog Data
	enum { IDD = IDD_ADD_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
  CTinyGraphicsDoc *pDoc;
  afx_msg void OnBnClickedAddParallel();
  afx_msg void OnBnClickedAddPoint();
};
