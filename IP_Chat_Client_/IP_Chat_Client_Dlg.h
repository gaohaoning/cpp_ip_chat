
// IP_Chat_Client_Dlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CIP_Chat_Client_Dlg �Ի���
class CIP_Chat_Client_Dlg : public CDialog
{
// ����
public:
	CIP_Chat_Client_Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IP_CHAT_CLIENT__DIALOG };

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
	CEdit m_Edit_Input;
	afx_msg void OnDestroy();
	int Init_Socket_Client(void);

	SOCKET m_sock_Client;

	afx_msg void OnBnClickedButtonSend();
	CIPAddressCtrl m_IP_Remote;

	_SYSTEMTIME Time;
};
