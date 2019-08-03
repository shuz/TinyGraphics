     // ControllerBase.cpp: implementation of the CControllerBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CGFramework.h"
#include "ControllerBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


IMPLEMENT_DYNCREATE( CControllerBase, CObject );

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CControllerBase::CControllerBase()
{

}

CControllerBase::~CControllerBase()
{

}

//////////////////////////////////////////////////////////////////////////
// 界面功能

void CControllerBase::DrawPixel(int x, int y, unsigned int color, int size )
{
	if( m_pDC == NULL )
		return;

	if( size == 1 )
	{
		m_pDC->SetPixel( x, y, color );
	}
	else
	{
		size = ( size + 1 ) / 2;
		CPen newPen( PS_SOLID, 1, color );
		CPen *oldPen = m_pDC->SelectObject( &newPen );
		CBrush newBrush( color );
		CBrush *oldBrush = m_pDC->SelectObject( &newBrush );
		m_pDC->Ellipse( x - size, y - size, x + size, y + size );
		m_pDC->SelectObject( oldPen );
		m_pDC->SelectObject( oldBrush );
	}
}

void CControllerBase::DrawLine(int x1, int y1, int x2, int y2, unsigned int color, int width )
{
	if( m_pDC == NULL )
		return;

	CPen newPen( PS_SOLID, width, color );
	CPen *oldPen = m_pDC->SelectObject( &newPen );
	m_pDC->MoveTo( x1, y1 );
	m_pDC->LineTo( x2, y2 );
	m_pDC->SelectObject( oldPen );
}

void CControllerBase::DrawText(int x, int y, char *text, unsigned int color)
{
	if( m_pDC == NULL )
		return;

	m_pDC->SetTextColor( color );
	m_pDC->TextOut( x, y, text );
}

void CControllerBase::DrawCircle(int x, int y, int radius, unsigned int color, int width )
{
	if( m_pDC == NULL )
		return;

	CPen newPen( PS_SOLID, width, color );
	CPen *oldPen = m_pDC->SelectObject( &newPen );
	m_pDC->Ellipse( x - radius, y - radius, x + radius, y + radius );
	m_pDC->SelectObject( oldPen );
}

//////////////////////////////////////////////////////////////////////////

void CControllerBase::Refresh()
{
	m_pView->Invalidate();
}

void CControllerBase::MessageBox(char *pMessage)
{
	m_pView->MessageBox( pMessage );
}

void CControllerBase::InsertMenu(unsigned int id, char *pName)
{
	CMenu *pMainMenu = AfxGetMainWnd()->GetMenu();
	pMainMenu->GetSubMenu(3)->InsertMenu( 0, MF_STRING, id, pName );
}

//////////////////////////////////////////////////////////////////////////
// 重载用

void CControllerBase::OnLButtonDown(int x, int y)
{

}

void CControllerBase::OnRButtonDown(int x, int y)
{

}

void CControllerBase::OnLButtonUp(int x, int y)
{

}

void CControllerBase::OnRButtonUp(int x, int y)
{
	
}

void CControllerBase::OnMouseMove(int x, int y)
{

}

void CControllerBase::OnKeyPress(char key)
{

}

//////////////////////////////////////////////////////////////////////////

char* CControllerBase::GetName()
{
	return "基类控制器";
}

void CControllerBase::Init()
{

}

void CControllerBase::OnCustomerMenu(unsigned int id)
{

}

void CControllerBase::OnPaint()
{
	DrawText( 20, 20, "这是基类控制器，供子类继承，不提供任何功能！", RGB( 255, 0, 0 ) );
}

