// DlgNewTrip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgNewTrip.h"
#include "afxdialogex.h"


#include <afxdao.h>         //dao������ʵ�����ݿ�Ķ�д
#include <comdef.h>         //�����ݸ�ʽת����ʱ����õ�

extern CDaoDatabase db;    //���ݿ�



// CDlgNewTrip �Ի���
static int num=0;
IMPLEMENT_DYNAMIC(CDlgNewTrip, CDialogEx)

CDlgNewTrip::CDlgNewTrip(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgNewTrip::IDD, pParent)
{
	
}

CDlgNewTrip::~CDlgNewTrip()
{
}

void CDlgNewTrip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//͸����ť
	DDX_Control(pDX, IDC_EXPLORER1, m_web);
	DDX_Control(pDX, IDC_BUTTON_savepath, m_btn1);	
	DDX_Control(pDX, IDC_BUTTON_TripName, m_btn2);
	DDX_Control(pDX, IDC_BUTTON_AddDarry, m_btn3);
	DDX_Control(pDX, IDC_BUTTON_PicIn, m_btn4);
	DDX_Control(pDX, IDC_BUTTON_SavePic, m_btn5);
	DDX_Control(pDX, IDC_BUTTON_AddRode, m_btn6);
	DDX_Control(pDX, IDC_BUTTON_SaveTrack, m_btn7);
	m_btn1.Load(IDB_PNG1, 244);
	m_btn2.Load(IDB_PNG1, 244);
	m_btn3.Load(IDB_PNG1, 244);
	m_btn4.Load(IDB_PNG1, 244);
	m_btn5.Load(IDB_PNG1, 244);
	m_btn6.Load(IDB_PNG1, 244);
	m_btn7.Load(IDB_PNG1, 244);

	CString ProjectPath= GetMoudulePath();    //���ú�����ù���Ŀ¼
	CString mapPath="\\map.htm";            // ��  ��\\����������Լ���html����  ע��html��÷��ڹ���Ŀ¼��
	mapPath=ProjectPath+mapPath;          //��ñ�����ַ
	m_web.Navigate(mapPath,NULL,NULL,NULL,NULL);	

	
}

CString CDlgNewTrip::GetMoudulePath()
{
	char pFileName[MAX_PATH];   
	int nPos = GetCurrentDirectory( MAX_PATH, pFileName);   

	CString csFullPath(pFileName);    
	if( nPos < 0 )   
		return CString("");   
	else   
		return csFullPath;   
}

BEGIN_MESSAGE_MAP(CDlgNewTrip, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_AddRode, &CDlgNewTrip::OnBnClickedButtonAddrode)
	ON_BN_CLICKED(IDC_BUTTON_savepath, &CDlgNewTrip::OnBnClickedButtonsavepath)
	ON_BN_CLICKED(IDC_BUTTON_TripName, &CDlgNewTrip::OnBnClickedButtonTripname)
	ON_BN_CLICKED(IDC_BUTTON_AddDarry, &CDlgNewTrip::OnBnClickedButtonAdddarry)
	ON_BN_CLICKED(IDC_BUTTON_SavePic, &CDlgNewTrip::OnBnClickedButtonSavepic)
	ON_BN_CLICKED(IDC_BUTTON_PicIn, &CDlgNewTrip::OnBnClickedButtonPicin)
	ON_BN_CLICKED(IDC_BUTTON_SaveTrack, &CDlgNewTrip::OnBnClickedButtonSavetrack)
	ON_WM_NCLBUTTONDOWN()
END_MESSAGE_MAP()


// CDlgNewTrip ��Ϣ�������
void CDlgNewTrip::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgNewTrip::OnBnClickedButtonAddrode()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComQIPtr<IHTMLDocument2> spDoc = m_web.get_Document();
	CComDispatchDriver spScript;
	spDoc->get_Script(&spScript);
	CComVariant  var;
	spScript.Invoke1(L"drivecar",&var);

}


void CDlgNewTrip::OnBnClickedButtonsavepath()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ZeroMemory(savepath,   sizeof(savepath));   
	BROWSEINFO       bi;   
	bi.hwndOwner   =   m_hWnd;   
	bi.pidlRoot   =   NULL;   
	bi.pszDisplayName   =   savepath;   
	bi.lpszTitle   =   "��ѡ���г̱���·����";   
	bi.ulFlags   =   BIF_EDITBOX   ;   
	bi.lpfn   =   NULL;   
	bi.lParam   =   0;   
	bi.iImage     =   0;   
	LPITEMIDLIST     lp   =   SHBrowseForFolder(&bi);   

	if(lp   &&   SHGetPathFromIDList(lp,   savepath))   
	{   
		//::SetDlgItemText(this->m_hWnd,IDC_BUTTON_Track_Save,buf);
		//AfxMessageBox(savepath);
	}
}


