#pragma once


// CDlgAboutFunction �Ի���

class CDlgAboutFunction : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAboutFunction)

public:
	CDlgAboutFunction(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgAboutFunction();

// �Ի�������
	enum { IDD = IDD_About_Function };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
