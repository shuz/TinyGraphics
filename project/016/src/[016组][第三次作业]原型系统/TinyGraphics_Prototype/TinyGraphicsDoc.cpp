// TinyGraphicsDoc.cpp : implementation of the CTinyGraphicsDoc class
//

#include "stdafx.h"
#include "TinyGraphics.h"

#include "TinyGraphicsDoc.h"
#include "InsertCuboid.h"

#include "Kernel/Cuboid.h"
#include "Kernel/Primitive3D.h"
#include "Kernel/World3D.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsDoc

IMPLEMENT_DYNCREATE(CTinyGraphicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CTinyGraphicsDoc, CDocument)
	//{{AFX_MSG_MAP(CTinyGraphicsDoc)
	ON_COMMAND(ID_MENU_INSERT_CUBOID, OnMenuInsertCuboid)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsDoc construction/destruction

CTinyGraphicsDoc::CTinyGraphicsDoc()
{
	// TODO: add one-time construction code here
  world = new World3D();
  world->add(new Cuboid(20, 10, 10, Point3D(12, 12, -30)));
}

CTinyGraphicsDoc::~CTinyGraphicsDoc()
{
  delete world;
}

BOOL CTinyGraphicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsDoc serialization

void CTinyGraphicsDoc::Serialize(CArchive& ar)
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
// CTinyGraphicsDoc diagnostics

#ifdef _DEBUG
void CTinyGraphicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTinyGraphicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTinyGraphicsDoc commands

void CTinyGraphicsDoc::OnMenuInsertCuboid() 
{
	// TODO: Add your command handler code here
  CInsertCuboid dialog;
  int retVal = dialog.DoModal();
  if (retVal == IDOK) {
    world->add(new Cuboid(dialog.m_length, dialog.m_width, dialog.m_height,
                          Point3D(dialog.m_x, dialog.m_y, dialog.m_z)));
    UpdateAllViews(NULL);
  }
}
