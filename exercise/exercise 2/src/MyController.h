#ifndef MYCONTROLLER_H
#define MYCONTROLLER_H

#include "ControllerBase.h"
#include <vector>

struct Point {
  int x, y;
  Point() {}
  Point(int xx, int yy) : x(xx), y(yy) {}
};

struct Line {
  Point begin, end;
  unsigned int color;
  bool visible;
  Line() 
    : color(RGB(0, 0, 0)) {}
  Line(Point b, Point e, unsigned int c)
    : begin(b), end(e), color(c), visible(true) {}
};


//////////////////////////////////////////////////////////////////////////
// ʾ��������
class CMyController : public CControllerBase  
{
	DECLARE_DYNCREATE( CMyController );
	
public:
	CMyController();
	virtual ~CMyController();

	virtual void OnMouseMove( int x, int y );   // ����ƶ�ʱ�Ļص�����
	virtual void OnLButtonDown( int x, int y );	// ����������ʱ�Ļص�����
	virtual void OnKeyPress( char key );        // ���̰���ʱ�Ļص�����
	virtual void OnPaint();                     // �����ػ�ʱ�Ļص�����
	virtual void OnCustomerMenu(unsigned int id);	// �˵����ʱ�Ļص�����
	virtual void Init();                          // ��ʼ������
	virtual char* GetName();                      // �ṩ�Ա�������������

private:
	std::vector<Line> m_lines;
  int m_curMenu;
  bool m_isDrawing;
  Line m_clipBorder[4];

  void Clip(Line& line);
  void DrawClipBorder();
	void AddPixelWithGrid(int x, int y);
};

#endif // #ifndef MYCONTROLLER_H