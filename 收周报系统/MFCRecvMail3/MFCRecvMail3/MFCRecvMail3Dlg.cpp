
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
	//, m_cstrSDate(_T(""))
	//, m_cstrEDate(_T(""))
	, m_cstrDownloadDir(_T(""))
	, m_STime(COleDateTime::GetCurrentTime())
	, m_ETime(COleDateTime::GetCurrentTime())
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
	//DDX_Text(pDX, IDC_EDIT_S_DATE, m_cstrSDate);
	//DDX_Text(pDX, IDC_EDIT_E_DATE, m_cstrEDate);
	DDX_Text(pDX, IDC_EDIT_DOWNLOAD_DRECTORY, m_cstrDownloadDir);
	DDX_Control(pDX, IDC_LIST1, m_listctrShowMail);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER3, m_STime);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER4, m_ETime);
}

BEGIN_MESSAGE_MAP(CMFCRecvMail3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_DOWNLOAD, &CMFCRecvMail3Dlg::OnBnClickedBtnDownload)
	ON_BN_CLICKED(IDC_BTN_ADD_NAME, &CMFCRecvMail3Dlg::OnBnClickedBtnAddName)
	ON_EN_CHANGE(IDC_EDIT_E_DATE, &CMFCRecvMail3Dlg::OnEnChangeEditEDate)
	ON_BN_CLICKED(IDC_BTN_SEARCH, &CMFCRecvMail3Dlg::OnBnClickedBtnSearch)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCRecvMail3Dlg::OnBnClickedButton1)
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
	InitListctr();
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

int CMFCRecvMail3Dlg::AddEmloyee(){
	CString cstrID;

	CString cstrSql;
	// CEdit * pEdit = (CEdit *)GetDlgItem(IDC_EDIT_ADD_NAME);
	UpdateData(1);
	cstrSql.Format(TEXT("INSERT INTO tb_Employee (employee_id, employee_name) VALUES (NULL, \'%s\')"), m_cstrAddName);

	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // 用来接收返回值
	char* cErrMsg = NULL; // 用来接收错误
	//int nID; // 用来过获取员工ID
	rh = sqlite3_exec(m_DB, bstrSql, NULL, NULL, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError);
		return -1;
	}
	MessageBox(TEXT("插入成功\r\n"));
	return 0;
}

void CMFCRecvMail3Dlg::DownloadMail(){
	CoInitialize(NULL);

	try
	{
		jmail::IPOP3Ptr pPOP3("JMail.POP3");
		pPOP3->Timeout = 30; // 设置连接服务器超时限制 30S

		_bstr_t bstrAaccount = m_cstrAccount.GetBuffer();
		_bstr_t bstrPassword = m_cstrPassword.GetBuffer();
		_bstr_t bstrServerName = m_cstrSeverName.GetBuffer();
		pPOP3->Connect(bstrAaccount, bstrPassword, bstrServerName, 110); // 连接邮件服务器，110为pop3默认端口号
		// 信箱指针
		jmail::IMessagesPtr pMessagesBox;
		// 获取信箱
		pMessagesBox = pPOP3->Messages;

		long ncMail = NULL; // 邮件数目,
		pMessagesBox->get_Count(&ncMail);
		
		ncMail--; // 实际上只有10封没有读的邮件
		if (ncMail <= 0){
			throw -1;
		}

		// 现在开始逐一检查没一封邮件
		jmail::IMessagePtr pMail;
		//pMail->Charset = "gb2312";
		for (int i = ncMail; i >= 1; --i){ // 邮件下标从1开始
			TRACE("%d\r\n", i);
			try{
				pMail = pMessagesBox->Item[i];
			}
			catch (_com_error e){
				//i = i + 1; // 从新读取
				continue;
			}

			//到这个里表示pMail有效，且正指向一封邮件
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

			//遍历下载邮件的附件
			for (int j = 0; j < lcAttachment; ++j){
				jmail::IAttachmentPtr pAttchment;
				try{
					pAttchmentBox->get_Item(j, &pAttchment);// 获取邮件附件
				}
				catch (_com_error e){
					j = j - 1; // 从新读取
					continue;
				}

				
				_bstr_t bstrAttName = pAttchment->GetName();
				std::vector<std::string> TagNamePices;
				std::string strAttName = bstrAttName;


				// 判断附件是否已经下载
				if (MailIsRecv(bstrSendTime, bstrAttName)){
					throw 1; // 表示邮件查收完毕
				}

				// 判断附件
				if (!SplitFileName(TagNamePices, strAttName)){
					continue;
				}

				_bstr_t	bstrOwner = TagNamePices[0].c_str();
				_bstr_t bstrPath = cstrPath;
				cstrPath += TEXT("\\");
				cstrPath += bstrAttName.GetBSTR();

				_bstr_t bstrFullName = cstrPath;
				pAttchment->SaveToFile(bstrFullName);
				RecordMailInfo(bstrRecvTime, bstrAttName, bstrOwner, bstrPath);
			}
			pAttchmentBox->Clear();
		}
		pMessagesBox->Clear();
		pPOP3->Disconnect();
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("连接失败！请检查邮箱地址和密码是否正确！"));
		OutputDebugString(e.Description());
	}
	catch (int e){
		if (e > 0){
			MessageBox(TEXT("查收完毕"));
		}
		else{
			MessageBox(TEXT("查收出现异常"));
		}
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

	if (CreateDirectory(strDir, NULL)){
		// 创建成功将成功的路径添加到数据库中
		CString cstrSql;
		cstrSql.Format(TEXT("INSERT INTO tb_mailpath (mail_mailpathid, mail_path) VALUES (NULL, \'%s\')"),strDir);
		_bstr_t bstrSql = cstrSql;
		int rh = SQLITE_ERROR; // 用来接收返回值
		char* cErrMsg = NULL; // 用来接收错误
		rh = sqlite3_exec(m_DB, bstrSql, NULL, NULL, &cErrMsg);
		if (rh){
			_bstr_t bstrError = cErrMsg;
			MessageBox(bstrError + TEXT(":下载邮件成功，但是信息无法插入数据库"));
			return -1;
		}
	}
	return TRUE;
}

