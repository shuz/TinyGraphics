#pragma once

#include "Kernel/Position.h"
#include "Kernel/Vector3D.h"
#include "Kernel/Primitive3D.h"

#include "Kernel/ParallelCamera.h"
#include "Kernel/PerspectiveCamera.h"

#include "afxwin.h"

using namespace TinyGraphics;

// CEditCameraDialog dialog

class CEditCameraDialog : public CDialog
{
	DECLARE_DYNAMIC(CEditCameraDialog)

public:
	CEditCameraDialog(CWnd* pParent = NULL);   // standard constructor
  CEditCameraDialog(const ParallelCamera *parallelCamera,
                    const PerspectiveCamera *perspectiveCamera,
                    bool is_parallel, CWnd* pParent = NULL);
	virtual ~CEditCameraDialog();

// Dialog Data
	enum { IDD = IDD_EDIT_CAMERA };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
  virtual BOOL OnInitDialog();
  afx_msg void OnBnClickedRadioParallelCamera();
  afx_msg void OnBnClickedRadioPerspectiveCamera();

	DECLARE_MESSAGE_MAP()

public:
  Point3D location[2];
  Vector3D vf[2], vup[2], pd[2];
  Point3D cop;
  real vpw[2], ar[2];
  bool is_parallel;

private:
  int i;
  CEdit m_copuEdit;
  CEdit m_copvEdit;
  CEdit m_copnEdit;
};
