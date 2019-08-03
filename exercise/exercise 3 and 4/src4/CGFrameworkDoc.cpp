// CGFrameworkDoc.cpp : implementation of the CCGFrameworkDoc class
//

#include "stdafx.h"
#include "CGFramework.h"

#include "CGFrameworkDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkDoc

IMPLEMENT_DYNCREATE(CCGFrameworkDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGFrameworkDoc, CDocument)
	//{{AFX_MSG_MAP(CCGFrameworkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkDoc construction/destruction

CCGFrameworkDoc::CCGFrameworkDoc()
{
	// TODO: add one-time construction code here

}

CCGFrameworkDoc::~CCGFrameworkDoc()
{
}

BOOL CCGFrameworkDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkDoc serialization

void CCGFrameworkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkDoc diagnostics

#ifdef _DEBUG
void CCGFrameworkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGFrameworkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCGFrameworkDoc commands