void CDlgNewTrip::OnBnClickedButtonTripname()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString text;
	text.Format("�ѽ����г�·�������� %s !", savepath);
	MessageBox(text, "��ܰ��ʾ");
	CString ProjectPath = GetMoudulePath();    //���ú�����ù���Ŀ¼
	CString mapPath = "\\map.htm";            // ��  ��\\����������Լ���html����  ע��html��÷��ڹ���Ŀ¼��
	mapPath = ProjectPath + mapPath;          //��ñ�����ַ
	m_web.Navigate(mapPath, NULL, NULL, NULL, NULL);

	CDlgTripName DlgTripName;
	if (DlgTripName.DoModal() == IDOK)
	{
		m_TripName = DlgTripName.m_TripNameSon;
	}

	CFile file;
	CString filenametxt, filepath;
	filepath = savepath;


	filenameDirectory = "";  //�ļ���
	filenameDirectory.Format(_T("\\%s"), m_TripName);//1..9������		
	filenameDirectory = filepath + filenameDirectory;  //�ļ�·��
	CreateDirectory(filenameDirectory, NULL);

	filenametxt = "";  //�ļ���
	filenametxt.Format(_T("\\%s\\%s.txt"), m_TripName, m_TripName);//1..9������		
	filenametxt = filepath + filenametxt;  //txt�ļ�·��
	file.Open(filenametxt, CFile::modeCreate | CFile::modeWrite);//�����ļ�


	//���ݿ����
	CDaoRecordset Dbset(&db);    //��¼�������������ܽ��ж�д�Լ�ɾ������
	CString Filepath = "TripData.mdb";
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE, "SELECT * FROM TripDataTable", 0);
	Dbset.AddNew();  //���޼�¼���Ķ�β���
	Dbset.SetFieldValue("TripName", m_TripName.GetBuffer());//��cstring��ʽת��Ϊ���ݿ�涨�ĸ�ʽ
	m_TripName.ReleaseBuffer();
	Dbset.SetFieldValue("DirectPath", filenameDirectory.GetBuffer());
	filenameDirectory.ReleaseBuffer();
	Dbset.SetFieldValue("TxtPath", filenametxt.GetBuffer());
	filenametxt.ReleaseBuffer();
	Dbset.Update();    //һ��Ҫ��ʱ����
	Dbset.Close();
	db.Close();   //���ر�	
}


void CDlgNewTrip::OnBnClickedButtonAdddarry()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	filenametxt="";  //�ļ���
	filenametxt.Format(_T("\\%s.txt"),m_TripName);//1..9������		
	filenametxt=filenameDirectory+filenametxt;  //�ļ�·��
	//ShellExecute(0,"open",filenametxt,"","",SW_SHOWNORMAL);
	ShellExecute(NULL, "open", filenametxt, NULL, NULL, SW_SHOWNORMAL);
}


CString CDlgNewTrip::GetFileTitleFromFileName(CString FileName, BOOL Ext) 
{ 

	int Where; 
	Where = FileName.ReverseFind('\\'); 
	if (Where == -1) 
		Where = FileName.ReverseFind('/'); 
	CString FileTitle = FileName.Right(FileName.GetLength() - 1 - Where); 
	if (!Ext) 
	{ 
		int Which = FileTitle.ReverseFind('.'); 
		if (Which != -1) 
			FileTitle = FileTitle.Left(Which); 
	} 
	return FileTitle; 
} 

void CDlgNewTrip::OnBnClickedButtonSavepic()
{	
	for(int i=0;i<num;i++)
	{
		CString picture = this->GetFileTitleFromFileName(PicPath[i],FALSE);

		CString FileName1,FileName2;
		FileName1.Format(_T("\\%s.jpg"),picture);
		FileName1=filenameDirectory+FileName1;
		CopyFile(PicPath[i],FileName1,false);

		CImage image;
		image.Load(PicPath[i]);
		CDC dstDC;
		dstDC.SelectObject(image);
		FileName2.Format(_T("\\%s.bmp"),picture);
		FileName2=filenameDirectory+FileName2;
		image.Save(FileName2);						
	}
	MessageBox("ͼƬ����ɹ���","��ܰ��ʾ");
	
}


