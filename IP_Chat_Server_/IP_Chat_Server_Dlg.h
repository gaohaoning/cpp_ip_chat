
// IP_Chat_Server_Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CIP_Chat_Server_Dlg �Ի���
class CIP_Chat_Server_Dlg : public CDialog
{
// ����
public:
	CIP_Chat_Server_Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IP_CHAT_SERVER__DIALOG };

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