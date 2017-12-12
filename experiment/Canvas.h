#pragma once
#include "quad.h"

class Quadrangle;

// Canvas 视图

class Canvas : public CScrollView
{
	//使用DECLARE_DYNCREATE宏可以使每个CObject的派生类的对象具有运行时动态创建的能力
	DECLARE_DYNCREATE(Canvas)

	//protected:
public:
	Canvas();           // 动态创建所使用的受保护的构造函数
	virtual ~Canvas();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制该视图
	virtual void OnInitialUpdate();     // 构造后的第一次

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
