// DlgTripName.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgTripName.h"
#include "afxdialogex.h"


// CDlgTripName �Ի���

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

	//����͸����
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
		if(func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 230, 0x2); 
		FreeLibrary(hInst); 
	}	
}


BEGIN_MESSAGE_MAP(CDlgTripName, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgTripName::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgTripName::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgTripName ��Ϣ�������


void CDlgTripName::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);//TRUE �ѱ༭�����������-���󶨵ı�������
	CDialogEx::OnOK();
}


void CDlgTripName::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
