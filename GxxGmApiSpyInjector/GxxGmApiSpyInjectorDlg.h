
// GxxGmApiSpyInjectorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CGxxGmApiSpyInjectorDlg �Ի���
class CGxxGmApiSpyInjectorDlg : public CDialogEx
{
// ����
public:
	CGxxGmApiSpyInjectorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GXXGMAPISPYINJECTOR_DIALOG };

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
	CListCtrl m_cProcessList;
	CEdit m_cDllPath;
	afx_msg void OnBnClickedBtnRefreshProcesses();
	afx_msg void OnBnClickedBtnInject();
};
