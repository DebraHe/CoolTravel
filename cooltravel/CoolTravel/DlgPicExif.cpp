// DlgPicExif.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgPicExif.h"
#include "afxdialogex.h"


// CDlgPicExif �Ի���

IMPLEMENT_DYNAMIC(CDlgPicExif, CDialogEx)

CDlgPicExif::CDlgPicExif(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgPicExif::IDD, pParent)
{

}

CDlgPicExif::~CDlgPicExif()
{
}

void CDlgPicExif::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Pic_Display, m_ShowPicture);

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


BEGIN_MESSAGE_MAP(CDlgPicExif, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ON, &CDlgPicExif::OnBnClickedButtonOn)
	ON_BN_CLICKED(IDC_BUTTON_OUT, &CDlgPicExif::OnBnClickedButtonOut)
	ON_BN_CLICKED(IDC_BUTTON_Message, &CDlgPicExif::OnBnClickedButtonMessage)
END_MESSAGE_MAP()


// CDlgPicExif ��Ϣ�������
bool CDlgPicExif::PromptForFileName(CString& fileName, UINT nIDSTitle, DWORD dwFlags, bool bOpenFileDialog, int* pType)
{
	CFileDialog dlgFile(bOpenFileDialog);
	CString title;
	if (bOpenFileDialog) title = _T("ѡ��ͼƬ"); 
	else title = _T("Save file");

	dlgFile.m_ofn.Flags |= dwFlags;

	int nDocType = (pType != NULL) ? *pType : 0;

	int nIndex = 0;

	dlgFile.m_ofn.nFilterIndex = nIndex +1;
	CString strDefExt = _T("pal");
	dlgFile.m_ofn.lpstrDefExt = strDefExt;

	CString strFilter = _T("*.jpg");
	strFilter += (TCHAR)NULL;
	strFilter += _T("*.jpg");
	strFilter += (TCHAR)NULL;
	strFilter += _T("*.*");
	strFilter += (TCHAR)NULL;
	strFilter += _T("*.*");
	strFilter += (TCHAR)NULL;

	dlgFile.m_ofn.lpstrFilter = strFilter;
	dlgFile.m_ofn.lpstrTitle = title;
	dlgFile.m_ofn.lpstrFile = fileName.GetBuffer(_MAX_PATH);

	BOOL bRet = (dlgFile.DoModal() == IDOK) ? TRUE : FALSE;
	fileName.ReleaseBuffer();
	if (bRet){
		if (pType != NULL){
			int nIndex = (int)dlgFile.m_ofn.nFilterIndex - 1;
			ASSERT(nIndex >= 0);
		}
	}
	return bRet;
}


