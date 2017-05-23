
// CoolTravelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "CoolTravelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoolTravelDlg 对话框




CCoolTravelDlg::CCoolTravelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCoolTravelDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_DlgNewTrip = NULL;
	m_DlgOldTrip = NULL;
	m_pDlgPicExif =NULL;
}

void CCoolTravelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LookOldTrip, m_btn1);
	DDX_Control(pDX, IDC_SetNewTrip, m_btn2);
}

BEGIN_MESSAGE_MAP(CCoolTravelDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(ID_MENU_STYLE3, &CCoolTravelDlg::OnMenuStyle3)
	ON_COMMAND(ID_MENU_STYLE1, &CCoolTravelDlg::OnMenuStyle1)
	ON_COMMAND(ID_MENU_STYLE2, &CCoolTravelDlg::OnMenuStyle2)
	ON_COMMAND(ID_MENU_STYLE4, &CCoolTravelDlg::OnMenuStyle4)
	ON_COMMAND(ID_MENU_STYLE5, &CCoolTravelDlg::OnMenuStyle5)
	ON_BN_CLICKED(IDC_LookOldTrip, &CCoolTravelDlg::OnBnClickedLookoldtrip)
	ON_BN_CLICKED(IDC_SetNewTrip, &CCoolTravelDlg::OnBnClickedSetnewtrip)
	ON_COMMAND(ID_Pic_Exif, &CCoolTravelDlg::OnPicExif)
	ON_COMMAND(ID_HELP, &CCoolTravelDlg::OnHelp)
	ON_COMMAND(ID_About, &CCoolTravelDlg::OnAbout)
END_MESSAGE_MAP()


// CCoolTravelDlg 消息处理程序

BOOL CCoolTravelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	//背景图片
	this->MoveWindow(0,0,1000,640,true);
	LoadDlgBk(IDB_BITMAP3);

	//透明窗体
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
		if(func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 240, 0x2); 
		FreeLibrary(hInst); 
	}

	//创建子窗体
	CStatic *pFrame = (CStatic *)GetDlgItem(IDC_MAIN_FRAME);
	RECT rect;
	pFrame->GetClientRect(&rect);
	rect.left += 2;
	rect.top  += 2;
	rect.right -= 2;
	rect.bottom -= 2;

	m_DlgOldTrip = new CDlgOldTrip;
	m_DlgOldTrip->Create(IDD_OldTrip, pFrame);
	m_DlgOldTrip->MoveWindow(&rect);
	m_DlgOldTrip->ShowWindow(SW_SHOW);

	m_DlgNewTrip = new CDlgNewTrip;
	m_DlgNewTrip->Create(IDD_NewTrip, pFrame);
	m_DlgNewTrip->MoveWindow(&rect);
	m_DlgNewTrip->ShowWindow(SW_HIDE);
	//创建子窗体结束

	//透明按钮
	m_btn1.Load(IDB_PNG1, 244);
	m_btn2.Load(IDB_PNG1, 244);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCoolTravelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//获取客户区域的大小
		CRect rect;
		GetClientRect(rect);

		CPaintDC dc(this);
		dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcMain, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

HBRUSH CCoolTravelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//消除文本框的背景
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
	if(   CTLCOLOR_STATIC   ==   nCtlColor   )  
	{ 
		//pDC->SetBkColor(RGB(255,0,0));  //需要指定背景色的时候用 
		pDC->SetTextColor(RGB(255,   255,   255));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明 
	}  
	return hbr;
} 

void CCoolTravelDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCoolTravelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//掩码贴图背景
void CCoolTravelDlg::LoadDlgBk(int iBmpID)
{
	//释放资源
	m_dcMain.DeleteDC();
	m_dcBk.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBk.DeleteObject();

	//获取客户区域大小
	CRect   rect;
	GetClientRect(rect);

	//绘制背景
	CClientDC  dc(this);
	m_dcMain.CreateCompatibleDC(&dc);
	m_bmpMain.CreateCompatibleBitmap(&dc,rect.right,rect.bottom);
	m_dcMain.SelectObject(&m_bmpMain);

	m_dcBk.CreateCompatibleDC(&m_dcMain);
	m_bmpBk.LoadBitmap(iBmpID);
	m_dcBk.SelectObject(m_bmpBk);


	m_dcMain.SetStretchBltMode(STRETCH_HALFTONE);

	m_dcMain.StretchBlt(0,0,rect.right,rect.bottom,&m_dcBk,0,0,1000,640,SRCCOPY);

	Invalidate(FALSE);
}


void CCoolTravelDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码

	//释放资源
	m_dcMain.DeleteDC();
	m_dcBk.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBk.DeleteObject();
}


void CCoolTravelDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CCoolTravelDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnOK();
}


void CCoolTravelDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	CDialogEx::OnCancel();
}


void CCoolTravelDlg::OnMenuStyle3()
{
	// TODO: 在此添加命令处理程序代码
	LoadDlgBk(IDB_BITMAP3);
}


void CCoolTravelDlg::OnMenuStyle1()
{
	// TODO: 在此添加命令处理程序代码
	LoadDlgBk(IDB_BITMAP1);
}


void CCoolTravelDlg::OnMenuStyle2()
{
	// TODO: 在此添加命令处理程序代码
	LoadDlgBk(IDB_BITMAP2);
}


void CCoolTravelDlg::OnMenuStyle4()
{
	// TODO: 在此添加命令处理程序代码
	LoadDlgBk(IDB_BITMAP4);
}


void CCoolTravelDlg::OnMenuStyle5()
{
	// TODO: 在此添加命令处理程序代码
	LoadDlgBk(IDB_BITMAP5);
}
//掩码贴图背景结束

//查看以往行程
void CCoolTravelDlg::OnBnClickedLookoldtrip()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DlgOldTrip->dataupdate();
	m_DlgOldTrip->ShowWindow(SW_SHOW);
	m_DlgNewTrip->ShowWindow(SW_HIDE);
	
}

//新建一个行程
void CCoolTravelDlg::OnBnClickedSetnewtrip()
{
	// TODO: 在此添加控件通知处理程序代码
	m_DlgNewTrip->ShowWindow(SW_SHOW);
	m_DlgOldTrip->ShowWindow(SW_HIDE);
}


void CCoolTravelDlg::OnPicExif()
{
	// TODO: 在此添加命令处理程序代码
	if (NULL == m_pDlgPicExif)   
	{   
		// 创建非模态对话框实例   
		m_pDlgPicExif = new CDlgPicExif();   
		m_pDlgPicExif->Create(IDD_Pic_Exif, this);   
	}   
	// 显示非模态对话框   
	m_pDlgPicExif->ShowWindow(SW_SHOW);   

	// 将各控件中的数据保存到相应的变量   
	UpdateData(TRUE);   
}


void CCoolTravelDlg::OnHelp()
{
	// TODO: 在此添加命令处理程序代码
	CDlgHelp m_dlgHelp;
	m_dlgHelp.DoModal();
}


void CCoolTravelDlg::OnAbout()
{
	// TODO: 在此添加命令处理程序代码
	CDlgAboutMF m_dlgAbout;
	m_dlgAbout.DoModal();
}
