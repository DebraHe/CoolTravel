#pragma once


// CDlgTripName 对话框

class CDlgTripName : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTripName)

public:
	CDlgTripName(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgTripName();

// 对话框数据
	enum { IDD = IDD_Dlg_TripName };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_TripNameSon;
};
