
// MFCRecvMail3Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "sqlite3.h"
#import "jmail.dll"// 导入jmail.dll, 如jmail.dll不在工程目录下，您需要写上完整路径 

// CMFCRecvMail3Dlg 对话框
class CMFCRecvMail3Dlg : public CDialogEx
{
// 构造
public:
	CMFCRecvMail3Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MFCRECVMAIL3_DIALOG };

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
	CString m_cstrAccount;
	CString m_cstrPassword;
	CString m_cstrSeverName;
	CString m_cstrAddName;
	CString m_cstrSDate;
	CString m_cstrEDate;
	CString m_cstrDownloadDir;
	CListCtrl m_listctrShowMail;
};
