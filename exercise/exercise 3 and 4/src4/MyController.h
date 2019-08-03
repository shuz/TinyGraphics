#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "ControllerBase.h"

struct World;

//////////////////////////////////////////////////////////////////////////
// 示例控制器

struct CMyController_impl;

class CMyController : public CControllerBase  
{
	DECLARE_DYNCREATE( CMyController );
	
public:
	CMyController();
	virtual ~CMyController();

	virtual void OnMouseMove( int x, int y );   // 鼠标移动时的回调函数
	virtual void OnLButtonDown( int x, int y );	// 鼠标左键按下时的回调函数
  virtual void OnLButtonUp( int x, int y );
  virtual void OnKeyPress( char key );        // 键盘按下时的回调函数
	virtual void OnPaint();                     // 窗口重绘时的回调函数
	virtual void OnSize(unsigned int nType,
                      int cx, int cy);        // 窗口改变大小时的回调函数
  virtual void OnTimer(unsigned int nIDEvent);
  virtual void OnCustomerMenu(unsigned int id);	// 菜单点击时的回调函数
	virtual void Init();                          // 初始化函数
	virtual char* GetName();                      // 提供对本控制器的描述

private:
  CMyController_impl *pImpl;
};

#endif // #ifndef MYCONTROLLER_H