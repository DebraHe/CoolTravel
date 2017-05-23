#pragma once
#include "explorer1.h"
#include <MsHTML.h>
#include "shellapi.h"
#include <Windows.h>
#include "exif.h"
#include "TraButton.h"  //透明按钮

#include "explorer1.h"
#include <MsHTML.h>

#include "DlgTripPic.h"
// CDlgOldTrip 对话框

class CDlgOldTrip : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOldTrip)

public:
	CDlgOldTrip(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgOldTrip();

// 对话框数据
	enum { IDD = IDD_OldTrip };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);    //窗口不移动

	//网页
	EXIFINFO m_exifinfo;
	CExplorer1 m_oldmap;
	CString GetMoudulePath();
	afx_msg void OnBnClickedButtonLoadpoint();
	afx_msg void OnBnClickedButtonDeletetrip();
	afx_msg void OnBnClickedButtonLookpic();
	afx_msg void OnBnClickedButtonLooktrack();
	void GetInfo(CString str);
	CString PicPath[500];
	double JD[500],WD[500];
	int i = -1;
	//行程数据库
	CString m_trip;
	CListCtrl m_list;
	afx_msg void OnLvnItemchangedListTripname(NMHDR *pNMHDR, LRESULT *pResult);


	//删除行程
	bool DeleteDirectory(CString DirName);
	
	void dataupdate();
};
