#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "ControllerBase.h"

struct World;

//////////////////////////////////////////////////////////////////////////
// ʾ��������

struct CMyController_impl;

class CMyController : public CControllerBase  
{
	DECLARE_DYNCREATE( CMyController );
	
public:
	CMyController();
	virtual ~CMyController();

	virtual void OnMouseMove( int x, int y );   // ����ƶ�ʱ�Ļص�����
	virtual void OnLButtonDown( int x, int y );	// ����������ʱ�Ļص�����
  virtual void OnLButtonUp( int x, int y );
  virtual void OnKeyPress( char key );        // ���̰���ʱ�Ļص�����
	virtual void OnPaint();                     // �����ػ�ʱ�Ļص�����
	virtual void OnSize(unsigned int nType,
                      int cx, int cy);        // ���ڸı��Сʱ�Ļص�����
  virtual void OnTimer(unsigned int nIDEvent);
  virtual void OnCustomerMenu(unsigned int id);	// �˵����ʱ�Ļص�����
	virtual void Init();                          // ��ʼ������
	virtual char* GetName();                      // �ṩ�Ա�������������

private:
  CMyController_impl *pImpl;
};

#endif // #ifndef MYCONTROLLER_H