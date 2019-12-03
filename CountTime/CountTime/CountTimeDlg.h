
// CountTimeDlg.h : 头文件
//

#pragma once
#include<time.h>
#include "afxwin.h"
#include "afxdtctl.h"
#include "afxcmn.h"

#define CLOCKS_PER_HOUR 3600
#define CLOCKS_PER_MINT 60

#ifndef ODD_NUMBER
#define ODD_NUMBER(a) a%2 ==0?a+1:a
#endif // !ODD_NUMBER
#ifndef EVEN_NUMBER
#define EVEN_NUMBER(a) a%2 ==0?a:a+1
#endif // !ODD_NUMBER

// CCountTimeDlg 对话框
class CCountTimeDlg : public CDialogEx
{
// 构造
public:
	CCountTimeDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_COUNTTIME_DIALOG };
#endif

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	clock_t m_start;
	clock_t m_end;
	bool m_count_flag;
	bool m_countdown_flag;
	bool m_run_flag;
	virtual void OnCancel();
	virtual void OnOK();
	CListBox m_count_list;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CDateTimeCtrl m_countdown_time;
	clock_t m_cd_start;
	clock_t m_cd_end;
	afx_msg void OnBnClickedButton4();
	int m_countdown_count;
	void SetCStringtoDlg(int Dlgitem, CString str);
	void ResetButtonState();
	CProgressCtrl m_progress_cd;
	HANDLE m_thred_count;
	DWORD m_thred_count_dw;
	CWinThread* m_thred_countdown;
	afx_msg void OnBnClickedButton6();
};
