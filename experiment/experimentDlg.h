// experimentDlg.h : ͷ�ļ�
//

#pragma once
#include "canvas.h"


// CexperimentDlg �Ի���
class CexperimentDlg : public CDialogEx
{
	// ����
public:
	CexperimentDlg(CWnd* pParent = NULL);	// ��׼���캯��

											// �Ի�������
	enum { IDD = IDD_EXPERIMENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


														// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	Canvas *pCanvas;
	afx_msg void OnBnClickedOk();
	double answer;
	CString result;
	afx_msg void OnClickedButtonNext();
	afx_msg void OnClickedButtonStop();
	afx_msg void OnClickedButtonSubmit();

public:
	QUADPTR createAquad(void);
private:
	bool lastDone;

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
