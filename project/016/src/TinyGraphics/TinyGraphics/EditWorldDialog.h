#pragma once

#include "Kernel/real.h"
#include "Kernel/ColorRGB.h"

#include "ColorButton.h"

using namespace TinyGraphics;

// CEditWorldDialog dialog

class CEditWorldDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditWorldDialog)

public:
	CEditWorldDialog(CWnd* pParent = NULL);   // standard constructor
  CEditWorldDialog(const ColorRGB& ambientColor, const ColorRGB& backgroundColor,
                   real refract_idx, int non, CWnd* pParent = NULL);
	virtual ~CEditWorldDialog();

// Dialog Data
	enum { IDD = IDD_EDIT_WORLD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();

  afx_msg void OnBnClickedEditBtnAmbientColor();
  afx_msg void OnBnClickedEditBtnBkgndColor();

	DECLARE_MESSAGE_MAP()

public:
  ColorRGB ambientColor, backgroundColor;
  real refract_idx;
  int next_obj_num;

  CColorButton m_btnAmbient;
  CColorButton m_btnBkgnd;
};
