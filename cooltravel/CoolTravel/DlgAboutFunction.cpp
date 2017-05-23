// DlgAboutFunction.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgAboutFunction.h"
#include "afxdialogex.h"


// CDlgAboutFunction �Ի���

IMPLEMENT_DYNAMIC(CDlgAboutFunction, CDialogEx)

CDlgAboutFunction::CDlgAboutFunction(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAboutFunction::IDD, pParent)
{

}

CDlgAboutFunction::~CDlgAboutFunction()
{
}

void CDlgAboutFunction::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgAboutFunction, CDialogEx)
END_MESSAGE_MAP()


// CDlgAboutFunction ��Ϣ�������
HBRUSH CDlgAboutFunction::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT);//���ñ���͸��
		pDC->SetTextColor(RGB(0,0,0));//��������Ϊ��ɫ
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}