// DlgAboutMember.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgAboutMember.h"
#include "afxdialogex.h"


// CDlgAboutMember �Ի���

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
	InitListCtrlStyle(); //���÷�����ʼ��ListCtrl����ʽ
	RefreshListCtrlData(); //ˢ��ListCtrl������
}


BEGIN_MESSAGE_MAP(CDlgAboutMember, CDialogEx)
END_MESSAGE_MAP()


// CDlgAboutMember ��Ϣ�������
int CDlgAboutMember::InitListCtrlStyle(void)
{
	//���ListCtrl�Ŀ��
	CRect rect;
	m_list_member.GetClientRect(&rect);
	int nColInterval = rect.Width();

	//����ListCtrl����ʽ
	m_list_member.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);

	//�������������������еĶ����ʽ���п�


	m_list_member.InsertColumn(0, _T("С���Ա"), LVCFMT_CENTER, int (nColInterval * 0.2));
	m_list_member.InsertColumn(1, _T("��Աְλ"), LVCFMT_CENTER, int (nColInterval * 0.2));
	m_list_member.InsertColumn(2, _T("��Ա�Ը�"), LVCFMT_CENTER, int (nColInterval * 0.6));


	return 0;
}

//ˢ��ListControl������
int CDlgAboutMember::RefreshListCtrlData(void)
{
	int i;
	for(i = 0; i < 6; i++)
	{
		CString temp;
		//���ListCtrl�ĵ�ǰ��¼���ݵ�����iItemCount
		int iItemCount = m_list_member.GetItemCount();
		m_list_member.InsertItem(iItemCount, temp);

		//��iItemCount�����һ�����ݣ�������С���Ա
		switch(i)
		{
		case 0:
			m_list_member.SetItemText(iItemCount, 0, _T("������"));			
			break;
		case 1:
			m_list_member.SetItemText(iItemCount, 0, _T("�غ� "));
			break;
		case 2:
			m_list_member.SetItemText(iItemCount, 0, _T("� "));			
			break;
		case 3:
			m_list_member.SetItemText(iItemCount, 0,_T("���� "));
			break;
		case 4:
			m_list_member.SetItemText(iItemCount, 0, _T("������"));
			break;
		default:
			m_list_member.SetItemText(iItemCount, 0, _T("��־Զ"));
			break;
		}

		//��iItemCount����ڶ������ݣ��������Աְλ
		if(i==0)
			m_list_member.SetItemText(iItemCount, 1, _T("�鳤"));
		else
			m_list_member.SetItemText(iItemCount, 1, _T("��Ա"));

		//��iItemCount����ڶ������ݣ��������Ա�Ը�
		switch(i)
		{
		case 0:
			m_list_member.SetItemText(iItemCount, 2, _T("���ǵ��鳤����,�ǵ���ͳԷ� = ="));			
			break;
		case 1:
			m_list_member.SetItemText(iItemCount, 2, _T("���Լ�����ûɶ˵�ģ��Ի� = ="));
			break;
		case 2:
			m_list_member.SetItemText(iItemCount, 2, _T("�ҵĻ�����磬�е����ɧ = ="));			
			break;
		case 3:
			m_list_member.SetItemText(iItemCount, 2,_T("�鳤���˵ĺû��� = = ��������"));
			break;
		case 4:
			m_list_member.SetItemText(iItemCount, 2, _T("��������ɧ = ="));
			break;
		default:
			m_list_member.SetItemText(iItemCount, 2, _T("�������Ǹ�С���Ӱ� = ="));
			break;
		}
	}
	return 0;
}