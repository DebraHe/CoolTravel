#pragma once
#include "afxcmn.h"

// CDlgHelp �Ի���

class CDlgHelp : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgHelp)

public:
	CDlgHelp(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgHelp();

// �Ի�������
	enum { IDD = IDD_Dlg_Help };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CTreeCtrl m_treeHelp;
	CListCtrl m_listHelp;
	afx_msg void OnNMClickTreeHelp(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnTvnSelchangedTreeHelp(NMHDR *pNMHDR, LRESULT *pResult);
};