void CMFCRecvMail3Dlg::OnBnClickedBtnDownload()
{
	// TODO:  在此添加控件通知处理程序代码


	DownloadMail();
}

BOOL CMFCRecvMail3Dlg::SplitFileName(std::vector<std::string> & Tag_pices, std::string & strFileName){
	boost::split(Tag_pices, strFileName, boost::is_any_of("-."));

	int nId = -1;
	int nID = GetEmloyeeID(Tag_pices[0].c_str());
	if (nID < 0){
		return FALSE;
	}
	return TRUE;
}

static int MailIsRecvcallback(void *NotUsed, int argc, char **argv, char **azColName){
	*(BOOL *)NotUsed = TRUE;
	return 0;
}

/*
*	检查邮件信息，判断邮件是否已经收取
*	已经收取返回真，未收取返回假。
*/
BOOL CMFCRecvMail3Dlg::MailIsRecv(_bstr_t  RecvTime, _bstr_t strFileName){
	
	CString cstrSql;
	cstrSql.Format(TEXT("SELECT mail_Ownerid FROM tb_RecvMail WHERE  mail_mailID = \'%s-%s\'"), RecvTime.GetBSTR(), strFileName.GetBSTR());
	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // 用来接收返回值
	BOOL bRet = FALSE;
	char* cErrMsg = NULL; // 用来接收错误
	rh = sqlite3_exec(m_DB, bstrSql, MailIsRecvcallback, &bRet, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError + TEXT(":下载邮件成功，但是信息无法插入数据库"));
		return -1;
	}
	return bRet;
}

static int ListMailInfocallback(void *Wnd, int argc, char **argv, char **azColName){
	CMFCRecvMail3Dlg * pDlg = (CMFCRecvMail3Dlg *)Wnd;
	_bstr_t bstrTemp = argv[0];
	pDlg->m_listctrShowMail.InsertItem(0, bstrTemp);
	for (int i = 1; i < argc; ++i){
		bstrTemp = argv[i];
		pDlg->m_listctrShowMail.SetItemText(0, i,bstrTemp);
	}
	return 0;
}

