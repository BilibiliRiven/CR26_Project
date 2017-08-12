
// MFCRecvMail3Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCRecvMail3.h"
#include "MFCRecvMail3Dlg.h"
#include "afxdialogex.h"

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


// CMFCRecvMail3Dlg �Ի���



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


// CMFCRecvMail3Dlg ��Ϣ�������

BOOL CMFCRecvMail3Dlg::OnInitDialog()
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
	ConnectDataBase();
	InitListctr();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�
void CMFCRecvMail3Dlg::OnPaint()
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
HCURSOR CMFCRecvMail3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

int CMFCRecvMail3Dlg::ConnectDataBase()
{
	int rc = sqlite3_open(DB_NAME, &m_DB);

	// �ж��Ƿ������ӹ���
	if (rc){
		MessageBox(TEXT("���ݿ�����ʧ��\r\n"));
	}
	else{
		OutputDebugString(TEXT("���ݿ����ӳɹ�\r\n"));
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
	int rh = SQLITE_ERROR; // �������շ���ֵ
	char* cErrMsg = NULL; // �������մ���
	//int nID; // ��������ȡԱ��ID
	rh = sqlite3_exec(m_DB, bstrSql, NULL, NULL, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError);
		return -1;
	}
	MessageBox(TEXT("����ɹ�\r\n"));
	return 0;
}

void CMFCRecvMail3Dlg::DownloadMail(){
	CoInitialize(NULL);

	try
	{
		jmail::IPOP3Ptr pPOP3("JMail.POP3");
		pPOP3->Timeout = 30; // �������ӷ�������ʱ���� 30S

		_bstr_t bstrAaccount = m_cstrAccount.GetBuffer();
		_bstr_t bstrPassword = m_cstrPassword.GetBuffer();
		_bstr_t bstrServerName = m_cstrSeverName.GetBuffer();
		pPOP3->Connect(bstrAaccount, bstrPassword, bstrServerName, 110); // �����ʼ���������110Ϊpop3Ĭ�϶˿ں�
		// ����ָ��
		jmail::IMessagesPtr pMessagesBox;
		// ��ȡ����
		pMessagesBox = pPOP3->Messages;

		long ncMail = NULL; // �ʼ���Ŀ,
		pMessagesBox->get_Count(&ncMail);
		
		ncMail--; // ʵ����ֻ��10��û�ж����ʼ�
		if (ncMail <= 0){
			throw -1;
		}

		// ���ڿ�ʼ��һ���ûһ���ʼ�
		jmail::IMessagePtr pMail;
		//pMail->Charset = "gb2312";
		for (int i = ncMail; i >= 1; --i){ // �ʼ��±��1��ʼ
			TRACE("%d\r\n", i);
			try{
				pMail = pMessagesBox->Item[i];
			}
			catch (_com_error e){
				//i = i + 1; // ���¶�ȡ
				continue;
			}

			//��������ʾpMail��Ч������ָ��һ���ʼ�
			DATE SendTime; // ���ڼ�¼�ʼ��ķ���ʱ��
			SendTime = pMail->GetDate();
			COleDateTime ColSendTime(SendTime); // ���ڼ�¼�ʼ��ķ���ʱ��
			_bstr_t bstrSendTime;
			bstrSendTime = ColSendTime.Format(TEXT("%Y-%m-%d %H:%M:%S"));

			COleDateTime ColRecvTime(SendTime); // ���ڼ�¼�ʼ��Ľ��ܵ�ʱ��
			_bstr_t bstrRecvTime;
			bstrRecvTime = ColSendTime.Format(TEXT("%Y-%m-%d %H:%M:%S"));

			
			// ��ʼ�����ʼ����͵�ʱ�䣬������Ӧ�ļ���
			CString cstrPath;
			CheckDateCreateDir(ColSendTime, cstrPath);

			jmail::IAttachmentsPtr pAttchmentBox;
			pAttchmentBox = pMail->Attachments;
			long lcAttachment = NULL; // ���ڼ���ʼ��еĸ�����Ŀ
			pAttchmentBox->get_Count(&lcAttachment);

			//���������ʼ��ĸ���
			for (int j = 0; j < lcAttachment; ++j){
				jmail::IAttachmentPtr pAttchment;
				try{
					pAttchmentBox->get_Item(j, &pAttchment);// ��ȡ�ʼ�����
				}
				catch (_com_error e){
					j = j - 1; // ���¶�ȡ
					continue;
				}

				
				_bstr_t bstrAttName = pAttchment->GetName();
				std::vector<std::string> TagNamePices;
				std::string strAttName = bstrAttName;


				// �жϸ����Ƿ��Ѿ�����
				if (MailIsRecv(bstrSendTime, bstrAttName)){
					throw 1; // ��ʾ�ʼ��������
				}

				// �жϸ���
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
		AfxMessageBox(_T("����ʧ�ܣ����������ַ�������Ƿ���ȷ��"));
		OutputDebugString(e.Description());
	}
	catch (int e){
		if (e > 0){
			MessageBox(TEXT("�������"));
		}
		else{
			MessageBox(TEXT("���ճ����쳣"));
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
		// �����ɹ����ɹ���·����ӵ����ݿ���
		CString cstrSql;
		cstrSql.Format(TEXT("INSERT INTO tb_mailpath (mail_mailpathid, mail_path) VALUES (NULL, \'%s\')"),strDir);
		_bstr_t bstrSql = cstrSql;
		int rh = SQLITE_ERROR; // �������շ���ֵ
		char* cErrMsg = NULL; // �������մ���
		rh = sqlite3_exec(m_DB, bstrSql, NULL, NULL, &cErrMsg);
		if (rh){
			_bstr_t bstrError = cErrMsg;
			MessageBox(bstrError + TEXT(":�����ʼ��ɹ���������Ϣ�޷��������ݿ�"));
			return -1;
		}
	}
	return TRUE;
}

void CMFCRecvMail3Dlg::OnBnClickedBtnDownload()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������


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
*	����ʼ���Ϣ���ж��ʼ��Ƿ��Ѿ���ȡ
*	�Ѿ���ȡ�����棬δ��ȡ���ؼ١�
*/
BOOL CMFCRecvMail3Dlg::MailIsRecv(_bstr_t  RecvTime, _bstr_t strFileName){
	
	CString cstrSql;
	cstrSql.Format(TEXT("SELECT mail_Ownerid FROM tb_RecvMail WHERE  mail_mailID = \'%s-%s\'"), RecvTime.GetBSTR(), strFileName.GetBSTR());
	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // �������շ���ֵ
	BOOL bRet = FALSE;
	char* cErrMsg = NULL; // �������մ���
	rh = sqlite3_exec(m_DB, bstrSql, MailIsRecvcallback, &bRet, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError + TEXT(":�����ʼ��ɹ���������Ϣ�޷��������ݿ�"));
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
*	��ʱ������ռ���Ϣ
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
		int rh = SQLITE_ERROR; // �������շ���ֵ
		char* cErrMsg = NULL; // �������մ���
		rh = sqlite3_exec(m_DB, bstrSql, ListMailInfocallback, this, &cErrMsg);
		if (rh){
			_bstr_t bstrError = cErrMsg;
			MessageBox(bstrError + TEXT(":�����ʼ��ɹ���������Ϣ�޷��������ݿ�"));
			return -1;
		}
		return FALSE;
	}
	catch (_com_error &e){
		MessageBox(TEXT("����������ʱ��������Ϸ�����׼��ʽ��%Y-%m-%d��"));
	}
	return FALSE;
}

/*kk
*	����ƶ��ܣ��ĸ��������ǿ�
*/
BOOL CMFCRecvMail3Dlg::ListAWeekMail(COleDateTime & STime, COleDateTime & ETime){
	return TRUE;
}

/*
*	��¼�ʼ���������Ϣ
*/
BOOL CMFCRecvMail3Dlg::RecordMailInfo(_bstr_t RecvTime, _bstr_t strFileName, _bstr_t strOwnerName,_bstr_t strFilePath){
	// ����������
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
	

	// ִ�в������
	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // �������շ���ֵ
	char* cErrMsg = NULL; // �������մ���
	//int nID; // ��������ȡԱ��ID

	rh = sqlite3_exec(m_DB, bstrSql, NULL, NULL, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError+TEXT(":�����ʼ��ɹ���������Ϣ�޷��������ݿ�"));
		return -1;
	}
	return FALSE;
}

void CMFCRecvMail3Dlg::OnBnClickedBtnAddName()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
	int rh = SQLITE_ERROR; // �������շ���ֵ
	char* cErrMsg = NULL; // �������մ���
	int nID = -1; // ��������ȡԱ��ID
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
	m_listctrShowMail.InsertColumn(col++, TEXT("����"), 0, 100);
	m_listctrShowMail.InsertColumn(col++, TEXT("��������"), 0, 100);
	m_listctrShowMail.InsertColumn(col++, TEXT("·��"), 0, 100);
	m_listctrShowMail.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	return 0;
}

