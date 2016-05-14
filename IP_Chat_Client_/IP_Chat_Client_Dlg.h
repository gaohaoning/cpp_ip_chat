
// IP_Chat_Client_Dlg.h : 头文件
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CIP_Chat_Client_Dlg 对话框
class CIP_Chat_Client_Dlg : public CDialog
{
// 构造
public:
	CIP_Chat_Client_Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IP_CHAT_CLIENT__DIALOG };

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
	CEdit m_Edit_Input;
	afx_msg void OnDestroy();
	int Init_Socket_Client(void);

	SOCKET m_sock_Client;

	afx_msg void OnBnClickedButtonSend();
	CIPAddressCtrl m_IP_Remote;

	_SYSTEMTIME Time;
};
