
// CoolTravelDlg.h : ͷ�ļ�
//
#include "DlgNewTrip.h"
#include "DlgOldTrip.h"
#include "TraButton.h"  //͸����ť

#include "DlgPicExif.h"
#include "DlgAboutMF.h"
#include "DlgHelp.h"

#pragma once


// CCoolTravelDlg �Ի���
class CCoolTravelDlg : public CDialogEx
{
// ����
public:
	CCoolTravelDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_COOLTRAVEL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


//������ͼ���ر���ͼƬ
private:
	CDC       m_dcMain;
	CBitmap   m_bmpMain;
	CDC       m_dcBk;
	CBitmap   m_bmpBk;
public:
	void LoadDlgBk(int iBmpID);  //���ر���ͼƬ


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()


public:
	//������ͼ�����ر���ͼƬ
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnMenuStyle3();
	afx_msg void OnMenuStyle1();
	afx_msg void OnMenuStyle2();
	afx_msg void OnMenuStyle4();
	afx_msg void OnMenuStyle5();

	//�½�������ǩҳ
	CDlgNewTrip *m_DlgNewTrip;
	CDlgOldTrip *m_DlgOldTrip;
	afx_msg void OnBnClickedLookoldtrip();
	afx_msg void OnBnClickedSetnewtrip();
public:
	//͸����ť
	CTraButton m_btn1;
	CTraButton m_btn2;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
public:
	//����Ƭ��Ϣ��ȡ��
	CDlgPicExif *m_pDlgPicExif;	
	afx_msg void OnPicExif();



	afx_msg void OnHelp();
	afx_msg void OnAbout();
};
