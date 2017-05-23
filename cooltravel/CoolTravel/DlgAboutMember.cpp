// DlgAboutMember.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgAboutMember.h"
#include "afxdialogex.h"


// CDlgAboutMember 对话框

IMPLEMENT_DYNAMIC(CDlgAboutMember, CDialogEx)

CDlgAboutMember::CDlgAboutMember(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgAboutMember::IDD, pParent)
{

}

CDlgAboutMember::~CDlgAboutMember()
{
}

void CDlgAboutMember::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Member, m_list_member);
	InitListCtrlStyle(); //调用方法初始化ListCtrl的样式
	RefreshListCtrlData(); //刷新ListCtrl的数据
}


BEGIN_MESSAGE_MAP(CDlgAboutMember, CDialogEx)
END_MESSAGE_MAP()


// CDlgAboutMember 消息处理程序
int CDlgAboutMember::InitListCtrlStyle(void)
{
	//获得ListCtrl的宽度
	CRect rect;
	m_list_member.GetClientRect(&rect);
	int nColInterval = rect.Width();

	//设置ListCtrl的样式
	m_list_member.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//插入列索引、列名、列的对齐格式、列宽


	m_list_member.InsertColumn(0, _T("小组成员"), LVCFMT_CENTER, int (nColInterval * 0.2));
	m_list_member.InsertColumn(1, _T("成员职位"), LVCFMT_CENTER, int (nColInterval * 0.2));
	m_list_member.InsertColumn(2, _T("成员性格"), LVCFMT_CENTER, int (nColInterval * 0.6));


	return 0;
}

//刷新ListControl的数据
int CDlgAboutMember::RefreshListCtrlData(void)
{
	int i;
	for(i = 0; i < 6; i++)
	{
		CString temp;
		//获得ListCtrl的当前记录数据的条数iItemCount
		int iItemCount = m_list_member.GetItemCount();
		m_list_member.InsertItem(iItemCount, temp);

		//在iItemCount插入第一列数据，即插入小组成员
		switch(i)
		{
		case 0:
			m_list_member.SetItemText(iItemCount, 0, _T("秦晓磊"));			
			break;
		case 1:
			m_list_member.SetItemText(iItemCount, 0, _T("贺鹤 "));
			break;
		case 2:
			m_list_member.SetItemText(iItemCount, 0, _T("杨帆 "));			
			break;
		case 3:
			m_list_member.SetItemText(iItemCount, 0,_T("唐天 "));
			break;
		case 4:
			m_list_member.SetItemText(iItemCount, 0, _T("王仪琦"));
			break;
		default:
			m_list_member.SetItemText(iItemCount, 0, _T("俞志远"));
			break;
		}

		//在iItemCount插入第二列数据，即插入成员职位
		if(i==0)
			m_list_member.SetItemText(iItemCount, 1, _T("组长"));
		else
			m_list_member.SetItemText(iItemCount, 1, _T("组员"));

		//在iItemCount插入第二列数据，即插入成员性格
		switch(i)
		{
		case 0:
			m_list_member.SetItemText(iItemCount, 2, _T("我们的组长大人,记得请客吃饭 = ="));			
			break;
		case 1:
			m_list_member.SetItemText(iItemCount, 2, _T("我自己咯，没啥说的，吃货 = ="));
			break;
		case 2:
			m_list_member.SetItemText(iItemCount, 2, _T("我的基友杨哥，有点儿闷骚 = ="));			
			break;
		case 3:
			m_list_member.SetItemText(iItemCount, 2,_T("组长大人的好基友 = = 不敢描述"));
			break;
		case 4:
			m_list_member.SetItemText(iItemCount, 2, _T("真正的闷骚 = ="));
			break;
		default:
			m_list_member.SetItemText(iItemCount, 2, _T("记忆中是个小胖子啊 = ="));
			break;
		}
	}
	return 0;
}