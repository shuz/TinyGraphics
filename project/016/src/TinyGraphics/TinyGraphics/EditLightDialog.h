#pragma once

#include "Kernel/Primitive3D.h"
#include "Kernel/Vector3D.h"
#include "Kernel/ColorRGB.h"
#include "ColorButton.h"
#include "afxwin.h"

using namespace TinyGraphics;

// CEditLightDialog dialog

class CEditLightDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditLightDialog)

public:
	CEditLightDialog(CWnd* pParent = NULL);   // standard constructor
	CEditLightDialog(const Point3D& point, const Vector3D& dir, const Vector3D& att, real intensity,
                   const ColorRGB& color, bool is_point, CString name, CWnd* pParent = NULL);   // standard constructor
	virtual ~CEditLightDialog();

// Dialog Data
	enum { IDD = IDD_EDIT_LIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedEditBtnColor();

	DECLARE_MESSAGE_MAP()
public:
  Point3D location;
  Vector3D direction;
  Vector3D attenuation;
  real intensity;
  ColorRGB color;
  bool is_point;
  CString name;

private:
  CEdit m_dirxEdit;
  CEdit m_diryEdit;
  CEdit m_dirzEdit;
  CColorButton m_colorBtn;
};
