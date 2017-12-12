// experimentDlg.h : 头文件
//

#pragma once
#include "canvas.h"


// CexperimentDlg 对话框
class CexperimentDlg : public CDialogEx
{
	// 构造
public:
	CexperimentDlg(CWnd* pParent = NULL);	// 标准构造函数

											// 对话框数据
	enum { IDD = IDD_EXPERIMENT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


														// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
