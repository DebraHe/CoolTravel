// DlgTripPic.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgTripPic.h"
#include "afxdialogex.h"


// CDlgTripPic �Ի���

IMPLEMENT_DYNAMIC(CDlgTripPic, CDialogEx)

CDlgTripPic::CDlgTripPic(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgTripPic::IDD, pParent)
{

}

CDlgTripPic::~CDlgTripPic()
{
}

void CDlgTripPic::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Pic, m_listPic);
	DDX_Control(pDX, IDC_Pic_Display, m_Pic);

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


	//���ͼƬ
	//CFileDialog ff(TRUE, "", NULL, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY, _T("image files (*.jpeg; *.jpg; *.bmp) |*.bmp; *.jpg; *.jpeg | All Files (*.*) |*.*||"), NULL);
	//CFileDialog ff(TRUE, _T(""), _T("*.*"), OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, _T("image files (*.bmp)|*.bmp;*.jpg|All Files (*.*)|*.*||"), NULL);
	TCHAR szFilters[] = _T("image files (*.bmp)|*.bmp|All Files (*.*)|*.*||");
	CFileDialog ff(true, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT | OFN_ALLOWMULTISELECT, szFilters);
	int MIN_FILE_NUMBER = 20;//���ͬʱѡ���ļ���
	ff.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //���¶��建������С
	memset(ff.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //��ʼ������Ļ�����
	ff.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;
	CString dir;	
	int nFlags=20;	
	if(IDOK==ff.DoModal())
	{				
		for(static int m=0;m<nFlags;)
		{
			POSITION pos = ff.GetStartPosition();		
			while (NULL != pos)
			{
				dir = ff.GetNextPathName(pos);//��ȡ�ļ���
				path[m]=dir;//�����Լ����ļ������浽��Ҫ�ĵط�	
				m++;				
			}
			nFlags=m;
		}
	}
	//�ͷŶԻ����е���Դ
	m_listPic.DeleteAllItems();
	CImageList a; 
	a.Create(100,100, ILC_COLOR32 | ILC_COLORDDB | ILC_MASK , 8, 1); 
	for(int m=0;m<nFlags;m++)
	{
		HBITMAP hBmp  = (HBITMAP)::LoadImage(
			::AfxGetInstanceHandle(), 
			path[m],
			IMAGE_BITMAP,
			100,
			100,
			LR_LOADFROMFILE
			);
		CBitmap* pBmp = CBitmap::FromHandle(hBmp); 		 
		a.Add(pBmp,RGB(0 ,0, 0));			
		m_listPic.SetImageList(&a,LVSIL_NORMAL);  
		CString strTemp;	
		strTemp.Format(_T("Picture��%d"),m+1);
		m_listPic.InsertItem(m,strTemp,m);			
	}
	a.Detach();	
}


BEGIN_MESSAGE_MAP(CDlgTripPic, CDialogEx)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_Pic, &CDlgTripPic::OnLvnItemchangedListPic)
END_MESSAGE_MAP()


// CDlgTripPic ��Ϣ�������


void CDlgTripPic::OnLvnItemchangedListPic(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	NM_LISTVIEW *pNMListView=(NM_LISTVIEW*)pNMHDR;
	//�õ�ѡ�е��� 
	int column=pNMListView->iSubItem;
	int row=pNMListView->iItem;

	for(int i=0;i<20;i++)
	{
		if(row==i)
			LoadPic(i);
	}

	*pResult = 0;
}

void CDlgTripPic::LoadPic(int n)
{
	CDC *pDC =m_Pic.GetWindowDC(); 
	CImage m_image;
	m_image.Load(path[n]);//�ļ�·��

	CRect rect;
	m_Pic.GetClientRect(&rect);

	int Width = rect.right - rect.left;
	int Height = rect.bottom - rect.top;

	pDC->SetStretchBltMode(STRETCH_HALFTONE); //����ʧ��
	m_image.Draw(pDC->m_hDC,0,0,Width,Height);

	ReleaseDC(pDC);
}