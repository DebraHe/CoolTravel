#pragma once
#include "afxwin.h"


// CDlgLand �Ի���

class CDlgLand : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLand)

public:
	CDlgLand(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgLand();

// �Ի�������
	enum { IDD = IDD_Land };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_name;
	CEdit m_password;
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedButton2();
};
