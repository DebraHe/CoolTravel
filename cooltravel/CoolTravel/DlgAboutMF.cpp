// DlgAboutMF.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgAboutMF.h"
#include "afxdialogex.h"


// CDlgAboutMF 对话框

IMPLEMENT_DYNAMIC(CDlgAboutMF, CDialogEx)

CDlgAboutMF::CDlgAboutMF(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAboutMF::IDD, pParent)
{

}

CDlgAboutMF::~CDlgAboutMF()
{
}

void CDlgAboutMF::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_AboutMF, m_tab_About);


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
		if(func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 170, 0x2); 
		FreeLibrary(hInst); 
	}

	CRect tabRect;
	m_tab_About.InsertItem(0,_T("项目小组成员"));//插入第一个标签
	m_tab_About.InsertItem(1,_T("项目主要功能"));//插入第二个标签
	m_TabAboutMember.Create(IDD_About_Member,&m_tab_About);//创建第一个标签页
	m_TabAboutFunction.Create(IDD_About_Function,&m_tab_About);//创建第二个标签页
	m_tab_About.GetClientRect(&tabRect); //获取标签控件的属性
	//调整tabRect的大小，让它覆盖范围适合这个标签页	
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 21;
	tabRect.bottom -= 2;
	//根据调整好的tabRect，放置两个标签页，并把第一个设置为显示，第二个设置为隐藏
	m_TabAboutMember.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);
	m_TabAboutFunction.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);
}


BEGIN_MESSAGE_MAP(CDlgAboutMF, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_AboutMF, &CDlgAboutMF::OnSelchangeTabAboutmf)
END_MESSAGE_MAP()


// CDlgAboutMF 消息处理程序
void CDlgAboutMF::OnSelchangeTabAboutmf(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;

	CRect tabRect;

	m_tab_About.GetClientRect(&tabRect); //获取标签控件的属性

	//调整tabRect的大小，让它覆盖范围适合这个标签页
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 21;
	tabRect.bottom -= 2;

	switch(m_tab_About.GetCurSel())
	{
		//根据调整好的tabRect，放置两个标签页，并把第一个设置为显示，第二个设置为隐藏
	case 0:		
		m_TabAboutMember.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);
		m_TabAboutFunction.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);
		break;

		//根据调整好的tabRect，放置两个标签页，并把第二个设置为显示，一个设置为隐藏
	case 1:		
		m_TabAboutMember.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);
		m_TabAboutFunction.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);

	default:
		break;
	}
}