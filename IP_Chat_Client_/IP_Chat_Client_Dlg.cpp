
// IP_Chat_Client_Dlg.cpp : 实现文件
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


// CIP_Chat_Client_Dlg 对话框




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


// CIP_Chat_Client_Dlg 消息处理程序

BOOL CIP_Chat_Client_Dlg::OnInitDialog()
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
	//===========================================加载套接字库 V1.1
	//AfxSocketInit 函数内部调用了 WSAStartup 并且保证程序结束前调用 WSACleanup (不需包含ws2_32.h)
	if (!AfxSocketInit())
	{
		AfxMessageBox(_T("Failed to Initialize Sockets"), MB_OK | MB_ICONSTOP);
		return FALSE;
	}
	//===========================================加载套接字库 V1.1

	Init_Socket_Client();

	//==================================设置默认的IP地址
	SetDlgItemText(IDC_IPADDRESS_REMOTE,_T("127.0.0.1"));
	//==================================设置默认的IP地址

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIP_Chat_Client_Dlg::OnPaint()
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
HCURSOR CIP_Chat_Client_Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


void CIP_Chat_Client_Dlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
}

int CIP_Chat_Client_Dlg::Init_Socket_Client(void)
{

	//===========================================创建 socket
	m_sock_Client=socket(AF_INET,SOCK_DGRAM,0);
	// TCP:SOCK_STREAM
	// UDP:SOCK_DGRAM
	//===========================================创建 socket

	return 0;
}

void CIP_Chat_Client_Dlg::OnBnClickedButtonSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//======================@@@@@@@@@@@@@@@@@@@@@@=====================设置目的地址

	////==================================设置默认的IP地址
	//SetDlgItemText(IDC_IPADDRESS_REMOTE,_T("127.0.0.1"));
	////==================================设置默认的IP地址

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

	/*char * sendBuf=new char[inf.GetLength()];
	for(int i=0;i<inf.GetLength();i++)
	{
		*(sendBuf+i)=inf.GetAt(i);
	}*/

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
