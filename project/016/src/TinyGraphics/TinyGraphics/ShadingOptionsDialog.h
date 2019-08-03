#pragma once


// CShadingOptionsDialog dialog

class CShadingOptionsDialog : public CDialog
{
	DECLARE_DYNAMIC(CShadingOptionsDialog)

public:
	CShadingOptionsDialog(CWnd* pParent = NULL);   // standard constructor
	CShadingOptionsDialog(int rld, int rrd, bool um, CWnd* pParent = NULL);
	virtual ~CShadingOptionsDialog();

// Dialog Data
	enum { IDD = IDD_SHADING_OPTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
  int m_reflectDepth;
  int m_refractDepth;
  bool m_useMaterial;
};
