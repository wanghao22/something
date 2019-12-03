
// CountTimeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CountTime.h"
#include "CountTimeDlg.h"
#include "afxdialogex.h"

//#include <DXGI.h>//�Կ���

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

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
				AfxMessageBox(L"ʱ�䵽��");
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
			AfxMessageBox(L"ʱ�䵽��");
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

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CCountTimeDlg �Ի���



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


// CCountTimeDlg ��Ϣ�������

BOOL CCountTimeDlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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
	//SetTimer(1, 3000, NULL);  //��һ�����������Լ������Ƕ�ʱ����ID���ڶ��������Ǽ��ʱ�䣨����Ϊ��λ�ģ�

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCountTimeDlg::OnPaint()
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
HCURSOR CCountTimeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ʼ
void CCountTimeDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//��ʱ
void CCountTimeDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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

//����
void CCountTimeDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_count_flag)
	{
		m_count_flag = false;
		//�����߳�
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
	// TODO: �ڴ����ר�ô����/����û���
	KillTimer(1);
	m_count_flag = false;
	m_countdown_flag = false;
	m_run_flag = false;
	CDialogEx::OnCancel();
}


void CCountTimeDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���
	KillTimer(1);
	m_count_flag = false;
	m_countdown_flag = false;
	m_run_flag = false;
	CDialogEx::OnOK();
}


void CCountTimeDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nIDEvent == 1)
	{
		TRACE(L"1111");
	}
	CDialogEx::OnTimer(nIDEvent);
}


void CCountTimeDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	/*CString ccc; ccc.Format(L"%d", EVEN_NUMBER(13));
	AfxMessageBox(ccc);*/
}
