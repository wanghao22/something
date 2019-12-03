
// CountTimeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CountTime.h"
#include "CountTimeDlg.h"
#include "afxdialogex.h"

//#include <DXGI.h>//显卡用

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

UINT CountThread(LPVOID pParam)
{
	CCountTimeDlg *pWnd = (CCountTimeDlg*)pParam;
	while (pWnd->m_run_flag)
	{
		while (pWnd->m_count_flag)
		{
			pWnd->m_end = clock();
			CString result;
			double temp = pWnd->m_end - pWnd->m_start;
			int temp1 = temp;
			int temp_s = temp / CLOCKS_PER_SEC;
			int hour, mint, secend, sun_secend;
			hour = temp_s / CLOCKS_PER_HOUR;
			temp_s = temp_s % CLOCKS_PER_HOUR;
			mint = temp_s / CLOCKS_PER_MINT;
			secend = temp_s % CLOCKS_PER_MINT;
			sun_secend = (temp1 % 1000);
			result.Format(L"%2d", hour);
			pWnd->SetCStringtoDlg(IDC_HOUR, result);
			result.Format(L"%2d", mint);
			pWnd->SetCStringtoDlg(IDC_MINT, result);
			result.Format(L"%2d", secend);
			pWnd->SetCStringtoDlg(IDC_SECND, result);
			result.Format(L"%3d", sun_secend);
			pWnd->SetCStringtoDlg(IDC_SUB_SECND, result);
		}
		Sleep(10);
	}
	return 0;
}

UINT CountThread_(LPVOID pParam)
{
	CCountTimeDlg *pWnd = (CCountTimeDlg*)pParam;
	while (pWnd->m_count_flag)
	{
		pWnd->m_end = clock();
		CString result;
		double temp = pWnd->m_end - pWnd->m_start;
		int temp1 = temp;
		int temp_s = temp / CLOCKS_PER_SEC;
		int hour, mint, secend, sun_secend;
		hour = temp_s / CLOCKS_PER_HOUR;
		temp_s = temp_s % CLOCKS_PER_HOUR;
		mint = temp_s / CLOCKS_PER_MINT;
		secend = temp_s % CLOCKS_PER_MINT;
		sun_secend = (temp1 % 1000);
		result.Format(L"%2d", hour);
		pWnd->SetCStringtoDlg(IDC_HOUR, result);
		result.Format(L"%2d", mint);
		pWnd->SetCStringtoDlg(IDC_MINT, result);
		result.Format(L"%2d", secend);
		pWnd->SetCStringtoDlg(IDC_SECND, result);
		result.Format(L"%3d", sun_secend);
		pWnd->SetCStringtoDlg(IDC_SUB_SECND, result);
	}
	return 0;
}

DWORD WINAPI CountThread__(LPVOID pParam)
{
	CCountTimeDlg *pWnd = (CCountTimeDlg*)pParam;
	while (pWnd->m_count_flag)
	{
		pWnd->m_end = clock();
		CString result;
		double temp = pWnd->m_end - pWnd->m_start;
		int temp1 = temp;
		int temp_s = temp / CLOCKS_PER_SEC;
		int hour, mint, secend, sun_secend;
		hour = temp_s / CLOCKS_PER_HOUR;
		temp_s = temp_s % CLOCKS_PER_HOUR;
		mint = temp_s / CLOCKS_PER_MINT;
		secend = temp_s % CLOCKS_PER_MINT;
		sun_secend = (temp1 % 1000);
		result.Format(L"%2d", hour);
		pWnd->SetCStringtoDlg(IDC_HOUR, result);
		result.Format(L"%2d", mint);
		pWnd->SetCStringtoDlg(IDC_MINT, result);
		result.Format(L"%2d", secend);
		pWnd->SetCStringtoDlg(IDC_SECND, result);
		result.Format(L"%3d", sun_secend);
		pWnd->SetCStringtoDlg(IDC_SUB_SECND, result);
	}
	return 0;
}

UINT CountThread2(LPVOID pParam)
{
	CCountTimeDlg *pWnd = (CCountTimeDlg*)pParam;
	while (pWnd->m_run_flag)
	{
		while (pWnd->m_countdown_flag)
		{
			//TODO:
			pWnd->m_cd_end = clock();
			double temp = pWnd->m_cd_end - pWnd->m_cd_start;
			double tc = temp / pWnd->m_countdown_count;
			pWnd->m_progress_cd.SetPos(tc * 100);
			if (temp >= pWnd->m_countdown_count)
			{
				AfxMessageBox(L"时间到！");
				pWnd->m_countdown_flag = false;
				pWnd->m_progress_cd.SetPos(0);
				pWnd->m_progress_cd.EnableWindow(false);
				pWnd->m_countdown_time.EnableWindow(true);
				pWnd->ResetButtonState();
			}
		}
		Sleep(10);
	}
	return 0;
}

