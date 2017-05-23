#pragma once


// CDlgAboutMember 对话框

class CDlgAboutMember : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAboutMember)

public:
	CDlgAboutMember(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAboutMember();

// 对话框数据
	enum { IDD = IDD_About_Member };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_list_member;
	int InitListCtrlStyle(void);
	int RefreshListCtrlData(void);
};
