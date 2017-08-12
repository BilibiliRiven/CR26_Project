
// MFCRecvMail3Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "sqlite3.h"
#import "jmail.dll"// 导入jmail.dll, 如jmail.dll不在工程目录下，您需要写上完整路径 
#define DB_NAME "db_CR26RecvMail"
#include "boost/algorithm/string.hpp"
#include <boost/lexical_cast.hpp>
#include <iostream>
#include "vector"
#include "ATLComTime.h"
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
public:
	sqlite3 * m_DB;

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
	//CString m_cstrSDate;
	//CString m_cstrEDate;
	CString m_cstrDownloadDir;
	CListCtrl m_listctrShowMail;
	/*
	*	初始化list控件
	*	-----------------------------------------------
	*	|职工号id | 职工号姓名 | 附件名 | 附件存储路径|
	*	-----------------------------------------------
	*/
	int InitListctr();
	/*
	*	连接数据库，用来连接数据库
	*	sqlite3 * m_DB;数据库
	*/
	int ConnectDataBase();
	/*
	*	向数据库添员工,输入员工姓名就
	*	自动分配员工ID，返回的是员工ID
	*	失败员工ID返回空,ID从1开始，返回<0表示插入失败
	*/
	int AddEmloyee();
	/*
	*	查询邮件，将附件下载到指定文件夹
	*	邮件的收取按照星期为单位，没周收取
	*	收取的附件信息会放到数据库中。
	*	附件保存的路径以发送当天星期周末为准。
	*/
	void DownloadMail();
	/*
	*	用来分附件的名字字符串提取信息,同时检查邮件命名合法性
	*	合法返回真，非法返回假
	*/
	BOOL SplitFileName(std::vector<std::string> &, std::string & strFileName);
	/*
	*	获取邮件时间，根据时间创建文件夹。
	*	根据时间,得到当时星期一的日期，以日期为文件名创建文件夹
	*	同时返回文件的目录
	*/
	BOOL CheckDateCreateDir(COleDateTime & rColDateTime,CString & strDir);
	/*
	*	记录邮件附件的信息
	*/
	BOOL RecordMailInfo(_bstr_t RecvTime, _bstr_t strFileName, _bstr_t OwnerID, _bstr_t strFilePath);
	/*
	*	检查邮件信息，判断邮件是否已经收取
	*/
	BOOL MailIsRecv(_bstr_t RecvTime, _bstr_t strFileName);
	/*
	*	按时间遍历收件信息
	*/
	BOOL ListMailInfo(COleDateTime & STime, COleDateTime & ETime);
	/*
	*	检查制定周，的附件接收星狂
	*/
	BOOL ListAWeekMail(COleDateTime & STime, COleDateTime & ETime);
	/*
	*	查询职工姓名，获得职工ID
	*	如果找不到，或发生错误返回<0
	*/
	int GetEmloyeeID(_bstr_t bstrEmpName);
	/*
	*	遍历目录生成报表
	*/
	int GenStatment();
	/*
	*	给定一个天，过得当时的周日
	*/
	COleDateTime GetSunday(COleDateTime m_Date);
	/*
	*	给定一个天，过得当时的周末
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

