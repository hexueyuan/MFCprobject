// experimentDlg.cpp : ʵ���ļ�
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

//{{ ȫ��˵�����������
List<QUADPTR> list;
//}}
void access(const QUADPTR& quad)
{
	quad->draw();
}
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

														// ʵ��
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


// CexperimentDlg �Ի���




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
	//�ӱ༭���л�ȡanswer��ֵ
	DDX_Text(pDX, IDC_EDIT_ANSWER, answer);

	//����answer�����䷶Χ
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


// CexperimentDlg ��Ϣ�������

BOOL CexperimentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	pCanvas = new Canvas();

	//�������������
	pCanvas->Create(NULL, NULL, WS_BORDER, CRect(20, 20, 580, 420), this, 9999);
	pCanvas->SetScrollSizes(MM_TEXT, CSize(540, 600));
	pCanvas->ShowWindow(TRUE);

	answer = 10.0;
	UpdateData(FALSE);

	//�����������
	srand(unsigned(time(NULL)));

	//{{ ����㻹�������ĳ�ʼ��������Ѵ�����ڷ���//{{��//}}֮��
	//��ĳ�ʼ�������������
	//}}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CexperimentDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CexperimentDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//�رմ��ڣ���������
void CexperimentDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}

//�����һ�ⰴťʱ����һ���µ�����
void CexperimentDlg::OnClickedButtonNext()
{
	if (pCanvas->isLearning)
	{
		//�������һ�����岢����
		QUADPTR quad = createAquad();
		quad->draw();

		lastDone = false;
	}
	//��ȡ��һ�ⰴť�ľ��
	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
	//��δ������ȷ����ǰ�����ܵ����һ��
	p->EnableWindow(FALSE);
}

//�����ʼѧϰ��ť
void CexperimentDlg::OnClickedButtonStop()
{
	//��ʼѧϰ
	//�л���ǰģʽ
	pCanvas->toggleMode();

	BOOL enable = TRUE;

	//��ô����е�һ����ʼѧϰ/��ͣѧϰ��ť�ľ��
	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_STOP);
	CString s;
	//�ӵ�һ����ť�л�ȡ�����ַ���
	p->GetWindowText(s);
	if (s == "��ʼ")
	{
		p->SetWindowText(_T("��ϰ"));
		//��һ��
		OnClickedButtonNext();
	}
	else
	{
		p->SetWindowText(_T("��ʼ"));

		//��ǰ��ʾ����Ŀ�Ƿ�����𰸣���û�У���ɾ���������еĶ�Ӧ����
		if (!lastDone) { list.pop_back(); }
		//����������ĳ�������(����Ϊ��������*120�����Ϊ500)
		if (list.size() != 0)
		{
			pCanvas->SetScrollSizes(MM_TEXT, CSize(500, list.size() * 120));
		}

		if (list.size() == 0)
		{
			//��û������ʱ����ʾû��ѧϰ��
			this->MessageBox(_T("����û��ѧϰ"), _T("�ı���ѧϰϵͳ"), MB_ICONSTOP);
		}
		else
		{
			//��������������ʱ�����������������
			list.traverse(access);
		}
		pCanvas->Invalidate();
		enable = FALSE;
		//��ȡ�ڶ�����һ�ⰴť�ľ��
		CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
		//ʹ�����ťΪ���ɵ��,����û������֮ǰ������һ��
		p->EnableWindow(FALSE);
	}

	//��ȡ�ύ��ť���
	p = (CButton *)GetDlgItem(IDC_BUTTON_SUBMIT);
	//���ÿ�������
	p->EnableWindow(enable);
	//��ȡ�༭��ľ��
	CEdit *q = (CEdit *)GetDlgItem(IDC_EDIT_ANSWER);
	//���ñ༭��Ŀ�������
	q->EnableWindow(enable);
}

//����ύ�𰸰�ť
void CexperimentDlg::OnClickedButtonSubmit()
{
	UpdateData();

	BOOL enable = TRUE;
	double ref = static_cast<double>(pCanvas->area * 10);
	double area = static_cast<double>(answer * 10);
	if (area==ref)
	{
		result = _T("����ȷ");
		lastDone = true;
	}
	else
	{
		result = _T("�𰸴���");
		enable = FALSE;
	}
	UpdateData(FALSE);

	CButton *p = (CButton *)GetDlgItem(IDC_BUTTON_NEXT);
	p->EnableWindow(enable);
}


QUADPTR CexperimentDlg::createAquad(void)
{
	//���������������ĳ������Ĵ���
	//��������ķ�ʽ����ƽ���ı��Ρ����Ρ����Ρ����κ�������֮һ
	//�������������Ҳ��������ɵ�
	//����һ���������ָ�뱣�浽�б���
	//�����ķ���ֵ�����ɵ������ָ��
	QUADPTR q;
	int num = rand() % 5;
	int j = 0, k = 0;
	j = (rand() % 9) + 1;
	//�����������ֵ����֤�䲻���
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
	// TODO: �ڴ����ר�ô����/����û���

	//if (wParam == 1 || wParam == 2) return FALSE;

	return CDialogEx::OnCommand(wParam, lParam);
}

