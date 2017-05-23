#pragma once
#include "afxcmn.h"

// CDlgHelp 对话框

class CDlgHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHelp)

public:
	CDlgHelp(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgHelp();

// 对话框数据
	enum { IDD = IDD_Dlg_Help };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CTreeCtrl m_treeHelp;
	CListCtrl m_listHelp;
	afx_msg void OnNMClickTreeHelp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeHelp(NMHDR *pNMHDR, LRESULT *pResult);
};
