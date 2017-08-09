
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


CString & CMFCRecvMail3Dlg::AddEmloyee(){
	CString cstrID;
	return cstrID;
}


CString & CMFCRecvMail3Dlg::DownloadMail(){
	CoInitialize(NULL);
	jmail::IPOP3Ptr pPOP3("JMail.POP3");
	pPOP3->Timeout = 30; // �������ӷ�������ʱ���� 30S

	_bstr_t bstrAaccount = m_cstrAccount.GetBuffer();
	_bstr_t bstrPassword = m_cstrPassword.GetBuffer();
	_bstr_t bstrServerName = m_cstrSeverName.GetBuffer();
	try
	{
		pPOP3->Connect(bstrAaccount, bstrPassword, bstrServerName, 110); // �����ʼ���������110Ϊpop3Ĭ�϶˿ں�
		// ����ָ��
		jmail::IMessagesPtr pMessagesBox;
		// ��ȡ����
		pMessagesBox = pPOP3->Messages;

		long ncMail = NULL; // �ʼ���Ŀ,
		pMessagesBox->get_Count(&ncMail);
		ncMail--; // ʵ����ֻ��10��û�ж����ʼ�

		if (!ncMail){
			// �ʼ���ĿΪ��
			throw;
		}

		// ���ڿ�ʼ��һ���ûһ���ʼ�
		jmail::IMessagePtr pMail;
		for (int i = ncMail; i > 0; --i){ // �ʼ��±��1��ʼ
			try{
				pMessagesBox->get_Item(i, &pMail);
			}
			catch (_com_error e){
				i = i + 1; // ���¶�ȡ
				continue;
			}
			// ��������ʾpMail��Ч������ָ��һ���ʼ�
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

			// ���������ʼ��ĸ���
			for (int i = 0; i < lcAttachment; ++i){
				jmail::IAttachmentPtr pAttchment;
				try{
					pAttchmentBox->get_Item(i, &pAttchment);// ��ȡ�ʼ�����
				}
				catch (_com_error e){
					i = i - 1; // ���¶�ȡ
					continue;
				}

				// �жϸ����Ƿ��Ѿ�����
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


		// �ͷ�����
		pMessagesBox->Release();
		// ���ʼ��������Ͽ�����
		pPOP3->Disconnect();
		// �ͷ�
		//pPOP3->Release();
	}
	catch (_com_error e)
	{
		AfxMessageBox(_T("����ʧ�ܣ����������ַ�������Ƿ���ȷ��"));
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	DownloadMail();
}

BOOL CMFCRecvMail3Dlg::SplitFileName(std::vector<std::string> &, std::string & strFileName){
	return NULL;
}

/*
*	����ʼ���Ϣ���ж��ʼ��Ƿ��Ѿ���ȡ
*/
BOOL CMFCRecvMail3Dlg::MailIsRecv(_bstr_t  RecvTime, _bstr_t strFileName){
	return TRUE;
}


/*
*	��ʱ������ռ���Ϣ
*/
BOOL CMFCRecvMail3Dlg::ListMailInfo(COleDateTime & STime, COleDateTime & ETime){
	return TRUE;
}


/*
*	����ƶ��ܣ��ĸ��������ǿ�
*/
BOOL CMFCRecvMail3Dlg::ListAWeekMail(COleDateTime & STime, COleDateTime & ETime){
	return TRUE;
}