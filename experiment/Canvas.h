#pragma once
#include "quad.h"

class Quadrangle;

// Canvas ��ͼ

class Canvas : public CScrollView
{
	//ʹ��DECLARE_DYNCREATE�����ʹÿ��CObject��������Ķ����������ʱ��̬����������
	DECLARE_DYNCREATE(Canvas)

	//protected:
public:
	Canvas();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~Canvas();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��Ƹ���ͼ
	virtual void OnInitialUpdate();     // �����ĵ�һ��

	DECLARE_MESSAGE_MAP()
public:
	static Canvas * pCanvas;
	static void drawQuad(const Quadrangle *quad);
	static bool isLearning;

	bool toggleMode(void);
	double area;

private:
	enum _QUAD_ { para = 0, rect, sqr, diam, trap };
	typedef pair<string, _QUAD_> KV;
	map<string, _QUAD_> quadMap;
};
