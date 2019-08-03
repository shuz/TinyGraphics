#pragma once

#include "TinyGraphicsDoc.h"

// CAddObjectDialog dialog

class CAddObjectDialog : public CDialog
{
	DECLARE_DYNAMIC(CAddObjectDialog)

public:
	CAddObjectDialog(CWnd* pParent = NULL);   // standard constructor
  CAddObjectDialog(CTinyGraphicsDoc *pDoc, CWnd* pParent = NULL);
	virtual ~CAddObjectDialog();

// Dialog Data
	enum { IDD = IDD_ADD_OBJECT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
  CTinyGraphicsDoc *pDoc;
  afx_msg void OnBnClickedAddCone();
  afx_msg void OnBnClickedAddCuboid();
  afx_msg void OnBnClickedAddCylinder();
  afx_msg void OnBnClickedAddPlane();
  afx_msg void OnBnClickedAddSphere();
};