void CDlgPicExif::ShowInfo(void)
{
	CString t;
	s="";

	if (m_exifinfo.CameraMake[0]){
		t.Format(_T("�����������  : %s\n"),CString(m_exifinfo.CameraMake)); s+=t;
		t.Format(_T("������ͺ�     : %s\n"),CString(m_exifinfo.CameraModel)); s+=t;
	}
	if (m_exifinfo.DateTime[0]){
		t.Format(_T("����ʱ��        : %s\n"),CString(m_exifinfo.DateTime)); s+=t;
	}
	if (m_exifinfo.Version[0]){
		t.Format(_T("EXIF �汾       : %s\n"),CString(m_exifinfo.Version)); s+=t;
	}

	t.Format(_T("�ֱ���           : %d x %d\n"),m_exifinfo.Width, m_exifinfo.Height); s+=t;
	t.Format(_T("���              : %d ����\n"),m_exifinfo.Width); s+=t;
	t.Format(_T("�߶�              : %d ����\n"),m_exifinfo.Height); s+=t;

	if ((m_exifinfo.ResolutionUnit!=0)&&(m_exifinfo.Xresolution!=0)){
		t.Format(_T("ˮƽ�ֱ���     : %5.1fdpi\n"),m_exifinfo.Xresolution/m_exifinfo.ResolutionUnit); s+=t;
	}
	if ((m_exifinfo.ResolutionUnit!=0)&&(m_exifinfo.Yresolution!=0)){
		t.Format(_T("��ֱ�ֱ���     : %5.1fdpi\n"),m_exifinfo.Yresolution/m_exifinfo.ResolutionUnit); s+=t;
	}

	if (m_exifinfo.Orientation > 1){
		t.Format(_T("Orientation  : %s\n"), m_exifinfo.Orientation); s+=t;
	}
	if (m_exifinfo.IsColor == 0){
		t.Format(_T("Color/bw     : Black and white\n")); s+=t;
	}
	if (m_exifinfo.FlashUsed >= 0){
		t.Format(_T("�����ģʽ     : %s\n"),m_exifinfo.FlashUsed ? _T("������") :_T("������")); s+=t;
	}
	if (m_exifinfo.FocalLength){
		t.Format(_T("����     : %4.1fmm"),(double)m_exifinfo.FocalLength); s+=t;
		if (m_exifinfo.CCDWidth){
			t.Format(_T("  (35mm equivalent: %dmm)"),
				(int)(m_exifinfo.FocalLength/m_exifinfo.CCDWidth*36 + 0.5)); s+=t;
		}
		t.Format(_T("\n")); s+=t;
	}
	if(m_exifinfo.Latitude > 0.0)
	{
		t.Format(_T("γ��     : %4.15f \n"), (double)m_exifinfo.Latitude);
		s+=t;
	}
	if(m_exifinfo.Longitude > 0.0)
	{
		t.Format(_T("����     : %4.15f \n"), (double)m_exifinfo.Longitude);
		s+=t;
	}

	if (m_exifinfo.CCDWidth){
		t.Format(_T("CCD width     : %4.2fmm\n"),(double)m_exifinfo.CCDWidth); s+=t;
	}

	if (m_exifinfo.ExposureTime){
		t.Format(_T("�ع�ʱ��        :%6.3f s "),(double)m_exifinfo.ExposureTime); s+=t;
		if (m_exifinfo.ExposureTime <= 0.5){
			t.Format(_T(" (1/%d)"),(int)(0.5 + 1/m_exifinfo.ExposureTime)); s+=t;
		}
		t.Format(_T("\n")); s+=t;
	}
	if (m_exifinfo.Brightness){
		t.Format(_T("Brightness : %6.3f\n"),m_exifinfo.Brightness); s+=t;
	}
	if (m_exifinfo.ApertureFNumber){
		t.Format(_T("��Ȧֵ           : f/%3.1f\n"),(double)m_exifinfo.ApertureFNumber); s+=t;
	}
	if (m_exifinfo.Distance){
		if (m_exifinfo.Distance < 0){
			t.Format(_T("Focus dist.  : Infinite\n")); s+=t;
		}else{
			t.Format(_T("Focus dist.  : %4.2fm\n"),(double)m_exifinfo.Distance); s+=t;
		}
	}


	if (m_exifinfo.ISOequivalent){ // 05-jan-2001 vcs
		t.Format(_T("ISO �ٶ�.       : %2d\n"),(int)m_exifinfo.ISOequivalent); s+=t;
	}
	if (m_exifinfo.ExposureBias){ // 05-jan-2001 vcs
		t.Format(_T("Exposure bias:%4.2f\n"),(double)m_exifinfo.ExposureBias); s+=t;
	}

	if (m_exifinfo.Whitebalance){ // 05-jan-2001 vcs
		switch(m_exifinfo.Whitebalance) {
		case 1:
			t.Format(_T("Whitebalance : sunny\n")); s+=t;
			break;
		case 2:
			t.Format(_T("Whitebalance : fluorescent\n")); s+=t;
			break;
		case 3:
			t.Format(_T("Whitebalance : incandescent\n")); s+=t;
			break;
		default:
			t.Format(_T("Whitebalance : cloudy\n")); s+=t;
		}
	}
	if (m_exifinfo.MeteringMode){ // 05-jan-2001 vcs
		switch(m_exifinfo.MeteringMode) {
		case 2:
			t.Format(_T("Metering Mode: center weight\n")); s+=t;
			break;
		case 3:
			t.Format(_T("Metering Mode: spot\n")); s+=t;
			break;
		case 5:
			t.Format(_T("Metering Mode: matrix\n")); s+=t;
			break;
		}
	}
	if (m_exifinfo.ExposureProgram){ // 05-jan-2001 vcs
		switch(m_exifinfo.ExposureProgram) {
		case 2:
			t.Format(_T("Exposure     : program (auto)\n")); s+=t;
			break;
		case 3:
			t.Format(_T("Exposure     : aperture priority (semi-auto)\n")); s+=t;
			break;
		case 4:
			t.Format(_T("Exposure     : shutter priority (semi-auto)\n")); s+=t;
			break;
		}
	}
	if (m_exifinfo.CompressionLevel){ // 05-jan-2001 vcs
		switch(m_exifinfo.CompressionLevel) {
		case 1:
			t.Format(_T("Jpeg Quality : basic\n")); s+=t;
			break;
		case 2:
			t.Format(_T("Jpeg Quality : normal\n")); s+=t;
			break;
		case 4:
			t.Format(_T("Jpeg Quality : fine\n")); s+=t;
			break;
		}
	}

	t.Format(_T("Encoding       : ")); s+=t;
	switch(m_exifinfo.Process){
	case 0xC0: //M_SOF0
		t.Format(_T("Baseline\n")); s+=t;
		break;
	case 0xC1: //M_SOF1
		t.Format(_T("Extended sequential\n")); s+=t;
		break;
	case 0xC2: //M_SOF2
		t.Format(_T("Progressive\n")); s+=t;
		break;
	case 0xC3: //M_SOF3
		t.Format(_T("Lossless\n")); s+=t;
		break;
	case 0xC5: //M_SOF5
		t.Format(_T("Differential sequential\n")); s+=t;
		break;
	case 0xC6: //M_SOF6
		t.Format(_T("Differential progressive\n")); s+=t;
		break;
	case 0xC7: //M_SOF7
		t.Format(_T("Differential lossless\n")); s+=t;
		break;
	case 0xC9: //M_SOF9
		t.Format(_T("Extended sequential, arithmetic coding\n")); s+=t;
		break;
	case 0xCA: //M_SOF10
		t.Format(_T("Progressive, arithmetic coding\n")); s+=t;
		break;
	case 0xCB: //M_SOF11
		t.Format(_T("Lossless, arithmetic coding\n")); s+=t;
		break;
	case 0xCD: //M_SOF13
		t.Format(_T("Differential sequential, arithmetic coding\n")); s+=t;
		break;
	case 0xCE: //M_SOF14
		t.Format(_T("Differential progressive, arithmetic coding\n")); s+=t;
		break;
	case 0xCF: //M_SOF0
		t.Format(_T("Differential lossless, arithmetic coding\n")); s+=t;
		break;
	default:
		t.Format(_T("Unknown\n")); s+=t;
		break;
	}

	// Print the comment. Print 'Comment:' for each new line of comment.
	if (m_exifinfo.Comments[0]){
		int a,c;
		t.Format(_T("Comment      : ")); 
		s+=t;
		for (a=0;a<MAX_COMMENT;a++){
			c = m_exifinfo.Comments[a];
			if (c == '\0') break;
			if (c == '\n'){
				// Do not start a new line if the string ends with a carriage return.
				if (m_exifinfo.Comments[a+1] != '\0'){
					t.Format(_T("\nComment      : ")); 
					s+=t;
				}else{
					t.Format(_T("\n")); 
					s+=t;
				}
			}else{
				s.Format(_T("%s%d"),s,c);
				// s+=c;
			}
		}
	}

	t.Format(_T("\n")); s+=t;

	//MessageBox(s,TEXT("EXIF"),MB_OK|MB_ICONQUESTION);
}


