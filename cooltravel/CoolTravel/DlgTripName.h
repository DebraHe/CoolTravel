#pragma once


// CDlgTripName �Ի���

class CDlgTripName : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgTripName)

public:
	CDlgTripName(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTripName();

// �Ի�������
	enum { IDD = IDD_Dlg_TripName };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_TripNameSon;
};
