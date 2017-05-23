// DlgAboutFunction.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgAboutFunction.h"
#include "afxdialogex.h"


// CDlgAboutFunction 对话框

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


// CDlgAboutFunction 消息处理程序
HBRUSH CDlgAboutFunction::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if(nCtlColor == CTLCOLOR_STATIC )
	{
		pDC->SetBkMode(TRANSPARENT);//设置背景透明
		pDC->SetTextColor(RGB(0,0,0));//设置字体为黑色
		return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}