/*
*	按时间遍历收件信息
*/
BOOL CMFCRecvMail3Dlg::ListMailInfo(COleDateTime & STime, COleDateTime & ETime){
	try{
		_bstr_t bstrSTime = STime.Format(TEXT("%Y-%m-%d"));
		_bstr_t bstrETime = ETime.Format(TEXT("%Y-%m-%d"));

		CString cstrSql;
		cstrSql.Format(TEXT("SELECT employee_id, employee_name, mail_name, mail_path FROM tb_Employee LEFT OUTER JOIN (SELECT mail_Ownerid, mail_name, mail_path FROM  tb_RecvMail,\
			tb_mailpath ON tb_RecvMail.mail_SavePathID = tb_mailpath.mail_mailpathid WHERE mail_sendtime >= \'%s\' and mail_sendtime <= \'s\')ON employee_id = mail_Ownerid"),\
			bstrSTime.GetBSTR(), bstrETime.GetBSTR());

		_bstr_t bstrSql = cstrSql;
		int rh = SQLITE_ERROR; // 用来接收返回值
		char* cErrMsg = NULL; // 用来接收错误
		rh = sqlite3_exec(m_DB, bstrSql, ListMailInfocallback, this, &cErrMsg);
		if (rh){
			_bstr_t bstrError = cErrMsg;
			MessageBox(bstrError + TEXT(":下载邮件成功，但是信息无法插入数据库"));
			return -1;
		}
		return FALSE;
	}
	catch (_com_error &e){
		MessageBox(TEXT("请重新输入时间参数不合法！标准格式（%Y-%m-%d）"));
	}
	return FALSE;
}

/*kk
*	检查制定周，的附件接收星狂
*/
BOOL CMFCRecvMail3Dlg::ListAWeekMail(COleDateTime & STime, COleDateTime & ETime){
	return TRUE;
}

/*
*	记录邮件附件的信息
*/
BOOL CMFCRecvMail3Dlg::RecordMailInfo(_bstr_t RecvTime, _bstr_t strFileName, _bstr_t strOwnerName,_bstr_t strFilePath){
	// 构造插入语句
	CString cstrSql;
	CString temp;
	cstrSql.Format(TEXT("INSERT INTO tb_RecvMail (mail_mailID, mail_sendtime, mail_name, mail_SavePathID, mail_Ownerid) VALUES "));
	cstrSql += TEXT("(");
	temp.Format(TEXT("\'%s-%s\',"), RecvTime.GetBSTR(), strFileName.GetBSTR());
	cstrSql += temp;
	temp.Format(TEXT("\'%s\',"), RecvTime.GetBSTR());
	cstrSql += temp;
	temp.Format(TEXT("\'%s\',"), strFileName.GetBSTR());
	cstrSql += temp;
	temp.Format(TEXT("(SELECT mail_mailpathid FROM tb_mailpath WHERE mail_path=\'%s\'),"), strFilePath.GetBSTR());
	cstrSql += temp;
	temp.Format(TEXT(" (SELECT employee_id FROM tb_Employee WHERE employee_name=\'%s\')"), strOwnerName.GetBSTR());
	cstrSql += temp;
	cstrSql += TEXT(")");
	

	// 执行插入语句
	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // 用来接收返回值
	char* cErrMsg = NULL; // 用来接收错误
	//int nID; // 用来过获取员工ID

	rh = sqlite3_exec(m_DB, bstrSql, NULL, NULL, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError+TEXT(":下载邮件成功，但是信息无法插入数据库"));
		return -1;
	}
	return FALSE;
}

void CMFCRecvMail3Dlg::OnBnClickedBtnAddName()
{
	// TODO:  在此添加控件通知处理程序代码
	AddEmloyee();
}

static int AddEmploycallback(void *NotUsed, int argc, char **argv, char **azColName){
	*(int *)NotUsed = boost::lexical_cast<int>(*argv);
	return 0;
}

int	CMFCRecvMail3Dlg::GetEmloyeeID(_bstr_t bstrEmpName){
	CString cstrSql;
	cstrSql.Format(TEXT("SELECT employee_id FROM tb_Employee WHERE employee_name=\'%s\'"), bstrEmpName.GetBSTR());

	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // 用来接收返回值
	char* cErrMsg = NULL; // 用来接收错误
	int nID = -1; // 用来过获取员工ID
	rh = sqlite3_exec(m_DB, bstrSql, AddEmploycallback, &nID, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError);
		return -1;
	}
	return nID;
}

int CMFCRecvMail3Dlg::InitListctr(){
	int col = 0;
	m_listctrShowMail.InsertColumn(col++, TEXT("ID"), 0, 50);
	m_listctrShowMail.InsertColumn(col++, TEXT("姓名"), 0, 100);
	m_listctrShowMail.InsertColumn(col++, TEXT("附件名称"), 0, 100);
	m_listctrShowMail.InsertColumn(col++, TEXT("路径"), 0, 100);
	m_listctrShowMail.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return 0;
}

void CMFCRecvMail3Dlg::OnEnChangeEditEDate()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CMFCRecvMail3Dlg::OnBnClickedBtnSearch()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	m_listctrShowMail.DeleteAllItems();
	ListMailInfo(m_STime, m_ETime);
}

