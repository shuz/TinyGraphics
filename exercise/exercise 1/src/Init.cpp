#include "stdafx.h"
#include "CGFramework.h"

#include "MyController.h"

//////////////////////////////////////////////////////////////////////////
// 在这里注册自己的控制器
void CGFInit()
{
	CGFRegisterController( RUNTIME_CLASS( CMyController ) );
}