// Canvas.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "experiment.h"
#include "Canvas.h"
#include"quad.h"
#include"diam.h"
#include"list.h"
#include"para.h"
#include"rect.h"
#include"squa.h"
#include"trap.h"
//{{ �ⲿ˵����ӵ�����
extern List<QUADPTR> list;

//}}

// Canvas

Canvas * Canvas::pCanvas = NULL;
bool Canvas::isLearning = false;

IMPLEMENT_DYNCREATE(Canvas, CScrollView)

//���캯��
Canvas::Canvas()
{
	pCanvas = this;

	//��ö��ֵ���ַ����Բ����ֵ���
	quadMap.insert(KV("Parallelogram", para));
	quadMap.insert(KV("Rectangle", rect));
	quadMap.insert(KV("Square", sqr));
	quadMap.insert(KV("Diamond", diam));
	quadMap.insert(KV("Trapezoid", trap));
}

//�����ַ����̶���ʽ
static CString formatString[] =
{
	_T("��=%.1lf, ��=%.1lf, ���="),
	_T("�Խ���1=%.1lf, �Խ���2=%.1lf, ���="),
	_T("�ϵױ�=%.1lf, �µױ�=%.1lf, ��=%.1lf, ���=")
};

//��������
Canvas::~Canvas(){}


BEGIN_MESSAGE_MAP(Canvas, CScrollView)

END_MESSAGE_MAP()


// Canvas ��ͼ

void Canvas::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	//CSize sizeTotal;
	// TODO: �������ͼ�ĺϼƴ�С
	//sizeTotal.cx = sizeTotal.cy = 100;
	//SetScrollSizes(MM_TEXT, sizeTotal);
}

//������������
union _QUADPTR_
{
	Quadrangle *q;
	Para *p;
	Rect *r;
	Diamond *d;
	Square *s;
	Trapezoid *t;
};

//����һ������
void Canvas::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: �ڴ���ӻ��ƴ���

	CRect rect;
	GetClientRect(&rect);

	CBrush br(RGB(220, 200, 170));
	CBrush * oldBrush = reinterpret_cast<CBrush*>(pDC->SelectObject(&br));

	int xc, yc;
	int vw = rect.Width(), vh = rect.Height();
	int sw = static_cast<int>(vw * 0.75 / 2.0), sh = static_cast<int>(vh * 0.75 / 2.0);
	//���������ĸ�����
	//ƽ���ı���
	//����
	//������
	//����
	//����
	SIZE ad[5][4] =
	{ { { -sw + 50, -sh },{ sw + 50, -sh },{ sw - 50, sh },{ -sw - 50, sh } },
	{ { -sw, -sh },{ sw, -sh },{ sw, sh },{ -sw, sh } },
	{ { -sh, -sh },{ sh, -sh },{ sh, sh },{ -sh, sh } },
	{ { 0, -sh },{ sw, 0 },{ 0, sh },{ -sw, 0 } },
	{ { -sw + 120, -sh },{ sw - 80, -sh },{ sw, sh },{ -sw, sh } },
	};

	double ratio = 1.0;
	int yOffset = 120;
	if (isLearning)
	{
		xc = vw / 2;
		yc = vh / 2;
	}
	else
	{
		xc = 80;
		yc = 60;
		ratio = 0.3;
	}

	//�����ĸ�����
	POINT vert[4];

	int shape;
	size_t i, begin = 0, end = list.size();
	if (isLearning) begin = end - 1;
	_QUADPTR_ quad;
	string name;
	CString msg, msg2;
	for (i = begin; i <= end; ++i)
	{
		quad.q = list[i];
		name = quad.q->what();
		area = quad.q->area();

		//�����������ƶ�Ӧ��ö�ٱ���ֵ
		shape = quadMap[name];
		//���ݲ�ͬ�������������������ַ���
		switch (shape)
		{
		case trap:
			msg.Format(formatString[2], quad.t->Width1(), quad.t->Width2(), quad.t->Height());
			break;

		case diam:
			msg.Format(formatString[1], quad.d->Width1(), quad.d->Width2());
			break;

		default:
			msg.Format(formatString[0], quad.p->Width(), quad.p->Height());
		}

		if (isLearning) msg2 = _T("��");
		else msg2.Format(_T("%.1lf"), area);
		msg += msg2;

		for (int i = 0; i < 4; ++i)
		{
			vert[i].x = static_cast<int>(xc + (ad[shape][i].cx * ratio));
			vert[i].y = static_cast<int>(yc + (ad[shape][i].cy * ratio));
		}

		int tx, ty;
		if (isLearning)
		{
			tx = xc - sw;
			ty = yc + sh + 8;
		}
		else
		{
			CBrush br(RGB(240, 240, 240));
			CBrush *oldbr = reinterpret_cast<CBrush *>(pDC->SelectObject(&br));
			CPen *oldpen = reinterpret_cast<CPen *>(pDC->SelectStockObject(NULL_PEN));
			pDC->Rectangle(xc - 80, yc - 50, xc + 600, yc + 50);
			pDC->SelectObject(oldbr);
			pDC->SelectObject(oldpen);

			tx = xc + yOffset - 24;
			ty = yc - 8;
			yc += yOffset;
		}

		pDC->Polygon(vert, 4);
		pDC->SetBkMode(TRANSPARENT);
		pDC->TextOutW(tx, ty, msg);
	}

	pDC->SelectObject(oldBrush);
}

//???
void Canvas::drawQuad(const Quadrangle *quad)
{
	if (isLearning) pCanvas->Invalidate();
}

//ת��ѧϰģʽ���ѧϰģʽ
bool Canvas::toggleMode(void)
{
	return isLearning = !isLearning;
}

// Canvas ���

#ifdef _DEBUG
void Canvas::AssertValid() const
{
	CScrollView::AssertValid();
}

#ifndef _WIN32_WCE
void Canvas::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}
#endif
#endif //_DEBUG

