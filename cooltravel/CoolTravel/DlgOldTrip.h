#pragma once
#include "explorer1.h"
#include <MsHTML.h>
#include "shellapi.h"
#include <Windows.h>
#include "exif.h"
#include "TraButton.h"  //͸����ť

#include "explorer1.h"
#include <MsHTML.h>

#include "DlgTripPic.h"
// CDlgOldTrip �Ի���

class CDlgOldTrip : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgOldTrip)

public:
	CDlgOldTrip(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgOldTrip();

// �Ի�������
	enum { IDD = IDD_OldTrip };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);    //���ڲ��ƶ�

	//��ҳ
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
	//�г����ݿ�
	CString m_trip;
	CListCtrl m_list;
	afx_msg void OnLvnItemchangedListTripname(NMHDR *pNMHDR, LRESULT *pResult);


	//ɾ���г�
	bool DeleteDirectory(CString DirName);
	
	void dataupdate();
};
