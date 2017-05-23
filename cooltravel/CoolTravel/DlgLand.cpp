// DlgLand.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgLand.h"
#include "afxdialogex.h"


// CDlgLand 对话框

IMPLEMENT_DYNAMIC(CDlgLand, CDialogEx)

CDlgLand::CDlgLand(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgLand::IDD, pParent)
{

}

CDlgLand::~CDlgLand()
{
}

void CDlgLand::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT7, m_name);
	DDX_Control(pDX, IDC_EDIT8, m_password);

	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE,
		GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE) ^ 0x80000);
	HINSTANCE hInst = LoadLibrary("User32.DLL");  //加载库文件
	if (hInst)
	{
		typedef BOOL(WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);
		MYFUNC func = NULL;	 //函数指针
		//取得SetLayeredWindowAttributes函数指针 
		func = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		//使用SetLayeredWindowAttributes函数设定透明度
		if (func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 230, 0x2);
		FreeLibrary(hInst);
	}
}


BEGIN_MESSAGE_MAP(CDlgLand, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgLand::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgLand::OnClickedButton2)
END_MESSAGE_MAP()


// CDlgLand 消息处理程序


void CDlgLand::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	CString c, b;
	m_name.GetWindowText(c);
	m_password.GetWindowText(b);

	if (c.IsEmpty() || b.IsEmpty())
	{
		MessageBox(_T("用户名或密码不能为空！"), _T("用户登录信息"));
		return;
	}
	else if (c == "YY"&&b == "1234")
	{
		//MessageBox(_T("测试成功！"), _T("登陆"));//这句可有可无

	}
	else
	{
		MessageBox(_T("用户名或密码不正确"), _T("提示"));
		return;
	}
	CDialogEx::OnOK();
}


HBRUSH CDlgLand::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)

	{
		pDC->SetTextColor(RGB(0, 0, 0)); //字体颜色
		pDC->SetBkMode(TRANSPARENT);// 背景透明

	}

	return hbr;
}


void CDlgLand::OnClickedButton2()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
