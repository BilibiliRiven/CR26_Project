
// MFCRecvMail3Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "sqlite3.h"
#import "jmail.dll"// ����jmail.dll, ��jmail.dll���ڹ���Ŀ¼�£�����Ҫд������·�� 
#define DB_NAME "db_CR26RecvMail"
#include "boost/algorithm/string.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "vector"
#include "ATLComTime.h"
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
public:
	sqlite3 * m_DB;

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
	//CString m_cstrSDate;
	//CString m_cstrEDate;
	CString m_cstrDownloadDir;
	CListCtrl m_listctrShowMail;
	/*
	*	��ʼ��list�ؼ�
	*	-----------------------------------------------
	*	|ְ����id | ְ�������� | ������ | �����洢·��|
	*	-----------------------------------------------
	*/
	int InitListctr();
	/*
	*	�������ݿ⣬�����������ݿ�
	*	sqlite3 * m_DB;���ݿ�
	*/
	int ConnectDataBase();
	/*
	*	�����ݿ���Ա��,����Ա��������
	*	�Զ�����Ա��ID�����ص���Ա��ID
	*	ʧ��Ա��ID���ؿ�,ID��1��ʼ������<0��ʾ����ʧ��
	*/
	int AddEmloyee();
	/*
	*	��ѯ�ʼ������������ص�ָ���ļ���
	*	�ʼ�����ȡ��������Ϊ��λ��û����ȡ
	*	��ȡ�ĸ�����Ϣ��ŵ����ݿ��С�
	*	���������·���Է��͵���������ĩΪ׼��
	*/
	void DownloadMail();
	/*
	*	�����ָ����������ַ�����ȡ��Ϣ,ͬʱ����ʼ������Ϸ���
	*	�Ϸ������棬�Ƿ����ؼ�
	*/
	BOOL SplitFileName(std::vector<std::string> &, std::string & strFileName);
	/*
	*	��ȡ�ʼ�ʱ�䣬����ʱ�䴴���ļ��С�
	*	����ʱ��,�õ���ʱ����һ�����ڣ�������Ϊ�ļ��������ļ���
	*	ͬʱ�����ļ���Ŀ¼
	*/
	BOOL CheckDateCreateDir(COleDateTime & rColDateTime,CString & strDir);
	/*
	*	��¼�ʼ���������Ϣ
	*/
	BOOL RecordMailInfo(_bstr_t RecvTime, _bstr_t strFileName, _bstr_t OwnerID, _bstr_t strFilePath);
	/*
	*	����ʼ���Ϣ���ж��ʼ��Ƿ��Ѿ���ȡ
	*/
	BOOL MailIsRecv(_bstr_t RecvTime, _bstr_t strFileName);
	/*
	*	��ʱ������ռ���Ϣ
	*/
	BOOL ListMailInfo(COleDateTime & STime, COleDateTime & ETime);
	/*
	*	����ƶ��ܣ��ĸ��������ǿ�
	*/
	BOOL ListAWeekMail(COleDateTime & STime, COleDateTime & ETime);
	/*
	*	��ѯְ�����������ְ��ID
	*	����Ҳ������������󷵻�<0
	*/
	int GetEmloyeeID(_bstr_t bstrEmpName);
	/*
	*	����Ŀ¼���ɱ���
	*/
	int GenStatment();
	/*
	*	����һ���죬���õ�ʱ������
	*/
	COleDateTime GetSunday(COleDateTime m_Date);
	/*
	*	����һ���죬���õ�ʱ����ĩ
	*/
	COleDateTime GetSaturday(COleDateTime m_Date);
	afx_msg void OnBnClickedBtnDownload();
	afx_msg void OnBnClickedBtnAddName();
	afx_msg void OnEnChangeEditEDate();
	COleDateTime m_STime;
	COleDateTime m_ETime;
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedButton1();
};

