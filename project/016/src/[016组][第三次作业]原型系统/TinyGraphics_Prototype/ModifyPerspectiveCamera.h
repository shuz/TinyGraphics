#if !defined(AFX_MODIFYPERSPECTIVECAMERA_H__83D60D64_A4B0_417C_A461_9C30DDC47AB2__INCLUDED_)
#define AFX_MODIFYPERSPECTIVECAMERA_H__83D60D64_A4B0_417C_A461_9C30DDC47AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModifyPerspectiveCamera.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModifyPerspectiveCamera dialog

class PerspectiveCamera;

class CModifyPerspectiveCamera : public CDialog
{
// Construction
public:
	CModifyPerspectiveCamera(PerspectiveCamera *camera,
                           CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModifyPerspectiveCamera)
	enum { IDD = IDD_MODIFY_CAMERA };
	double	m_copX;
	double	m_copY;
	double	m_copZ;
	double	m_umax;
	double	m_umin;
	double	m_vmax;
	double	m_vmin;
	double	m_vpnX;
	double	m_vpnY;
	double	m_vpnZ;
	double	m_vrpX;
	double	m_vrpY;
	double	m_vrpZ;
	double	m_vupX;
	double	m_vupY;
	double	m_vupZ;
	//}}AFX_DATA

  PerspectiveCamera *m_camera;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModifyPerspectiveCamera)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModifyPerspectiveCamera)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIFYPERSPECTIVECAMERA_H__83D60D64_A4B0_417C_A461_9C30DDC47AB2__INCLUDED_)
