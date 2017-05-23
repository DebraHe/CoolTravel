#pragma once


// CDlgTripPic 对话框

class CDlgTripPic : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTripPic)

public:
	CDlgTripPic(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTripPic();

// 对话框数据
	enum { IDD = IDD_Pic_Trip };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listPic;
	CStatic m_Pic;
	CString path[20];
	afx_msg void OnLvnItemchangedListPic(NMHDR *pNMHDR, LRESULT *pResult);
	void LoadPic(int n);
};
