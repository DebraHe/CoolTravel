
// CoolTravelDlg.h : 头文件
//
#include "DlgNewTrip.h"
#include "DlgOldTrip.h"
#include "TraButton.h"  //透明按钮

#include "DlgPicExif.h"
#include "DlgAboutMF.h"
#include "DlgHelp.h"

#pragma once


// CCoolTravelDlg 对话框
class CCoolTravelDlg : public CDialogEx
{
// 构造
public:
	CCoolTravelDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_COOLTRAVEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


//掩码贴图加载背景图片
private:
	CDC       m_dcMain;
	CBitmap   m_bmpMain;
	CDC       m_dcBk;
	CBitmap   m_bmpBk;
public:
	void LoadDlgBk(int iBmpID);  //加载背景图片


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	//掩码贴图，加载背景图片
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMenuStyle3();
	afx_msg void OnMenuStyle1();
	afx_msg void OnMenuStyle2();
	afx_msg void OnMenuStyle4();
	afx_msg void OnMenuStyle5();

	//新建两个标签页
	CDlgNewTrip *m_DlgNewTrip;
	CDlgOldTrip *m_DlgOldTrip;
	afx_msg void OnBnClickedLookoldtrip();
	afx_msg void OnBnClickedSetnewtrip();
public:
	//透明按钮
	CTraButton m_btn1;
	CTraButton m_btn2;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	//打开照片信息提取器
	CDlgPicExif *m_pDlgPicExif;	
	afx_msg void OnPicExif();



	afx_msg void OnHelp();
	afx_msg void OnAbout();
};
