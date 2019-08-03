// TinyGraphicsDoc.h : interface of the CTinyGraphicsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TINYGRAPHICSDOC_H__8C11DF3E_AA2C_494C_94D7_34F80197B001__INCLUDED_)
#define AFX_TINYGRAPHICSDOC_H__8C11DF3E_AA2C_494C_94D7_34F80197B001__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class World3D;

class CTinyGraphicsDoc : public CDocument
{
protected: // create from serialization only
	CTinyGraphicsDoc();
	DECLARE_DYNCREATE(CTinyGraphicsDoc)

// Attributes
public:
  World3D *world;
  
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTinyGraphicsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CTinyGraphicsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CTinyGraphicsDoc)
	afx_msg void OnMenuInsertCuboid();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TINYGRAPHICSDOC_H__8C11DF3E_AA2C_494C_94D7_34F80197B001__INCLUDED_)
