#pragma once

#include "exif.h"

#include "atlimage.h"
#include "istream"
// CDlgPicExif 对话框

static CString s;

class CDlgPicExif : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPicExif)

public:
	CDlgPicExif(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgPicExif();

// 对话框数据
	enum { IDD = IDD_Pic_Exif };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	EXIFINFO m_exifinfo;
	DECLARE_MESSAGE_MAP()

public:
	bool PromptForFileName(CString& fileName, UINT nIDSTitle, DWORD dwFlags, bool bOpenFileDialog, int* pType);
	void ShowInfo(void);
	afx_msg void OnBnClickedButtonOn();
	afx_msg void OnBnClickedButtonOut();	
	afx_msg void OnBnClickedButtonMessage();
	CStatic m_ShowPicture;
};
