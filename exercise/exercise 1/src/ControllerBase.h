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
	// ���湦��
	
	// ��ͼ���������ܶ��Զ��׼�����ɫ����RGB�����
	void DrawCircle( int x, int y, int radius, unsigned int color = RGB( 0, 0, 0 ), int width = 1 );
	void DrawText( int x, int y, char* text, unsigned int color = RGB( 0, 0, 0 ) );
	void DrawLine( int x1, int y1, int x2, int y2, unsigned int color = RGB( 0, 0, 0 ), int width = 1 );
	void DrawPixel( int x, int y, unsigned int color = RGB( 0, 0, 0 ), int size = 2 );

	// ˢ�´����е����ݣ�һ�㴰�ڵ�����ֻ���ڱ����������ڵ����ˢ�£�ʹ�������������ˢ�´���
	void Refresh();
	// ��������һ����Ϣ�ĶԻ���
	void MessageBox( char* pMessage );
	// ����˵�����еڶ���������Ҫ��ʾ�Ĳ˵����ƣ���һ�������ǲ˵�ID���Ժ�Ĳ˵�����Ҫ����Ϊʶ��
	// �˵�ID�����CGF_MENU_ID��ʼ��Ŀǰ���������Ϊ100�����μ�ʾ��CMyController�е��÷�
	void InsertMenu( unsigned int id, char* pName );

	//////////////////////////////////////////////////////////////////////////
	// ������

	// ����������Ӧ
	virtual void OnLButtonDown( int x, int y );
	virtual void OnRButtonDown( int x, int y );
	virtual void OnLButtonUp( int x, int y );
	virtual void OnRButtonUp( int x, int y );
	virtual void OnMouseMove( int x, int y );
	virtual void OnKeyPress( char key );

	// �����ػ�ʱ����øú��������еĻ��Ʋ�����Ӧ���������
	virtual void OnPaint();

	// ͨ��InsertMenu����Ĳ˵�������û������������øú�����
	// ���еĲ������ǲ���˵�ʱ�������id�����Դ����ж����ĸ��˵��������
	virtual void OnCustomerMenu( unsigned int id );

	// ��ʾ�ڴ��ڱ������ϵ�����
	virtual char* GetName();
	// �ڳ�������ʱ����ô˺�����Ŀǰ����Ҫ���������������˵���
	virtual void Init();

	//////////////////////////////////////////////////////////////////////////
	// �ڲ�ʹ�õı���
	// ������˽������Ĺ���ԭ���벻Ҫʹ��
	CView* m_pView;
	CDC * m_pDC;

	//////////////////////////////////////////////////////////////////////////
	// ����/����
	virtual ~CControllerBase();
protected:
	CControllerBase();
};

#endif // !defined(AFX_CONTROLLERBASE_H__07B138E4_F8C7_43AE_B222_2A9877F9EADE__INCLUDED_)
