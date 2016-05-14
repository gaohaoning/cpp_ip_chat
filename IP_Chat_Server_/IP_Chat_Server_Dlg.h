
// IP_Chat_Server_Dlg.h : 头文件
//

#pragma once
#include "afxcmn.h"


// CIP_Chat_Server_Dlg 对话框
class CIP_Chat_Server_Dlg : public CDialog
{
// 构造
public:
	CIP_Chat_Server_Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IP_CHAT_SERVER__DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDestroy();
	int Init_Socket_Server(void);
	int Init_Socket_Server_IP(void);

	SOCKADDR_IN m_Addr_Local;
	SOCKET m_sock_Server;

	HANDLE hThread_Recv;

	int Server_Recv(void);

	static DWORD WINAPI Recv_ThreadProc(LPVOID lpParameter);

	//=====================================================
	afx_msg LRESULT On_Recv_Data(WPARAM wParam,LPARAM lParam);
	//=====================================================

	_SYSTEMTIME Time;
	CIPAddressCtrl m_IP_Local;
};


#define WM_RECV_DATA WM_USER+1

class Recv_Parameter
{
public:
	SOCKET sock;
	HWND hwnd;
};