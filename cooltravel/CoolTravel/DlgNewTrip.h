#pragma once


#include "explorer1.h"
#include <MsHTML.h>

#include "shellapi.h"
#include <Windows.h>
#include "DlgTripName.h"
#include "exif.h"
#include "TraButton.h"  //͸����ť
// CDlgNewTrip �Ի���

class CDlgNewTrip : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgNewTrip)

public:
	CDlgNewTrip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgNewTrip();

// �Ի�������
	enum { IDD = IDD_NewTrip };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//��ҳ
	CExplorer1 m_web;
	CString GetMoudulePath();
	afx_msg void OnBnClickedButtonAddrode();
	CString filenametxt;
	CString m_TripName,filenameDirectory;
	char     savepath[MAX_PATH];  
	EXIFINFO m_exifinfo;
	CString GetFileTitleFromFileName(CString FileName, BOOL Ext);
	afx_msg void OnBnClickedButtonsavepath();
	afx_msg void OnBnClickedButtonTripname();
	afx_msg void OnBnClickedButtonAdddarry();
	afx_msg void OnBnClickedButtonSavepic();
	afx_msg void OnBnClickedButtonPicin();
	afx_msg void OnBnClickedButtonSavetrack();

	//͸����ť
	CTraButton m_btn1;
	CTraButton m_btn2;
	CTraButton m_btn3;
	CTraButton m_btn4;
	CTraButton m_btn5;
	CTraButton m_btn6;
	CTraButton m_btn7;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);  //���ڲ��ƶ�

	//���ݿ�
	//void readTripPic();

	CString PicPath[500];
};
