
// IP_Chat_Client_Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IP_Chat_Client_.h"
#include "IP_Chat_Client_Dlg.h"

#include "afxsock.h"

#include <iostream>
#include <stdio.h>



#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CIP_Chat_Client_Dlg �Ի���




CIP_Chat_Client_Dlg::CIP_Chat_Client_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIP_Chat_Client_Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIP_Chat_Client_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_Edit_Input);
	DDX_Control(pDX, IDC_IPADDRESS_REMOTE, m_IP_Remote);
}

BEGIN_MESSAGE_MAP(CIP_Chat_Client_Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CIP_Chat_Client_Dlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CIP_Chat_Client_Dlg ��Ϣ�������

BOOL CIP_Chat_Client_Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//===========================================�����׽��ֿ� V1.1
	//AfxSocketInit �����ڲ������� WSAStartup ���ұ�֤�������ǰ���� WSACleanup (�������ws2_32.h)
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("Failed to Initialize Sockets"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	//===========================================�����׽��ֿ� V1.1

	Init_Socket_Client();

	//==================================����Ĭ�ϵ�IP��ַ
	SetDlgItemText(IDC_IPADDRESS_REMOTE,_T("127.0.0.1"));
	//==================================����Ĭ�ϵ�IP��ַ

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CIP_Chat_Client_Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIP_Chat_Client_Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIP_Chat_Client_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void CIP_Chat_Client_Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
}

int CIP_Chat_Client_Dlg::Init_Socket_Client(void)
{

	//===========================================���� socket
	m_sock_Client=socket(AF_INET,SOCK_DGRAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================���� socket

	return 0;
}

void CIP_Chat_Client_Dlg::OnBnClickedButtonSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//======================@@@@@@@@@@@@@@@@@@@@@@=====================����Ŀ�ĵ�ַ

	////==================================����Ĭ�ϵ�IP��ַ
	//SetDlgItemText(IDC_IPADDRESS_REMOTE,_T("127.0.0.1"));
	////==================================����Ĭ�ϵ�IP��ַ

	//==================================��ȡ�����IP��ַ
	DWORD dwIP_;
	m_IP_Remote.GetAddress(dwIP_);
	PBYTE p_dwIP_=(PBYTE)&dwIP_;
	CString IP_Remote;
	IP_Remote.Format(_T("%u.%u.%u.%u"),*(p_dwIP_+3),*(p_dwIP_+2),*(p_dwIP_+1),*(p_dwIP_));
	char IP_Remote_char[100];
	sprintf(IP_Remote_char,"%u.%u.%u.%u",*(p_dwIP_+3),*(p_dwIP_+2),*(p_dwIP_+1),*(p_dwIP_));
	//==================================��ȡ�����IP��ַ

	SOCKADDR_IN Addr_To;
	Addr_To.sin_family=AF_INET;
	Addr_To.sin_port=htons(6000);
	Addr_To.sin_addr.S_un.S_addr=inet_addr(IP_Remote_char);
	//======================@@@@@@@@@@@@@@@@@@@@@@=====================����Ŀ�ĵ�ַ


	//===========================================��ȡ������Ϣ
	CString inf;
	//inf.Format(_T("This is a CString"));
	GetDlgItemText(IDC_EDIT_INPUT,inf);

	/*char * sendBuf=new char[inf.GetLength()];
	for(int i=0;i<inf.GetLength();i++)
	{
		*(sendBuf+i)=inf.GetAt(i);
	}*/

	char * sendBuf=new char[inf.GetLength()+1];//���������һλ ������Ч��֤���͵���Ϣ��β��������
	for(int i=0;i<inf.GetLength();i++)
	{
		*(sendBuf+i)=inf.GetAt(i);
	}
	*(sendBuf+inf.GetLength())='\0';//��������ڽ�β������ ������Ч��֤���͵���Ϣ��β��������
	//===========================================��ȡ������Ϣ

	//===========================================������Ϣ
	sendto(m_sock_Client,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR *)&Addr_To,sizeof(SOCKADDR));
	//===========================================������Ϣ


	//===========================================������ʾ
	char Temp_Buf[150];
	ZeroMemory(Temp_Buf,150);
	sprintf(Temp_Buf,"[Send To][%s] : %s",inet_ntoa(Addr_To.sin_addr),sendBuf);

	CString str_Display;
	str_Display=Temp_Buf;

	::GetLocalTime(&Time);//����ʱ��
	CString TIME;
	TIME.Format(_T("[%d-%d-%d %d:%d:%d] "),
		Time.wYear,Time.wMonth,Time.wDay,
		Time.wHour,Time.wMinute,Time.wSecond);

	str_Display=TIME+str_Display;

	//֮ǰ��¼
	CString str_Record;
	GetDlgItemText(IDC_EDIT_DISPLAY,str_Record);
	str_Display=str_Display+_T("\r\n");
	str_Display=str_Record+str_Display;

	SetDlgItemText(IDC_EDIT_DISPLAY,str_Display);
	//===========================================������ʾ

	SetDlgItemText(IDC_EDIT_INPUT,_T(""));//��ձ༭����Ϣ
	m_Edit_Input.SetFocus();//�ù��ص��༭��

}
