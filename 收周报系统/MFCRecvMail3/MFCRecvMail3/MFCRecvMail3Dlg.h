
// MFCRecvMail3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "sqlite3.h"
#import "jmail.dll"// ����jmail.dll, ��jmail.dll���ڹ���Ŀ¼�£�����Ҫд������·�� 

// CMFCRecvMail3Dlg �Ի���
class CMFCRecvMail3Dlg : public CDialogEx
{
// ����
public:
	CMFCRecvMail3Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MFCRECVMAIL3_DIALOG };

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
	CString m_cstrAccount;
	CString m_cstrPassword;
	CString m_cstrSeverName;
	CString m_cstrAddName;
	CString m_cstrSDate;
	CString m_cstrEDate;
	CString m_cstrDownloadDir;
	CListCtrl m_listctrShowMail;
};
