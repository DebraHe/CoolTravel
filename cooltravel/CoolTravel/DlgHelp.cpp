// DlgHelp.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgHelp.h"
#include "afxdialogex.h"


// CDlgHelp �Ի���

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
	HINSTANCE hInst = LoadLibrary("User32.DLL");  //���ؿ��ļ�
	if(hInst) 
	{ 
		typedef BOOL (WINAPI *MYFUNC)(HWND,COLORREF,BYTE,DWORD); 
		MYFUNC func = NULL;	 //����ָ��
		//ȡ��SetLayeredWindowAttributes����ָ�� 
		func = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		//ʹ��SetLayeredWindowAttributes�����趨͸����
		if(func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 170, 0x2); 
		FreeLibrary(hInst); 
	}


	m_listHelp.InsertColumn(0,_T("��������"),0,500);	

	HTREEITEM hMyTrip =m_treeHelp.InsertItem(_T("�ҵ��г�"),TVI_ROOT,TVI_LAST);
	m_treeHelp.InsertItem(_T("�����г�"),hMyTrip,TVI_LAST);
	m_treeHelp.InsertItem(_T("�г̱���"),hMyTrip,TVI_LAST);
	m_treeHelp.InsertItem(_T("��ѯ�г�"),hMyTrip,TVI_LAST);
	m_treeHelp.InsertItem(_T("����г�"),hMyTrip,TVI_LAST);

	m_treeHelp.InsertItem(_T("��ͼ����"),TVI_ROOT,TVI_LAST);

	m_treeHelp.InsertItem(_T("��Ƭ��Ϣ��ȡ"),TVI_ROOT,TVI_LAST);

	m_treeHelp.InsertItem(_T("�����л�"),TVI_ROOT,TVI_LAST);

	m_treeHelp.InsertItem(_T("����"),TVI_ROOT,TVI_LAST);


	//չ����ָ���Ľڵ�
	m_treeHelp.Expand(hMyTrip,TVE_EXPAND);
}


BEGIN_MESSAGE_MAP(CDlgHelp, CDialogEx)
	ON_NOTIFY(NM_CLICK, IDC_TREE_Help, &CDlgHelp::OnNMClickTreeHelp)
END_MESSAGE_MAP()


// CDlgHelp ��Ϣ�������
void CDlgHelp::OnNMClickTreeHelp(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	//��ȡ�û����ʱ����λ��
	CPoint point;
	GetCursorPos(&point);

	//���������ת��Ϊ���ؼ��ϵ�����
	CPoint pointInTree =point;
	m_treeHelp.ScreenToClient(&pointInTree);

	//�жϵ�ǰ�û�����һ���ڵ��ϵ�ѡ
	HTREEITEM hCurItem;
	UINT flag = TVHT_ONITEM;
	hCurItem =m_treeHelp.HitTest(pointInTree,&flag);

	//�жϵ�ǰѡ�еĽڵ��Ƿ�Ϊ��
	if(hCurItem!=NULL)
	{
		CString csItem =m_treeHelp.GetItemText(hCurItem);

		if(csItem.Compare(_T("�����г�"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("�������г̡���������ģ��"));
			m_listHelp.InsertItem(1,_T("�ֱ��ǣ��г��趨�����ؼ��֣�����Ƭ���롢�г��ռ�"));
			m_listHelp.InsertItem(2,_T("���У�����Ƭ���롱ģ���ַ�Ϊ ���ŵ��롢�������� ����ģ��"));
			m_listHelp.InsertItem(3,_T("�г��趨�����ؼ��֣������ؼ����趨�г�"));
			m_listHelp.InsertItem(4,_T("��Ƭ���룺�����ӵ�ͼƬ�����Ż����������뵱ǰ����"));
			m_listHelp.InsertItem(5,_T("�г��ռǣ�д����ڴ˶���;���μǼ��ĵ�"));
		}
		else if(csItem.Compare(_T("�г̱���"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("���г̱��桱��������ģ��"));
			m_listHelp.InsertItem(1,_T("�ֱ��ǣ�����켣������ͼƬ�������ռ�"));
			m_listHelp.InsertItem(2,_T("����켣�����浱ǰͨ��������Ӱ�г̼�¼ϵͳ����γɵĹ켣"));
			m_listHelp.InsertItem(3,_T("����ͼƬ�������ӵ�ͼƬ�����Ż����������뵽�û�·�߲�����"));
			m_listHelp.InsertItem(4,_T("�����ռǣ�������ڴ˶���;���μǼ��ĵ�"));

		}
		else if(csItem.Compare(_T("��ѯ�г�"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("����ѯ�г̡���������ģ��"));
			m_listHelp.InsertItem(1,_T("�ֱ��ǣ���ʱ���ѯ���������ѯ"));
			m_listHelp.InsertItem(2,_T("��ʱ���ѯ����������¼���û����г̣�����ʱ����в���"));
			m_listHelp.InsertItem(3,_T("�������ѯ����������¼���û����г̣����յ�����в���"));
		}
		else if(csItem.Compare(_T("����г�"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("������г̡���������ģ��"));
			m_listHelp.InsertItem(1,_T("�ֱ��ǣ���ʾ�г̹켣���鿴��Ƭ���鿴��־"));
			m_listHelp.InsertItem(2,_T("���У����鿴��Ƭ��ģ���ַ�Ϊ ���Ų鿴�������鿴 ����ģ��"));
			m_listHelp.InsertItem(3,_T("��ʾ�г̹켣�����ݿ�����Ӱ�г̼�¼ϵͳ����γɵĹ켣��ʾ�ڵ�ǰ������"));
			m_listHelp.InsertItem(4,_T("�鿴��Ƭ���鿴�����ͼƬ�����Ż�������"));
			m_listHelp.InsertItem(5,_T("�鿴��־���鿴������;���μǼ��ĵ�"));
		}
		else if(csItem.Compare(_T("��ͼ����"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("��ͼ���أ����ذٶȵ�ͼ������"));
		}
		else if(csItem.Compare(_T("��Ƭ��Ϣ��ȡ"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("��Ƭ��Ϣ��ȡ������Ƭ����ȡ��Ƭ��exif��Ϣ"));
		}
		else if(csItem.Compare(_T("�����л�"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("�������л����������ֲ�ͬ�ķ��"));
			m_listHelp.InsertItem(1,_T("�ֱ��ǣ�������ӿ����������������ǿա�Ψ�����ݡ�Ϧ���糵"));
		}
		else if(csItem.Compare(_T("����"))==0)
		{
			m_listHelp.DeleteAllItems();
			m_listHelp.InsertItem(0,_T("�����ڡ���Ϊ����ģ��"));
			m_listHelp.InsertItem(1,_T("�ֱ��ǣ���ĿС���Ա����Ŀ��Ҫ����"));
			m_listHelp.InsertItem(2,_T("��ĿС���Ա���������������������Ӱ�г̼�¼ϵͳ�������������Ա"));
			m_listHelp.InsertItem(3,_T("��Ŀ��Ҫ���ܣ���ͳ�Ĳ����˿�����Ӱ�г̼�¼ϵͳ�Ĵ��¹���"));
		}
		else
		{
			m_listHelp.DeleteAllItems();
		}
	}
}
