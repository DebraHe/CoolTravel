#pragma once
#include "DlgAboutMember.h"
#include "DlgAboutFunction.h"

// CDlgAboutMF �Ի���

class CDlgAboutMF : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAboutMF)

public:
	CDlgAboutMF(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAboutMF();

// �Ի�������
	enum { IDD = IDD_Dlg_About };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tab_About;
	CDlgAboutMember m_TabAboutMember;
	CDlgAboutFunction m_TabAboutFunction;
	afx_msg void OnSelchangeTabAboutmf(NMHDR *pNMHDR, LRESULT *pResult);
};
