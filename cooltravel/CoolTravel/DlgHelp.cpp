// DlgHelp.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgHelp.h"
#include "afxdialogex.h"


// CDlgHelp 对话框

IMPLEMENT_DYNAMIC(CDlgHelp, CDialogEx)

CDlgHelp::CDlgHelp(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgHelp::IDD, pParent)
{

}

CDlgHelp::~CDlgHelp()
{
}

void CDlgHelp::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE_Help, m_treeHelp);
	DDX_Control(pDX, IDC_LIST_Help, m_listHelp);


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


	m_listHelp.InsertColumn(0,_T("功能描述"),0,500);	

	HTREEITEM hMyTrip =m_treeHelp.InsertItem(_T("我的行程"),TVI_ROOT,TVI_LAST);
	m_treeHelp.InsertItem(_T("新增行程"),hMyTrip,TVI_LAST);
	m_treeHelp.InsertItem(_T("行程保存"),hMyTrip,TVI_LAST);
	m_treeHelp.InsertItem(_T("查询行程"),hMyTrip,TVI_LAST);
	m_treeHelp.InsertItem(_T("浏览行程"),hMyTrip,TVI_LAST);

	m_treeHelp.InsertItem(_T("地图加载"),TVI_ROOT,TVI_LAST);

	m_treeHelp.InsertItem(_T("照片信息提取"),TVI_ROOT,TVI_LAST);

	m_treeHelp.InsertItem(_T("背景切换"),TVI_ROOT,TVI_LAST);

	m_treeHelp.InsertItem(_T("关于"),TVI_ROOT,TVI_LAST);


	//展开到指定的节点
	m_treeHelp.Expand(hMyTrip,TVE_EXPAND);
}


BEGIN_MESSAGE_MAP(CDlgHelp, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_TREE_Help, &CDlgHelp::OnNMClickTreeHelp)
END_MESSAGE_MAP()


// CDlgHelp 消息处理程序
void CDlgHelp::OnNMClickTreeHelp(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	*pResult = 0;
	//获取用户点击时鼠标的位置
	CPoint point;
	GetCursorPos(&point);

	//将鼠标坐标转换为树控件上的坐标
	CPoint pointInTree =point;
	m_treeHelp.ScreenToClient(&pointInTree);

	//判断当前用户在哪一个节点上点选
	HTREEITEM hCurItem;
	UINT flag = TVHT_ONITEM;
	hCurItem =m_treeHelp.HitTest(pointInTree,&flag);

	//判断当前选中的节点是否为空
	if(hCurItem!=NULL)
	{
		CString csItem =m_treeHelp.GetItemText(hCurItem);

		if(csItem.Compare(_T("新增行程"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("“新增行程”包括三个模块"));
			m_listHelp.InsertItem(1,_T("分别是：行程设定（按关键字）、照片导入、行程日记"));
			m_listHelp.InsertItem(2,_T("其中，“照片导入”模块又分为 单张导入、批量导入 两个模块"));
			m_listHelp.InsertItem(3,_T("行程设定（按关键字）：按关键字设定行程"));
			m_listHelp.InsertItem(4,_T("照片导入：新增加的图片（单张或批量）导入当前界面"));
			m_listHelp.InsertItem(5,_T("行程日记：写入关于此段旅途的游记及心得"));
		}
		else if(csItem.Compare(_T("行程保存"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("“行程保存”包括三个模块"));
			m_listHelp.InsertItem(1,_T("分别是：保存轨迹、保存图片、保存日记"));
			m_listHelp.InsertItem(2,_T("保存轨迹：保存当前通过酷行靓影行程记录系统软件形成的轨迹"));
			m_listHelp.InsertItem(3,_T("保存图片：新增加的图片（单张或批量）导入到用户路线并保存"));
			m_listHelp.InsertItem(4,_T("保存日记：保存关于此段旅途的游记及心得"));

		}
		else if(csItem.Compare(_T("查询行程"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("“查询行程”包括两个模块"));
			m_listHelp.InsertItem(1,_T("分别是：按时间查询、按地域查询"));
			m_listHelp.InsertItem(2,_T("按时间查询：对于所记录的用户的行程，按照时间进行查找"));
			m_listHelp.InsertItem(3,_T("按地域查询：对于所记录的用户的行程，按照地域进行查找"));
		}
		else if(csItem.Compare(_T("浏览行程"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("“浏览行程”包括三个模块"));
			m_listHelp.InsertItem(1,_T("分别是：显示行程轨迹、查看照片、查看日志"));
			m_listHelp.InsertItem(2,_T("其中，“查看照片”模块又分为 单张查看、批量查看 两个模块"));
			m_listHelp.InsertItem(3,_T("显示行程轨迹：根据酷行靓影行程记录系统软件形成的轨迹显示在当前界面上"));
			m_listHelp.InsertItem(4,_T("查看照片：查看导入的图片（单张或批量）"));
			m_listHelp.InsertItem(5,_T("查看日志：查看关于旅途的游记及心得"));
		}
		else if(csItem.Compare(_T("地图加载"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("地图加载：加载百度地图到界面"));
		}
		else if(csItem.Compare(_T("照片信息提取"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("照片信息提取：打开照片并提取照片的exif信息"));
		}
		else if(csItem.Compare(_T("背景切换"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("“背景切换”包括五种不同的风格"));
			m_listHelp.InsertItem(1,_T("分别是：波涛汹涌、非是主流、浩瀚星空、唯美花草、夕阳风车"));
		}
		else if(csItem.Compare(_T("关于"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("“关于”分为两个模块"));
			m_listHelp.InsertItem(1,_T("分别是：项目小组成员、项目主要功能"));
			m_listHelp.InsertItem(2,_T("项目小组成员：介绍了我们这个酷行靓影行程记录系统第四组的六个成员"));
			m_listHelp.InsertItem(3,_T("项目主要功能：笼统的阐述了酷行靓影行程记录系统的大致功能"));
		}
		else
		{
			m_listHelp.DeleteAllItems();
		}
	}
}
