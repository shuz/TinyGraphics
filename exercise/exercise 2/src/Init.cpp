#include "stdafx.h"
#include "CGFramework.h"

#include "MyController.h"

//////////////////////////////////////////////////////////////////////////
// ������ע���Լ��Ŀ�����
void CGFInit()
{
	CGFRegisterController( RUNTIME_CLASS( CMyController ) );
}