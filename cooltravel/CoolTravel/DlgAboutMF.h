#pragma once
#include "DlgAboutMember.h"
#include "DlgAboutFunction.h"

// CDlgAboutMF 对话框

class CDlgAboutMF : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAboutMF)

public:
	CDlgAboutMF(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAboutMF();

// 对话框数据
	enum { IDD = IDD_Dlg_About };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab_About;
	CDlgAboutMember m_TabAboutMember;
	CDlgAboutFunction m_TabAboutFunction;
	afx_msg void OnSelchangeTabAboutmf(NMHDR *pNMHDR, LRESULT *pResult);
};