void CMFCRecvMail3Dlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	GenStatment();
}

static int WriteFilecallback(void *hFile, int argc, char **argv, char **azColName){
	CString m_Str;
	_bstr_t bstrName = argv[1];
	_bstr_t bstrFile = argv[2];
	m_Str.Format(TEXT("%s-%s\r\n"), bstrName.GetBSTR(), bstrFile.GetBSTR());
	DWORD nBytes;
	WriteFile(hFile, m_Str.GetBuffer(), m_Str.GetLength(), &nBytes,NULL);
	return 0;
}

static int GenStatmentcallback(void *pWnd, int argc, char **argv, char **azColName){
	CMFCRecvMail3Dlg * pDlg = (CMFCRecvMail3Dlg *)pWnd;
	_bstr_t bstrDir = argv[0];
	_bstr_t bstrFilepath = bstrDir + TEXT("Statment.txt");
	if (PathFileExists(bstrFilepath)){
		pDlg->m_listctrShowMail.InsertItem(0, TEXT("空"));
		pDlg->m_listctrShowMail.SetItemText(0, 1, TEXT("提交情况"));
		pDlg->m_listctrShowMail.SetItemText(0, 2, TEXT("Statment.txt"));
		pDlg->m_listctrShowMail.SetItemText(0, 3, bstrDir);
		return 0;
	}
	std::vector<std::string> vt;
	std::string str;
	str = bstrDir;
	boost::split(vt, str, boost::is_any_of("\\"));
	CString strDate;
	strDate = vt[vt.size() - 2].c_str();
	COleVariant Vt(strDate);
	Vt.ChangeType(VT_DATE);
	COleDateTime Date = Vt;

	HANDLE hFile;
	hFile = CreateFile(bstrFilepath, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	_bstr_t bstrSTime = pDlg->GetSunday(Date).Format(TEXT("%Y-%m-%d"));
	_bstr_t bstrETime = pDlg->GetSaturday(Date).Format(TEXT("%Y-%m-%d"));
	CString cstrSql1, cstrSql2;
	cstrSql1.Format(TEXT("SELECT employee_id, employee_name, mail_name, mail_path FROM tb_Employee LEFT OUTER JOIN (SELECT mail_Ownerid, mail_name, mail_path FROM  tb_RecvMail,\
															tb_mailpath ON tb_RecvMail.mail_SavePathID = tb_mailpath.mail_mailpathid WHERE mail_sendtime >= \'%s\' and mail_sendtime <= \'%s\')ON employee_id = mail_Ownerid\
															 ORDER BY mail_name"), \
															 bstrSTime.GetBSTR(), bstrETime.GetBSTR());

	_bstr_t bstrSql = cstrSql1;
	int rh = SQLITE_ERROR; // 用来接收返回值
	char* cErrMsg = NULL; // 用来接收错误
	rh = sqlite3_exec(pDlg->m_DB, bstrSql, WriteFilecallback, hFile, &cErrMsg);
	CloseHandle(hFile);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		OutputDebugString(TEXT("GenStatmentcallback 出现错误"));
		return -1;
	}
	return FALSE;
}

int CMFCRecvMail3Dlg::GenStatment(){
	CString cstrSql;
	cstrSql.Format(TEXT("SELECT mail_path FROM tb_mailpath"));

	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // 用来接收返回值
	char* cErrMsg = NULL; // 用来接收错误
	int nID = -1; // 用来过获取员工ID
	rh = sqlite3_exec(m_DB, bstrSql, GenStatmentcallback, this, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError);
		return -1;
	}
	return nID;
}

/*
*	给定一个天，过得当时的周日
*/
COleDateTime  CMFCRecvMail3Dlg::GetSunday(COleDateTime m_Date){
	int k = m_Date.GetDayOfWeek();
	COleDateTime Sunday;
	COleDateTimeSpan TimeSpan(k - 1, 0, 0, 0);
	Sunday = m_Date - TimeSpan;
	return Sunday;
}


/*
*	给定一个天，过得当时的周末
*/
COleDateTime  CMFCRecvMail3Dlg::GetSaturday(COleDateTime m_Date){
	int k = m_Date.GetDayOfWeek();
	COleDateTime Sunday;
	COleDateTimeSpan TimeSpan(7 - k, 0, 0, 0);
	Sunday = m_Date + TimeSpan;
	return Sunday;
}