void CDlgNewTrip::OnBnClickedButtonPicin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CFileDialog ff(TRUE,NULL,NULL,OFN_ENABLESIZING|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST,_T("All Files (*.*)|*.*||"),this);
	int MIN_FILE_NUMBER = 500;//���ͬʱѡ���ļ���
	ff.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //���¶��建������С
	memset(ff.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //��ʼ������Ļ�����
	ff.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;
	CString dir;	
	if(IDOK==ff.DoModal())
	{
		POSITION pos = ff.GetStartPosition();	
		
		while (NULL != pos)
		{
			dir = ff.GetNextPathName(pos);//��ȡ�ļ���			
			PicPath[num]=dir;
			num++;
			char aFilename[100] ;
			LPCWSTR lpcwStr=dir.AllocSysString();
			int iByteLen = WideCharToMultiByte(CP_ACP,0, lpcwStr, dir.GetLength(),NULL,0,NULL,NULL);
			//��CStringת����char*
			WideCharToMultiByte(CP_ACP,0,lpcwStr, dir.GetLength(), aFilename, iByteLen,NULL,NULL);
			aFilename[iByteLen] = '\0';
			FILE* hFile= fopen(aFilename,"rb");	
			if (hFile)
			{
				memset(&m_exifinfo,0,sizeof(EXIFINFO));
				Cexif exif(&m_exifinfo);
				exif.DecodeExif(hFile);
				fclose(hFile);
				if (m_exifinfo.IsExif)
				{
					CComQIPtr<IHTMLDocument2> spDoc = m_web.get_Document();
					CComDispatchDriver spScript;
					spDoc->get_Script(&spScript);
					CComVariant varmap;

					CComVariant varpic=dir;
					spScript.Invoke1(L"Picture",&varpic,&varmap); //varpic ��ͼƬ�ĵ�ַ 

					CFile fFile(filenametxt,CFile::modeRead);   
					CStringA strFile ;  
					fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()),fFile.GetLength());  
					fFile.Close(); 
					strFile.ReleaseBuffer();
					CComVariant vartxt=strFile;
					spScript.Invoke1(L"Message",&vartxt,&varmap); //vatxt3 ��txt�ĵ�ַ 

					CComVariant varJD,varWD;
					varJD=m_exifinfo.Longitude;
					varWD=m_exifinfo.Latitude;
					spScript.Invoke2(L"MakePoint", &varJD, &varWD, &varmap);


					spScript.Invoke1(L"goodview", &varmap);

					//���ݿ����
					/*readTripPic();

					CString Filepath="TripPic.mdb";
					DB.Open(Filepath);
					DBset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripPicTable",0);
					DBset.AddNew();  //���޼�¼���Ķ�β���
					DBset.SetFieldValue("PicPath",_variant_t(dir));//��cstring��ʽת��Ϊ���ݿ�涨�ĸ�ʽ
					DBset.SetFieldValue("JD",_variant_t(m_exifinfo.Longitude));
					DBset.SetFieldValue("WD",_variant_t(m_exifinfo.Latitude));
					DBset.Update();    //һ��Ҫ��ʱ����
					DBset.Close();
					DB.Close();   //���ر�
					*/
				}
			}	
		}	
		PicPath[num]='\0';


	}
	MessageBox("���ͼ���ϵĺ�ɫ����о�ϲ��","��ܰ��ʾ");	
}


void CDlgNewTrip::OnBnClickedButtonSavetrack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox("      �г̱���ɹ���","��ܰ��ʾ");
}



void CDlgNewTrip::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (HTCAPTION == nHitTest) 
	{
		return;
	}
	CDialogEx::OnNcLButtonDown(nHitTest, point);	
}



/*void CDlgNewTrip::readTripPic()
{
	CString Filepath="TripPic.mdb";  //�����ݿ��ļ�Data.mdb�ڳ����ͬһĿ¼��
	CFileFind Ffind;             //�ȿ����治�������ݿ��ļ�
	BOOL flag=Ffind.FindFile(Filepath);
	Ffind.Close();

	if(!flag)  //���û�У����Ǿʹ���
	{
		DB.Create(Filepath);
		CString sqlcmd="CREATE TABLE TripPicTable(PicPath VARCHAR(200),JD VARCHAR(200),WD VARCHAR(200))";  //�����ڲ����������������ԣ����������䣩
		DB.Execute(sqlcmd);    //ִ��sqlָ��
		DB.Close();//�������һ��Ҫ�رգ��������
		//MessageBox("ͼƬ���ݿ��ѽ����ɹ���","������ʾ");
	}

	_variant_t varPicPath,varJD,varWD;	
	CString SPicPath,SJD,SWD;
	int i=0;
	DB.Open(Filepath);
	DBset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripPicTable",0);
	while(!DBset.IsEOF())
	{
		varPicPath=DBset.GetFieldValue("PicPath");		
		SPicPath=(LPCSTR)_bstr_t(varPicPath); //�ֱ����ݿ�������������ļ�ת����cstring

		varJD=DBset.GetFieldValue("JD");		
		SJD=(LPCSTR)_bstr_t(varJD); //�ֱ����ݿ�������������ļ�ת����cstring

		varWD=DBset.GetFieldValue("WD");		
		SWD=(LPCSTR)_bstr_t(varWD); //�ֱ����ݿ�������������ļ�ת����cstring
		i++;
	}
	DBset.Close();
	DB.Close();
}
*/