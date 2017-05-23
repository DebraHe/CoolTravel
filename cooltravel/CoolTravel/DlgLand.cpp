// DlgLand.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgLand.h"
#include "afxdialogex.h"


// CDlgLand �Ի���

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
	HINSTANCE hInst = LoadLibrary("User32.DLL");  //���ؿ��ļ�
	if (hInst)
	{
		typedef BOOL(WINAPI *MYFUNC)(HWND, COLORREF, BYTE, DWORD);
		MYFUNC func = NULL;	 //����ָ��
		//ȡ��SetLayeredWindowAttributes����ָ�� 
		func = (MYFUNC)GetProcAddress(hInst, "SetLayeredWindowAttributes");
		//ʹ��SetLayeredWindowAttributes�����趨͸����
		if (func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 230, 0x2);
		FreeLibrary(hInst);
	}
}


BEGIN_MESSAGE_MAP(CDlgLand, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgLand::OnBnClickedButton1)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON2, &CDlgLand::OnClickedButton2)
END_MESSAGE_MAP()


// CDlgLand ��Ϣ�������


void CDlgLand::OnBnClickedButton1()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CString c, b;
	m_name.GetWindowText(c);
	m_password.GetWindowText(b);

	if (c.IsEmpty() || b.IsEmpty())
	{
		MessageBox(_T("�û��������벻��Ϊ�գ�"), _T("�û���¼��Ϣ"));
		return;
	}
	else if (c == "YY"&&b == "1234")
	{
		//MessageBox(_T("���Գɹ���"), _T("��½"));//�����п���

	}
	else
	{
		MessageBox(_T("�û��������벻��ȷ"), _T("��ʾ"));
		return;
	}
	CDialogEx::OnOK();
}


HBRUSH CDlgLand::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);

	if (nCtlColor == CTLCOLOR_STATIC)

	{
		pDC->SetTextColor(RGB(0, 0, 0)); //������ɫ
		pDC->SetBkMode(TRANSPARENT);// ����͸��

	}

	return hbr;
}


void CDlgLand::OnClickedButton2()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