void CMFCRecvMail3Dlg::OnEnChangeEditEDate()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}

void CMFCRecvMail3Dlg::OnBnClickedBtnSearch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	m_listctrShowMail.DeleteAllItems();
	ListMailInfo(m_STime, m_ETime);
}

void CMFCRecvMail3Dlg::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
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
		pDlg->m_listctrShowMail.InsertItem(0, TEXT("��"));
		pDlg->m_listctrShowMail.SetItemText(0, 1, TEXT("�ύ���"));
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
	int rh = SQLITE_ERROR; // �������շ���ֵ
	char* cErrMsg = NULL; // �������մ���
	rh = sqlite3_exec(pDlg->m_DB, bstrSql, WriteFilecallback, hFile, &cErrMsg);
	CloseHandle(hFile);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		OutputDebugString(TEXT("GenStatmentcallback ���ִ���"));
		return -1;
	}
	return FALSE;
}

int CMFCRecvMail3Dlg::GenStatment(){
	CString cstrSql;
	cstrSql.Format(TEXT("SELECT mail_path FROM tb_mailpath"));

	_bstr_t bstrSql = cstrSql;
	int rh = SQLITE_ERROR; // �������շ���ֵ
	char* cErrMsg = NULL; // �������մ���
	int nID = -1; // ��������ȡԱ��ID
	rh = sqlite3_exec(m_DB, bstrSql, GenStatmentcallback, this, &cErrMsg);
	if (rh){
		_bstr_t bstrError = cErrMsg;
		MessageBox(bstrError);
		return -1;
	}
	return nID;
}

/*
*	����һ���죬���õ�ʱ������
*/
COleDateTime  CMFCRecvMail3Dlg::GetSunday(COleDateTime m_Date){
	int k = m_Date.GetDayOfWeek();
	COleDateTime Sunday;
	COleDateTimeSpan TimeSpan(k - 1, 0, 0, 0);
	Sunday = m_Date - TimeSpan;
	return Sunday;
}


/*
*	����һ���죬���õ�ʱ����ĩ
*/
COleDateTime  CMFCRecvMail3Dlg::GetSaturday(COleDateTime m_Date){
	int k = m_Date.GetDayOfWeek();
	COleDateTime Sunday;
	COleDateTimeSpan TimeSpan(7 - k, 0, 0, 0);
	Sunday = m_Date + TimeSpan;
	return Sunday;
}

