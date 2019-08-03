   // ControllerBase.h: interface for the CControllerBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CONTROLLERBASE_H__07B138E4_F8C7_43AE_B222_2A9877F9EADE__INCLUDED_)
#define AFX_CONTROLLERBASE_H__07B138E4_F8C7_43AE_B222_2A9877F9EADE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CControllerBase : public CObject
{
	DECLARE_DYNCREATE( CControllerBase );

public:
	//////////////////////////////////////////////////////////////////////////
	// 界面功能
	
	// 画图，参数功能都显而易见，颜色可由RGB宏产生
	void DrawCircle( int x, int y, int radius, unsigned int color = RGB( 0, 0, 0 ), int width = 1 );
	void DrawText( int x, int y, char* text, unsigned int color = RGB( 0, 0, 0 ) );
	void DrawLine( int x1, int y1, int x2, int y2, unsigned int color = RGB( 0, 0, 0 ), int width = 1 );
	void DrawPixel( int x, int y, unsigned int color = RGB( 0, 0, 0 ), int size = 2 );

	// 刷新窗口中的内容，一般窗口的内容只有在被其它窗口遮挡后才刷新，使用这个函数主动刷新窗口
	void Refresh();
	// 弹出包含一条信息的对话框
	void MessageBox( char* pMessage );
	// 插入菜单项，其中第二个参数是要显示的菜单名称，第一个参数是菜单ID，以后的菜单命令要靠它为识别
	// 菜单ID必须从CGF_MENU_ID开始，目前的最大容量为100条，参见示例CMyController中的用法
	void InsertMenu( unsigned int id, char* pName );

	//////////////////////////////////////////////////////////////////////////
	// 重载用

	// 鼠标与键盘响应
	virtual void OnLButtonDown( int x, int y );
	virtual void OnRButtonDown( int x, int y );
	virtual void OnLButtonUp( int x, int y );
	virtual void OnRButtonUp( int x, int y );
	virtual void OnMouseMove( int x, int y );
	virtual void OnKeyPress( char key );

	// 窗口重绘时会调用该函数，所有的绘制操作都应在这里完成
	virtual void OnPaint();

	// 通过InsertMenu插入的菜单如果被用户点击，将会调用该函数。
	// 其中的参数就是插入菜单时所放入的id，请以此来判断是哪个菜单被点击了
	virtual void OnCustomerMenu( unsigned int id );

	// 显示在窗口标题栏上的文字
	virtual char* GetName();
	// 在程序启动时会调用此函数，目前的主要功能是在这里插入菜单项
	virtual void Init();

	//////////////////////////////////////////////////////////////////////////
	// 内部使用的变量
	// 如果不了解这个类的工作原理，请不要使用
	CView* m_pView;
	CDC * m_pDC;

	//////////////////////////////////////////////////////////////////////////
	// 构造/析构
	virtual ~CControllerBase();
protected:
	CControllerBase();
};

#endif // !defined(AFX_CONTROLLERBASE_H__07B138E4_F8C7_43AE_B222_2A9877F9EADE__INCLUDED_)
