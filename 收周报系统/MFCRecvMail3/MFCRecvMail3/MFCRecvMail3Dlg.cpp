
// MFCRecvMail3Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCRecvMail3.h"
#include "MFCRecvMail3Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMFCRecvMail3Dlg 对话框



CMFCRecvMail3Dlg::CMFCRecvMail3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMFCRecvMail3Dlg::IDD, pParent)
	, m_cstrAccount(_T(""))
	, m_cstrPassword(_T(""))
	, m_cstrSeverName(_T(""))
	, m_cstrAddName(_T(""))
	, m_cstrSDate(_T(""))
	, m_cstrEDate(_T(""))
	, m_cstrDownloadDir(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_cstrAccount = TEXT("15171496021@163.com");
	m_cstrPassword = TEXT("1javajavajava");
	m_cstrSeverName = TEXT("pop.163.com");
	m_cstrDownloadDir = TEXT("G:\\DownloadMail");
	CreateDirectory(m_cstrDownloadDir, NULL);
}

void CMFCRecvMail3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SERVERNAME, m_cstrAccount);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_cstrPassword);
	DDX_Text(pDX, IDC_EDIT_ACCOUNT, m_cstrSeverName);
	DDX_Text(pDX, IDC_EDIT_ADD_NAME, m_cstrAddName);
	DDX_Text(pDX, IDC_EDIT_S_DATE, m_cstrSDate);
	DDX_Text(pDX, IDC_EDIT_E_DATE, m_cstrEDate);
	DDX_Text(pDX, IDC_EDIT_DOWNLOAD_DRECTORY, m_cstrDownloadDir);
	DDX_Control(pDX, IDC_LIST1, m_listctrShowMail);
}

BEGIN_MESSAGE_MAP(CMFCRecvMail3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CMFCRecvMail3Dlg::OnBnClickedBtnDownload)
END_MESSAGE_MAP()


// CMFCRecvMail3Dlg 消息处理程序

BOOL CMFCRecvMail3Dlg::OnInitDialog()
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

	// TODO:  在此添加额外的初始化代码
	ConnectDataBase();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCRecvMail3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCRecvMail3Dlg::OnPaint()
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
HCURSOR CMFCRecvMail3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CMFCRecvMail3Dlg::ConnectDataBase()
{
	int rc = sqlite3_open(DB_NAME, &m_DB);

	// 判断是否有连接故障
	if (rc){
		MessageBox(TEXT("数据库连接失败\r\n"));
	}
	else{
		OutputDebugString(TEXT("数据库连接成功\r\n"));
	}
	return 0;
}


CString & CMFCRecvMail3Dlg::AddEmloyee(){
	CString cstrID;
	return cstrID;
}


