// CGFrameworkDoc.h : interface of the CCGFrameworkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CGFRAMEWORKDOC_H__41D12D61_8D49_4DC3_A5B5_7A09B47575C6__INCLUDED_)
#define AFX_CGFRAMEWORKDOC_H__41D12D61_8D49_4DC3_A5B5_7A09B47575C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CCGFrameworkDoc : public CDocument
{
protected: // create from serialization only
	CCGFrameworkDoc();
	DECLARE_DYNCREATE(CCGFrameworkDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCGFrameworkDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCGFrameworkDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCGFrameworkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CGFRAMEWORKDOC_H__41D12D61_8D49_4DC3_A5B5_7A09B47575C6__INCLUDED_)
