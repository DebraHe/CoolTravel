#pragma once


// CDlgAboutMember �Ի���

class CDlgAboutMember : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAboutMember)

public:
	CDlgAboutMember(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAboutMember();

// �Ի�������
	enum { IDD = IDD_About_Member };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_list_member;
	int InitListCtrlStyle(void);
	int RefreshListCtrlData(void);
};