CString & CMFCRecvMail3Dlg::DownloadMail(){
	CoInitialize(NULL);
	jmail::IPOP3Ptr pPOP3("JMail.POP3");
	pPOP3->Timeout = 30; // 设置连接服务器超时限制 30S

	_bstr_t bstrAaccount = m_cstrAccount.GetBuffer();
	_bstr_t bstrPassword = m_cstrPassword.GetBuffer();
	_bstr_t bstrServerName = m_cstrSeverName.GetBuffer();
	try
	{
		pPOP3->Connect(bstrAaccount, bstrPassword, bstrServerName, 110); // 连接邮件服务器，110为pop3默认端口号
		// 信箱指针
		jmail::IMessagesPtr pMessagesBox;
		// 获取信箱
		pMessagesBox = pPOP3->Messages;

		long ncMail = NULL; // 邮件数目,
		pMessagesBox->get_Count(&ncMail);
		ncMail--; // 实际上只有10封没有读的邮件

		if (!ncMail){
			// 邮件数目为零
			throw;
		}

		// 现在开始逐一检查没一封邮件
		jmail::IMessagePtr pMail;
		for (int i = ncMail; i > 0; --i){ // 邮件下标从1开始
			try{
				pMessagesBox->get_Item(i, &pMail);
			}
			catch (_com_error e){
				i = i + 1; // 从新读取
				continue;
			}
			// 到这个里表示pMail有效，且正指向一封邮件
			DATE SendTime; // 用于记录邮件的发送时间
			SendTime = pMail->GetDate();
			COleDateTime ColSendTime(SendTime); // 用于记录邮件的发送时间
			_bstr_t bstrSendTime;
			bstrSendTime = ColSendTime.Format(TEXT("%Y-%m-%d %H:%M:%S"));

			COleDateTime ColRecvTime(SendTime); // 用于记录邮件的接受的时间
			_bstr_t bstrRecvTime;
			bstrRecvTime = ColSendTime.Format(TEXT("%Y-%m-%d %H:%M:%S"));

			
			// 开始根据邮件发送的时间，建立相应文件夹
			CString cstrPath;
			CheckDateCreateDir(ColSendTime, cstrPath);

			jmail::IAttachmentsPtr pAttchmentBox;
			pAttchmentBox = pMail->Attachments;
			long lcAttachment = NULL; // 用于检查邮件中的附件数目
			pAttchmentBox->get_Count(&lcAttachment);

			// 遍历下载邮件的附件
			for (int i = 0; i < lcAttachment; ++i){
				jmail::IAttachmentPtr pAttchment;
				try{
					pAttchmentBox->get_Item(i, &pAttchment);// 获取邮件附件
				}
				catch (_com_error e){
					i = i - 1; // 从新读取
					continue;
				}

				// 判断附件是否已经下载
				_bstr_t bstrAttName = pAttchment->GetName();
				if (!MailIsRecv(bstrSendTime, bstrAttName)){
					pAttchment->Release();
					continue;
				}

				cstrPath += TEXT("\\");
				cstrPath += bstrAttName.GetBSTR();

				_bstr_t bstrFullName = cstrPath;
				pAttchment->SaveToFile(bstrFullName);

			}

			pAttchmentBox->Release();
		}


		// 释放信箱
		pMessagesBox->Release();
		// 与邮件服务器断开连接
		pPOP3->Disconnect();
		// 释放
		//pPOP3->Release();
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("连接失败！请检查邮箱地址和密码是否正确！"));
	}
	CoUninitialize();
}


BOOL CMFCRecvMail3Dlg::CheckDateCreateDir(COleDateTime & rColDateTime, CString & strDir){
	int k = rColDateTime.GetDayOfWeek();

	COleDateTime Monday;
	COleDateTimeSpan TimeSpan(k-1, 0, 0, 0);
	Monday = rColDateTime - TimeSpan;

	CString cstrDate = Monday.Format(TEXT("%Y-%m-%d"));
	strDir += m_cstrDownloadDir;
	strDir += TEXT("\\");
	strDir += cstrDate;
	strDir += TEXT("\\");

	CreateDirectory(strDir, NULL);
	return TRUE;
}

void CMFCRecvMail3Dlg::OnBnClickedBtnDownload()
{
	// TODO:  在此添加控件通知处理程序代码
	DownloadMail();
}

BOOL CMFCRecvMail3Dlg::SplitFileName(std::vector<std::string> &, std::string & strFileName){
	return NULL;
}

/*
*	检查邮件信息，判断邮件是否已经收取
*/
BOOL CMFCRecvMail3Dlg::MailIsRecv(_bstr_t  RecvTime, _bstr_t strFileName){
	return TRUE;
}


/*
*	按时间遍历收件信息
*/
BOOL CMFCRecvMail3Dlg::ListMailInfo(COleDateTime & STime, COleDateTime & ETime){
	return TRUE;
}


/*
*	检查制定周，的附件接收星狂
*/
BOOL CMFCRecvMail3Dlg::ListAWeekMail(COleDateTime & STime, COleDateTime & ETime){
	return TRUE;
}