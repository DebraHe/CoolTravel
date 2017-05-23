#pragma once

#include "exif.h"

#include "atlimage.h"
#include "istream"
// CDlgPicExif �Ի���

static CString s;

class CDlgPicExif : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPicExif)

public:
	CDlgPicExif(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgPicExif();

// �Ի�������
	enum { IDD = IDD_Pic_Exif };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
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
