#pragma once
#include "afxwin.h"


// CDlgLand 对话框

class CDlgLand : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgLand)

public:
	CDlgLand(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgLand();

// 对话框数据
	enum { IDD = IDD_Land };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_name;
	CEdit m_password;
	afx_msg void OnBnClickedButton1();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnClickedButton2();
};
