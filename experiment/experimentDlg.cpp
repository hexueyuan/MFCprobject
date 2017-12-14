// experimentDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "experiment.h"
#include "experimentDlg.h"
#include "afxdialogex.h"
#include"quad.h"
#include"diam.h"
#include"list.h"
#include"para.h"
#include"rect.h"
#include"squa.h"
#include"trap.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//{{ 全局说明添加在这里
List<QUADPTR> list;
//}}
void access(const QUADPTR& quad)
{
	quad->draw();
}
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

														// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CexperimentDlg 对话框




CexperimentDlg::CexperimentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CexperimentDlg::IDD, pParent)
	, lastDone(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	answer = 0.0;
	result = _T("");
}

void CexperimentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//从编辑框中获取answer的值
	DDX_Text(pDX, IDC_EDIT_ANSWER, answer);

	//定义answer的区间范围
	DDV_MinMaxDouble(pDX, answer, 1, 5000);

	DDX_Text(pDX, IDC_EDIT_RESULT, result);
	DDV_MaxChars(pDX, result, 30);
}

BEGIN_MESSAGE_MAP(CexperimentDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CexperimentDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CexperimentDlg::OnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_STOP, &CexperimentDlg::OnClickedButtonStop)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CexperimentDlg::OnClickedButtonSubmit)
END_MESSAGE_MAP()


// CexperimentDlg 消息处理程序

BOOL CexperimentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	pCanvas = new Canvas();

	//设置输出背景框
	pCanvas->Create(NULL, NULL, WS_BORDER, CRect(20, 20, 580, 420), this, 9999);
	pCanvas->SetScrollSizes(MM_TEXT, CSize(540, 600));
	pCanvas->ShowWindow(TRUE);

	answer = 10.0;
	UpdateData(FALSE);

	//设置随机种子
	srand(unsigned(time(NULL)));

	//{{ 如果你还有其他的初始化需求，请把代码放在符号//{{和//}}之间
	//你的初始化代码放在这里
	//}}

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CexperimentDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CexperimentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CexperimentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//关闭窗口，结束程序
void CexperimentDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

//点击下一题按钮时生成一个新的形体
void CexperimentDlg::OnClickedButtonNext()
{
	if (pCanvas->isLearning)
	{
		//随机创建一个形体并绘制
		QUADPTR quad = createAquad();
		quad->draw();

		lastDone = false;
	}
	//获取下一题按钮的句柄
	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
	//在未输入正确答案以前，不能点击下一题
	p->EnableWindow(FALSE);
}

//点击开始学习按钮
void CexperimentDlg::OnClickedButtonStop()
{
	//开始学习
	//切换当前模式
	pCanvas->toggleMode();

	BOOL enable = TRUE;

	//获得窗口中第一个开始学习/暂停学习按钮的句柄
	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
	CString s;
	//从第一个按钮中获取描述字符串
	p->GetWindowText(s);
	if (s == "开始")
	{
		p->SetWindowText(_T("复习"));
		//下一题
		OnClickedButtonNext();
	}
	else
	{
		p->SetWindowText(_T("开始"));

		//当前显示的题目是否输入答案，若没有，则删除在链表中的对应形体
		if (!lastDone) { list.pop_back(); }
		//设置下拉框的长度与宽度(长度为形体数量*120，宽度为500)
		if (list.size() != 0)
		{
			pCanvas->SetScrollSizes(MM_TEXT, CSize(500, list.size() * 120));
		}

		if (list.size() == 0)
		{
			//当没有形体时，表示没有学习过
			this->MessageBox(_T("您还没有学习"), _T("四边形学习系统"), MB_ICONSTOP);
		}
		else
		{
			//当有链表中形体时，遍历输出所有形体
			list.traverse(access);
		}
		pCanvas->Invalidate();
		enable = FALSE;
		//获取第二个下一题按钮的句柄
		CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
		//使这个按钮为不可点击,即答案没有输入之前不可下一题
		p->EnableWindow(FALSE);
	}

	//获取提交按钮句柄
	p = (CButton *)GetDlgItem(IDC_BUTTON_SUBMIT);
	//设置可用属性
	p->EnableWindow(enable);
	//获取编辑框的句柄
	CEdit *q = (CEdit *)GetDlgItem(IDC_EDIT_ANSWER);
	//设置编辑框的可用属性
	q->EnableWindow(enable);
}

//点击提交答案按钮
void CexperimentDlg::OnClickedButtonSubmit()
{
	UpdateData();

	BOOL enable = TRUE;
	double ref = static_cast<double>(pCanvas->area * 10);
	double area = static_cast<double>(answer * 10);
	if (area==ref)
	{
		result = _T("答案正确");
		lastDone = true;
	}
	else
	{
		result = _T("答案错误");
		enable = FALSE;
	}
	UpdateData(FALSE);

	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
	p->EnableWindow(enable);
}


QUADPTR CexperimentDlg::createAquad(void)
{
	//请在这里添加生成某个形体的代码
	//采用随机的方式生成平行四边形、梯形、矩形、菱形和正方形之一
	//形体的特征数据也是随机生成的
	//生成一个形体后将其指针保存到列表中
	//函数的返回值是生成的形体的指针
	QUADPTR q;
	int num = rand() % 5;
	int j = 0, k = 0;
	j = (rand() % 9) + 1;
	//随机两个特征值并保证其不相等
	while (j == k || k == 0) k = (rand() % 9) + 1;
	switch (num) {
	case 0:
		q = new Para(j, k);
		break;
	case 1:
		q = new Rect(j, k);
		break;
	case 2:
		q = new Square(j);
		break;
	case 3:
		q = new Diamond(j, k);
		break;
	case 4:
		q = new Trapezoid(num, j, k);
		break;
	}
	list += q;
	return q;
}



BOOL CexperimentDlg::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类

	//if (wParam == 1 || wParam == 2) return FALSE;

	return CDialogEx::OnCommand(wParam, lParam);
}

