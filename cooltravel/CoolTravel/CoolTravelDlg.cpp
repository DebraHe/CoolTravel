
// CoolTravelDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "CoolTravelDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCoolTravelDlg �Ի���




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


// CCoolTravelDlg ��Ϣ�������

BOOL CCoolTravelDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//����ͼƬ
	this->MoveWindow(0,0,1000,640,true);
	LoadDlgBk(IDB_BITMAP3);

	//͸������
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
		if(func)func(this->GetSafeHwnd(), RGB(0, 0, 0), 240, 0x2); 
		FreeLibrary(hInst); 
	}

	//�����Ӵ���
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
	//�����Ӵ������

	//͸����ť
	m_btn1.Load(IDB_PNG1, 244);
	m_btn2.Load(IDB_PNG1, 244);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCoolTravelDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//��ȡ�ͻ�����Ĵ�С
		CRect rect;
		GetClientRect(rect);

		CPaintDC dc(this);
		dc.BitBlt(0,0,rect.right,rect.bottom,&m_dcMain, 0, 0, SRCCOPY);
		CDialogEx::OnPaint();
	}
}

HBRUSH CCoolTravelDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	//�����ı���ı���
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor); 
	if(   CTLCOLOR_STATIC   ==   nCtlColor   )  
	{ 
		//pDC->SetBkColor(RGB(255,0,0));  //��Ҫָ������ɫ��ʱ���� 
		pDC->SetTextColor(RGB(255,   255,   255));    //����ǰ��ɫ
		pDC->SetBkMode(TRANSPARENT);    //����͸��
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);  //��ȡ������ɫ��Ϻ�Ļ��ʣ����͸�� 
	}  
	return hbr;
} 

void CCoolTravelDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCoolTravelDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
//������ͼ����
void CCoolTravelDlg::LoadDlgBk(int iBmpID)
{
	//�ͷ���Դ
	m_dcMain.DeleteDC();
	m_dcBk.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBk.DeleteObject();

	//��ȡ�ͻ������С
	CRect   rect;
	GetClientRect(rect);

	//���Ʊ���
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

	// TODO: �ڴ˴������Ϣ����������

	//�ͷ���Դ
	m_dcMain.DeleteDC();
	m_dcBk.DeleteDC();
	m_bmpMain.DeleteObject();
	m_bmpBk.DeleteObject();
}


void CCoolTravelDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CCoolTravelDlg::OnOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnOK();
}


void CCoolTravelDlg::OnCancel()
{
	// TODO: �ڴ����ר�ô����/����û���

	CDialogEx::OnCancel();
}


void CCoolTravelDlg::OnMenuStyle3()
{
	// TODO: �ڴ���������������
	LoadDlgBk(IDB_BITMAP3);
}


void CCoolTravelDlg::OnMenuStyle1()
{
	// TODO: �ڴ���������������
	LoadDlgBk(IDB_BITMAP1);
}


void CCoolTravelDlg::OnMenuStyle2()
{
	// TODO: �ڴ���������������
	LoadDlgBk(IDB_BITMAP2);
}


void CCoolTravelDlg::OnMenuStyle4()
{
	// TODO: �ڴ���������������
	LoadDlgBk(IDB_BITMAP4);
}


void CCoolTravelDlg::OnMenuStyle5()
{
	// TODO: �ڴ���������������
	LoadDlgBk(IDB_BITMAP5);
}
//������ͼ��������

//�鿴�����г�
void CCoolTravelDlg::OnBnClickedLookoldtrip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_DlgOldTrip->dataupdate();
	m_DlgOldTrip->ShowWindow(SW_SHOW);
	m_DlgNewTrip->ShowWindow(SW_HIDE);
	
}

//�½�һ���г�
void CCoolTravelDlg::OnBnClickedSetnewtrip()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_DlgNewTrip->ShowWindow(SW_SHOW);
	m_DlgOldTrip->ShowWindow(SW_HIDE);
}


void CCoolTravelDlg::OnPicExif()
{
	// TODO: �ڴ���������������
	if (NULL == m_pDlgPicExif)   
	{   
		// ������ģ̬�Ի���ʵ��   
		m_pDlgPicExif = new CDlgPicExif();   
		m_pDlgPicExif->Create(IDD_Pic_Exif, this);   
	}   
	// ��ʾ��ģ̬�Ի���   
	m_pDlgPicExif->ShowWindow(SW_SHOW);   

	// �����ؼ��е����ݱ��浽��Ӧ�ı���   
	UpdateData(TRUE);   
}


void CCoolTravelDlg::OnHelp()
{
	// TODO: �ڴ���������������
	CDlgHelp m_dlgHelp;
	m_dlgHelp.DoModal();
}


void CCoolTravelDlg::OnAbout()
{
	// TODO: �ڴ���������������
	CDlgAboutMF m_dlgAbout;
	m_dlgAbout.DoModal();
}
