#pragma once


// CDlgAboutFunction 对话框

class CDlgAboutFunction : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgAboutFunction)

public:
	CDlgAboutFunction(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgAboutFunction();

// 对话框数据
	enum { IDD = IDD_About_Function };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
