// DlgTripName.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgTripName.h"
#include "afxdialogex.h"


// CDlgTripName 对话框

IMPLEMENT_DYNAMIC(CDlgTripName, CDialogEx)

CDlgTripName::CDlgTripName(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTripName::IDD, pParent)
{

	m_TripNameSon = _T("");
}

CDlgTripName::~CDlgTripName()
{
}

void CDlgTripName::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_TripNameSon);
	DDV_MaxChars(pDX, m_TripNameSon, 256);

	//设置透明度
	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, 
		GetWindowLong(this->GetSafeHwnd(),GWL_EXSTYLE)^0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL");  //加载库文件
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC func = NULL;	 //函数指针
		//取得SetLayeredWindowAttributes函数指针 
		func = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		//使用SetLayeredWindowAttributes函数设定透明度
		if(func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 230, 0x2); 
		FreeLibrary(hInst); 
	}	
}


BEGIN_MESSAGE_MAP(CDlgTripName, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTripName::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgTripName::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgTripName 消息处理程序


void CDlgTripName::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);//TRUE 把编辑框里面的数据-》绑定的变量里面
	CDialogEx::OnOK();
}


void CDlgTripName::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
