#pragma once


// CDlgTripPic �Ի���

class CDlgTripPic : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTripPic)

public:
	CDlgTripPic(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTripPic();

// �Ի�������
	enum { IDD = IDD_Pic_Trip };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listPic;
	CStatic m_Pic;
	CString path[20];
	afx_msg void OnLvnItemchangedListPic(NMHDR *pNMHDR, LRESULT *pResult);
	void LoadPic(int n);
};
