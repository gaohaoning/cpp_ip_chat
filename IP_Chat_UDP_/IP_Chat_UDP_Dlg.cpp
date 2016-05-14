
// IP_Chat_UDP_Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IP_Chat_UDP_.h"
#include "IP_Chat_UDP_Dlg.h"

#include "afxsock.h"
#include <iostream>
#include <stdio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
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

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CIP_Chat_UDP_Dlg 对话框




CIP_Chat_UDP_Dlg::CIP_Chat_UDP_Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIP_Chat_UDP_Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIP_Chat_UDP_Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS_REMOTE, m_IP_Remote);
	DDX_Control(pDX, IDC_IPADDRESS_LOCAL, m_IP_Local);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_Edit_Input);
}

BEGIN_MESSAGE_MAP(CIP_Chat_UDP_Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DESTROY()
	//===========================================================
	ON_MESSAGE(WM_RECV_DATA, &CIP_Chat_UDP_Dlg::On_Recv_Data)
	//===========================================================
	ON_BN_CLICKED(IDC_BUTTON_SEND, &CIP_Chat_UDP_Dlg::OnBnClickedButtonSend)
END_MESSAGE_MAP()


// CIP_Chat_UDP_Dlg 消息处理程序

BOOL CIP_Chat_UDP_Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//=================================================Server
	Initialize_Windows_Sockets();

	Init_Socket_Server();

	Init_Socket_Server_IP();

	Server_Recv();
	//=================================================Server

	//=================================================Client
	Init_Socket_Client();

	SetDlgItemText(IDC_IPADDRESS_REMOTE,_T("127.0.0.1"));
	//=================================================Client

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIP_Chat_UDP_Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIP_Chat_UDP_Dlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIP_Chat_UDP_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CIP_Chat_UDP_Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

//////////////////////////////////////////////////////////////////////////////////////


int CIP_Chat_UDP_Dlg::Initialize_Windows_Sockets(void)
{
	int result=AfxSocketInit();
	if(result==0)
	{
		::AfxMessageBox(_T("Failed to Initialize Sockets"));
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////

int CIP_Chat_UDP_Dlg::Init_Socket_Server(void)
{
	//===========================================创建 socket
	m_sock_Server=socket(AF_INET,SOCK_DGRAM,0);
	if(m_sock_Server==INVALID_SOCKET)
	{
		::AfxMessageBox(_T("SOCKET 创建失败"));
	}
	//===========================================创建 socket

	//===========================================绑定 socket
	m_Addr_Local.sin_family=AF_INET;//地址族
	m_Addr_Local.sin_port=htons(6000);//端口号
	m_Addr_Local.sin_addr.S_un.S_addr=htonl(INADDR_ANY);//主机IP地址

	int bind_result=bind(m_sock_Server,(SOCKADDR *)&m_Addr_Local,sizeof(SOCKADDR));
	if(bind_result==SOCKET_ERROR)
	{
		::AfxMessageBox(_T("SOCKET 绑定失败"));
	}
	//===========================================绑定 socket

	return 0;
}

int CIP_Chat_UDP_Dlg::Init_Socket_Server_IP(void)
{
	//===========================================获取本机 IP信息
	char Name[100];
	hostent * HostInfo;
	CString IP_Local;
	char IP_Local_char[100];
	if(::gethostname(Name,sizeof(Name))==0)
	{
		HostInfo=::gethostbyname(Name);
		if(HostInfo!=NULL)
		{
			//此处运算结构极为复杂 包含很多层 详见 typedef struct hostent 
			IP_Local=inet_ntoa(*((in_addr *)*(HostInfo->h_addr_list)));
			//可用于 SOCKET 地址的表达式为: *((in_addr *)*(HostInfo->h_addr_list))
			sprintf(IP_Local_char,"%s",inet_ntoa(*((in_addr *)*(HostInfo->h_addr_list))));
		}
	}
	//此处运算结构极为复杂 包含很多层 详见 typedef struct hostent
	DWORD dwIP=htonl(inet_addr(inet_ntoa(*((in_addr *)*(HostInfo->h_addr_list)))));
	m_IP_Local.SetAddress(dwIP);
	//===========================================获取本机 IP信息

	return 0;
}


int CIP_Chat_UDP_Dlg::Server_Recv(void)
{
	Recv_Parameter * p_Recv_Parameter=new Recv_Parameter;
	p_Recv_Parameter->sock=m_sock_Server;//sock_Recv
	p_Recv_Parameter->hwnd=m_hWnd;

	hThread_Recv=::CreateThread(NULL,0,Recv_ThreadProc,(LPVOID)p_Recv_Parameter,0,NULL);
	::CloseHandle(hThread_Recv);

	return 0;
}

DWORD WINAPI CIP_Chat_UDP_Dlg::Recv_ThreadProc(LPVOID lpParameter)
{
	SOCKET sock=((Recv_Parameter *)lpParameter)->sock;//recvfrom函数用到
	HWND hwnd=((Recv_Parameter *)lpParameter)->hwnd;//发消息时用到
	
	SOCKADDR_IN Addr_From;
	int len=sizeof(SOCKADDR_IN);
	char Recv_Buf[100];
	char Temp_Buf[150];
	ZeroMemory(Recv_Buf,100);
	ZeroMemory(Temp_Buf,150);

	int recv_result;
	while(1)
	{
		recv_result=recvfrom(sock,Recv_Buf,100,0,(sockaddr *)&Addr_From,&len);
		if(recv_result==SOCKET_ERROR)
		{
			break;
		}

		sprintf(Temp_Buf,"[Receive From][%s] : %s",inet_ntoa(Addr_From.sin_addr),Recv_Buf);

		::PostMessageW(hwnd,WM_RECV_DATA,0,(LPARAM)Temp_Buf);
	}

	return 0;
}

LRESULT CIP_Chat_UDP_Dlg::On_Recv_Data(WPARAM wParam,LPARAM lParam)//(LPARAM)Temp_Buf
{
	char * pchar=(char *)lParam;
	CString str_Display;
	str_Display=pchar;

	::GetLocalTime(&Time);//本地时间
	CString TIME;
	TIME.Format(_T("[%d-%d-%d %d:%d:%d] "),
		Time.wYear,Time.wMonth,Time.wDay,
		Time.wHour,Time.wMinute,Time.wSecond);

	str_Display=TIME+str_Display;


	//之前记录
	CString str_Record;
	GetDlgItemText(IDC_EDIT_DISPLAY,str_Record);
	str_Display=str_Display+_T("\r\n");
	str_Display=str_Record+str_Display;

	SetDlgItemText(IDC_EDIT_DISPLAY,str_Display);

	return 0;
}


//////////////////////////////////////////////////////////////////////////////////////

int CIP_Chat_UDP_Dlg::Init_Socket_Client(void)
{
	//===========================================创建 socket
	m_sock_Client=socket(AF_INET,SOCK_DGRAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================创建 socket

	return 0;
}


void CIP_Chat_UDP_Dlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//======================@@@@@@@@@@@@@@@@@@@@@@=====================设置目的地址
	//==================================获取输入的IP地址
	DWORD dwIP_;
	m_IP_Remote.GetAddress(dwIP_);
	PBYTE p_dwIP_=(PBYTE)&dwIP_;
	CString IP_Remote;
	IP_Remote.Format(_T("%u.%u.%u.%u"),*(p_dwIP_+3),*(p_dwIP_+2),*(p_dwIP_+1),*(p_dwIP_));
	char IP_Remote_char[100];
	sprintf(IP_Remote_char,"%u.%u.%u.%u",*(p_dwIP_+3),*(p_dwIP_+2),*(p_dwIP_+1),*(p_dwIP_));
	//==================================获取输入的IP地址

	SOCKADDR_IN Addr_To;
	Addr_To.sin_family=AF_INET;
	Addr_To.sin_port=htons(6000);
	Addr_To.sin_addr.S_un.S_addr=inet_addr(IP_Remote_char);
	//======================@@@@@@@@@@@@@@@@@@@@@@=====================设置目的地址

	//===========================================获取发送信息
	CString inf;
	//inf.Format(_T("This is a CString"));
	GetDlgItemText(IDC_EDIT_INPUT,inf);

	//char * sendBuf=new char[inf.GetLength()];
	//for(int i=0;i<inf.GetLength();i++)
	//{
	//	*(sendBuf+i)=inf.GetAt(i);
	//}
	char * sendBuf=new char[inf.GetLength()+1];//这里必须多加一位 才能有效保证发送的信息结尾处无乱码
	for(int i=0;i<inf.GetLength();i++)
	{
		*(sendBuf+i)=inf.GetAt(i);
	}
	*(sendBuf+inf.GetLength())='\0';//这里必须在结尾处置零 才能有效保证发送的信息结尾处无乱码
	//===========================================获取发送信息

	//===========================================发送信息
	sendto(m_sock_Client,sendBuf,strlen(sendBuf)+1,0,(SOCKADDR *)&Addr_To,sizeof(SOCKADDR));
	//===========================================发送信息

	//===========================================本地显示
	char Temp_Buf[150];
	ZeroMemory(Temp_Buf,150);
	sprintf(Temp_Buf,"[Send To][%s] : %s",inet_ntoa(Addr_To.sin_addr),sendBuf);

	CString str_Display;
	str_Display=Temp_Buf;

	::GetLocalTime(&Time);//本地时间
	CString TIME;
	TIME.Format(_T("[%d-%d-%d %d:%d:%d] "),
		Time.wYear,Time.wMonth,Time.wDay,
		Time.wHour,Time.wMinute,Time.wSecond);

	str_Display=TIME+str_Display;

	//之前记录
	CString str_Record;
	GetDlgItemText(IDC_EDIT_DISPLAY,str_Record);
	str_Display=str_Display+_T("\r\n");
	str_Display=str_Record+str_Display;

	SetDlgItemText(IDC_EDIT_DISPLAY,str_Display);
	//===========================================本地显示

	SetDlgItemText(IDC_EDIT_INPUT,_T(""));//清空编辑框信息
	m_Edit_Input.SetFocus();//让光标回到编辑框

}