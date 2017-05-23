// DlgAboutMF.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgAboutMF.h"
#include "afxdialogex.h"


// CDlgAboutMF �Ի���

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

	CRect tabRect;
	m_tab_About.InsertItem(0,_T("��ĿС���Ա"));//�����һ����ǩ
	m_tab_About.InsertItem(1,_T("��Ŀ��Ҫ����"));//����ڶ�����ǩ
	m_TabAboutMember.Create(IDD_About_Member,&m_tab_About);//������һ����ǩҳ
	m_TabAboutFunction.Create(IDD_About_Function,&m_tab_About);//�����ڶ�����ǩҳ
	m_tab_About.GetClientRect(&tabRect); //��ȡ��ǩ�ؼ�������
	//����tabRect�Ĵ�С���������Ƿ�Χ�ʺ������ǩҳ	
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 21;
	tabRect.bottom -= 2;
	//���ݵ����õ�tabRect������������ǩҳ�����ѵ�һ������Ϊ��ʾ���ڶ�������Ϊ����
	m_TabAboutMember.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);
	m_TabAboutFunction.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);
}


BEGIN_MESSAGE_MAP(CDlgAboutMF, CDialogEx)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_AboutMF, &CDlgAboutMF::OnSelchangeTabAboutmf)
END_MESSAGE_MAP()


// CDlgAboutMF ��Ϣ�������
void CDlgAboutMF::OnSelchangeTabAboutmf(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;

	CRect tabRect;

	m_tab_About.GetClientRect(&tabRect); //��ȡ��ǩ�ؼ�������

	//����tabRect�Ĵ�С���������Ƿ�Χ�ʺ������ǩҳ
	tabRect.left += 1;
	tabRect.right -= 3;
	tabRect.top += 21;
	tabRect.bottom -= 2;

	switch(m_tab_About.GetCurSel())
	{
		//���ݵ����õ�tabRect������������ǩҳ�����ѵ�һ������Ϊ��ʾ���ڶ�������Ϊ����
	case 0:		
		m_TabAboutMember.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);
		m_TabAboutFunction.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);
		break;

		//���ݵ����õ�tabRect������������ǩҳ�����ѵڶ�������Ϊ��ʾ��һ������Ϊ����
	case 1:		
		m_TabAboutMember.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_HIDEWINDOW);
		m_TabAboutFunction.SetWindowPos(NULL,tabRect.left,tabRect.top,tabRect.Width(),tabRect.Height(),SWP_SHOWWINDOW);

	default:
		break;
	}
}