void CDlgPicExif::OnBnClickedButtonOn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	
	CString filename;   //����Ƭ��ַ

	//��ȡ��Ƭ�ĵ�ַ
	if (!PromptForFileName(filename, AFX_IDS_OPENFILE, OFN_HIDEREADONLY | OFN_FILEMUSTEXIST, TRUE, NULL))
	{
		return; 
	}

	char aFilename[100] ;
	LPCWSTR lpcwStr=filename.AllocSysString();

	//��ȡfilename�ĳ���
	int iByteLen = WideCharToMultiByte(CP_ACP,0, lpcwStr, filename.GetLength(),NULL,0,NULL,NULL);
	//��CStringת����char*
	WideCharToMultiByte(CP_ACP,0,lpcwStr, filename.GetLength(), aFilename, iByteLen,NULL,NULL);
	aFilename[iByteLen] = '\0';



	FILE* hFile= fopen(aFilename,"rb");	

	if (hFile){

		memset(&m_exifinfo,0,sizeof(EXIFINFO));

		Cexif exif(&m_exifinfo);
		exif.DecodeExif(hFile);

		fclose(hFile);

		CDC *pDC =m_ShowPicture.GetWindowDC(); 
		CImage m_image;
		m_image.Load(filename);//�ļ�·��

		CRect rect;
		m_ShowPicture.GetClientRect(&rect);

		int Width = rect.right - rect.left;
		int Height = rect.bottom - rect.top;

		pDC->SetStretchBltMode(STRETCH_HALFTONE); //����ʧ��
		m_image.Draw(pDC->m_hDC,0,0,Width,Height);

		ReleaseDC(pDC);

		if (m_exifinfo.IsExif) 
			ShowInfo();
		else 
			MessageBox(TEXT("      ��ͼƬû���ҵ�exif��Ϣ"),TEXT("EXIF"),MB_OK);

	}

}


void CDlgPicExif::OnBnClickedButtonOut()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//DestroyWindow();	
	PostMessage(WM_CLOSE);
}



void CDlgPicExif::OnBnClickedButtonMessage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(s=="")
		MessageBox(_T("��ȡ��Ϣʧ��"),TEXT("EXIF"),MB_OK|MB_ICONQUESTION);
	else
	{
		MessageBox(s,TEXT("EXIF"),MB_OK|MB_ICONQUESTION);
	}
}