UINT CountThread2_(LPVOID pParam)
{
	CCountTimeDlg *pWnd = (CCountTimeDlg*)pParam;
	while (pWnd->m_countdown_flag)
	{
		//TODO:
		pWnd->m_cd_end = clock();
		double temp = pWnd->m_cd_end - pWnd->m_cd_start;
		double tc = temp / pWnd->m_countdown_count;
		pWnd->m_progress_cd.SetPos(tc * 100);
		if (temp >= pWnd->m_countdown_count)
		{
			AfxMessageBox(L"时间到！");
			pWnd->m_countdown_flag = false;
			pWnd->m_progress_cd.SetPos(0);
			pWnd->m_progress_cd.EnableWindow(false);
			pWnd->m_countdown_time.EnableWindow(true);
			pWnd->ResetButtonState();
		}
	}
	return 0;
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCountTimeDlg 对话框



CCountTimeDlg::CCountTimeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_COUNTTIME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCountTimeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_count_list);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_countdown_time);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress_cd);
}

BEGIN_MESSAGE_MAP(CCountTimeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCountTimeDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCountTimeDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CCountTimeDlg::OnBnClickedButton3)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON4, &CCountTimeDlg::OnBnClickedButton4)
//	ON_BN_CLICKED(IDC_MFCLINK1, &CCountTimeDlg::OnBnClickedMfclink1)
ON_BN_CLICKED(IDC_BUTTON6, &CCountTimeDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CCountTimeDlg 消息处理程序

BOOL CCountTimeDlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	m_count_flag = false;
	m_countdown_flag = false;
	m_run_flag = true;
	//AfxBeginThread(CountThread, this);
	//AfxBeginThread(CountThread2, this);
	SYSTEMTIME time;
	GetLocalTime(&time);
	time.wHour = 0;
	time.wMinute = 2;
	time.wSecond = 0;
	time.wMilliseconds = 0;
	m_countdown_time.SetTime(time);
	m_progress_cd.SetRange(0, 100);
	m_progress_cd.EnableWindow(false);
	//SetTimer(1, 3000, NULL);  //第一个参数可以自己设置是定时器的ID，第二个参数是间隔时间（毫秒为单位的）

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCountTimeDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCountTimeDlg::OnPaint()
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
HCURSOR CCountTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//开始
void CCountTimeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_count_flag)
	{
		m_start = clock();
		m_count_flag = true;
		while (m_count_list.GetCount()!=0)
			m_count_list.DeleteString(0);
		//m_thred_count = AfxBeginThread(CountThread_, this);
		m_thred_count = ::CreateThread(NULL, 0, CountThread__, (LPVOID)this, 0, &m_thred_count_dw);
	}
}

//计时
void CCountTimeDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_count_flag)
	{
		m_end = clock();
		CString result;
		double temp = m_end - m_start;
		int temp1 = temp;
		int temp_s = temp / CLOCKS_PER_SEC;
		int hour, mint, secend, sun_secend;
		hour = temp_s / CLOCKS_PER_HOUR;
		temp_s = temp_s % CLOCKS_PER_HOUR;
		mint = temp_s / CLOCKS_PER_MINT;
		secend = temp_s % CLOCKS_PER_MINT;
		sun_secend = (temp1 % 1000);
		result.Format(L"%2d:%2d:%2d.%3d", hour, mint, secend, sun_secend);
		m_count_list.AddString(result);
	}
	/*if (m_countdown_flag)
	{
		TerminateThread(m_thred_countdown->m_hThread, m_thred_countdown->m_nThreadID);
	}*/
}

//结束
void CCountTimeDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	if (m_count_flag)
	{
		m_count_flag = false;
		//结束线程
		//TerminateThread(m_thred_count, m_thred_count_dw);
	}
	else
	{
		SetCStringtoDlg(IDC_HOUR, L"00");
		SetCStringtoDlg(IDC_MINT, L"00");
		SetCStringtoDlg(IDC_SECND, L"00");
		SetCStringtoDlg(IDC_SUB_SECND, L"000");
	}
}


void CCountTimeDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	KillTimer(1);
	m_count_flag = false;
	m_countdown_flag = false;
	m_run_flag = false;
	CDialogEx::OnCancel();
}


void CCountTimeDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	KillTimer(1);
	m_count_flag = false;
	m_countdown_flag = false;
	m_run_flag = false;
	CDialogEx::OnOK();
}


void CCountTimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nIDEvent == 1)
	{
		TRACE(L"1111");
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CCountTimeDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_countdown_flag)
	{
		SYSTEMTIME time;
		m_cd_start = clock();
		m_countdown_time.GetTime(&time);
		m_countdown_count = time.wHour * 60 * 60 * 1000;
		m_countdown_count += time.wMinute * 60 * 1000;
		m_countdown_count += time.wSecond * 1000;
		m_countdown_flag = true;
		(CButton*)GetDlgItem(IDC_BUTTON4)->EnableWindow(false);
		m_progress_cd.EnableWindow(true);
		m_countdown_time.EnableWindow(false);
		m_thred_countdown = AfxBeginThread(CountThread2_, this);
	}
}

void CCountTimeDlg::SetCStringtoDlg(int Dlgitem, CString str)
{
	CString last;
	GetDlgItemText(Dlgitem, last);
	if (last != str)
		SetDlgItemText(Dlgitem, str);
}


void CCountTimeDlg::ResetButtonState()
{
	(CButton*)GetDlgItem(IDC_BUTTON4)->EnableWindow(true);
}


void CCountTimeDlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	/*CString ccc; ccc.Format(L"%d", EVEN_NUMBER(13));
	AfxMessageBox(ccc);*/
}
