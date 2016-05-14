
// IP_Chat_UDP_Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CIP_Chat_UDP_Dlg �Ի���
class CIP_Chat_UDP_Dlg : public CDialog
{
// ����
public:
	CIP_Chat_UDP_Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IP_CHAT_UDP__DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//=================================================Server + Client
	int Initialize_Windows_Sockets(void);
	SOCKADDR_IN m_Addr_Local;

	_SYSTEMTIME Time;
	//=================================================Server + Client

	//=================================================Server
	SOCKET m_sock_Server;
	int Init_Socket_Server(void);
	int Init_Socket_Server_IP(void);

	int Server_Recv(void);
	static DWORD WINAPI Recv_ThreadProc(LPVOID lpParameter);
	afx_msg LRESULT On_Recv_Data(WPARAM wParam,LPARAM lParam);
	HANDLE hThread_Recv;
	//=================================================Server

	//=================================================Client
	SOCKET m_sock_Client;
	int Init_Socket_Client(void);
	afx_msg void OnBnClickedButtonSend();
	CEdit m_Edit_Input;
	//=================================================Client


	CIPAddressCtrl m_IP_Remote;
	CIPAddressCtrl m_IP_Local;
	
};


//=================================================Server
#define WM_RECV_DATA WM_USER+1

class Recv_Parameter
{
public:
	SOCKET sock;
	HWND hwnd;
};
//=================================================Server