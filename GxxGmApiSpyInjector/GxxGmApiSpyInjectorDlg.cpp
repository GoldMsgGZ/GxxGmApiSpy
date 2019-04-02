
// GxxGmApiSpyInjectorDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GxxGmApiSpyInjector.h"
#include "GxxGmApiSpyInjectorDlg.h"
#include "afxdialogex.h"
#include <Tlhelp32.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CGxxGmApiSpyInjectorDlg �Ի���



CGxxGmApiSpyInjectorDlg::CGxxGmApiSpyInjectorDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGxxGmApiSpyInjectorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGxxGmApiSpyInjectorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESSES, m_cProcessList);
	DDX_Control(pDX, IDC_EDIT1, m_cDllPath);
}

BEGIN_MESSAGE_MAP(CGxxGmApiSpyInjectorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_REFRESH_PROCESSES, &CGxxGmApiSpyInjectorDlg::OnBnClickedBtnRefreshProcesses)
	ON_BN_CLICKED(IDC_BTN_INJECT, &CGxxGmApiSpyInjectorDlg::OnBnClickedBtnInject)
END_MESSAGE_MAP()


// CGxxGmApiSpyInjectorDlg ��Ϣ�������

BOOL CGxxGmApiSpyInjectorDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_cProcessList.InsertColumn(0, _T("����ID"), 0, 100);
	m_cProcessList.InsertColumn(1, _T("������"), 0, 200);
	m_cProcessList.SetExtendedStyle(m_cProcessList.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	CWnd *pcwnd = GetDlgItem(IDC_RADIO_REMOTETHREAD);
	CButton *radio_box = (CButton *)pcwnd;
	radio_box->SetCheck(1);

	OnBnClickedBtnRefreshProcesses();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CGxxGmApiSpyInjectorDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGxxGmApiSpyInjectorDlg::OnPaint()
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
HCURSOR CGxxGmApiSpyInjectorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGxxGmApiSpyInjectorDlg::OnBnClickedBtnRefreshProcesses()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_cProcessList.DeleteAllItems();

	HANDLE hProcess = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcess == NULL)
		return;

	PROCESSENTRY32 info;
	ZeroMemory(&info, sizeof(PROCESSENTRY32));
	info.dwSize = sizeof(PROCESSENTRY32);

	BOOL bret = Process32First(hProcess, &info);
	do
	{
		int count = m_cProcessList.GetItemCount();
		CString process_id_str;
		process_id_str.Format(_T("%d"), info.th32ProcessID);
		m_cProcessList.InsertItem(count, process_id_str);
		m_cProcessList.SetItemText(count, 1, info.szExeFile);

	} while (Process32Next(hProcess, &info));

	return ;
}


void CGxxGmApiSpyInjectorDlg::OnBnClickedBtnInject()
{
	// �����õ�DLL·��
	CString dll_path;
	m_cDllPath.GetWindowText(dll_path);

	// Ȼ���õ�ѡ�еĽ��̺�
	POSITION pos = m_cProcessList.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	int index = m_cProcessList.GetNextSelectedItem(pos);
	CString process_id_str = m_cProcessList.GetItemText(index, 0);
	DWORD processId = _ttoi(process_id_str.GetString());

	// ���ﳢ��ʹ��auto��������
	auto size = dll_path.GetLength() * sizeof(TCHAR);

	auto hVictimProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, processId);
	if (hVictimProcess == NULL) // check if process open failed
	{
		return ;
	}

	// allocate memory in the remote process
	auto pNameInVictimProcess = VirtualAllocEx(hVictimProcess,
		nullptr,
		size,
		MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
	if (pNameInVictimProcess == NULL) 
	{
		return ;
	}

	// write the DLL to memory
	auto bStatus = WriteProcessMemory(hVictimProcess,
		pNameInVictimProcess,
		dll_path.GetBuffer(0),
		size,
		nullptr);
	if (bStatus == 0)
	{
		return ;
	}

	// gets a handle for kernel32dll's LoadLibrary call
	auto hKernel32 = GetModuleHandle(L"kernel32.dll");
	if (hKernel32 == NULL)
	{
		return ;
	}

	auto LoadLibraryAddress = GetProcAddress(hKernel32, "LoadLibraryW");
	if (LoadLibraryAddress == NULL)
	{
		if ((LoadLibraryAddress = GetProcAddress(hKernel32, "LoadLibraryA")) == NULL)
		{
			return ;
		}
	}

	// Using the above objects execute the DLL in the remote process
	auto hThreadId = CreateRemoteThread(hVictimProcess,
		nullptr,
		0,
		reinterpret_cast<LPTHREAD_START_ROUTINE>(LoadLibraryAddress),
		pNameInVictimProcess,
		NULL,
		nullptr);
	if (hThreadId == NULL)
	{
		return ;
	}


	/*if (bStatus == NULL)
	return FALSE;
	NOT NEEDED ANYMORE*/
	WaitForSingleObject(hThreadId, INFINITE);

	CloseHandle(hVictimProcess);
	VirtualFreeEx(hVictimProcess, pNameInVictimProcess, size, MEM_RELEASE);
}
