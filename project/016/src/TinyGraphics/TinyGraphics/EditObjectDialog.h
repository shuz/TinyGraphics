#pragma once

#include "Kernel/Primitive3D.h"
#include "Kernel/Vector3D.h"
#include "Kernel/Material.h"
#include "Kernel/Position.h"
#include "CImageTexture.h"
#include "ColorButton.h"
#include "afxwin.h"

using namespace TinyGraphics;

// CEditObjectDialog dialog

class CEditObjectDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditObjectDialog)

public:
	CEditObjectDialog(CWnd* pParent = NULL);   // standard constructor
  CEditObjectDialog(const Position& position, const Material& material,
                    double l, double w, double h, double r, int lx,
                    CString name, CWnd *pParent = NULL);
	virtual ~CEditObjectDialog();

// Dialog Data
	enum { IDD = IDD_EDIT_OBJECT };

protected:
  
  virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  Point3D location;
  Vector3D vf, vup;
  double l, w, h, r;
  int lx;
  CString name;

  bool enable_precision;
  bool enable_length;
  bool enable_width;
  bool enable_height;
  bool enable_radius;

  Material GetMaterial();

private:
  Material material;        // use GetMaterial to access

  CEdit m_precisionEdit;
  CEdit m_lengthEdit;
  CEdit m_widthEdit;
  CEdit m_heightEdit;
  CEdit m_radiusEdit;
  CColorButton m_btnColor;
  CStatic m_texture;
  HBITMAP m_blankBitmap;

public:
  afx_msg void OnBnClickedEditBtnColor();
  afx_msg void OnBnClickedTextureAttach();
  afx_msg void OnBnClickedTextureRemove();
  void DrawTexture(CImageTexture *texture);
  afx_msg void OnBnClickedCancel();
  afx_msg void OnPaint();
};
