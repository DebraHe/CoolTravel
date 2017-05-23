// DlgNewTrip.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgNewTrip.h"
#include "afxdialogex.h"


#include <afxdao.h>         //dao操作来实现数据库的读写
#include <comdef.h>         //在数据格式转换的时候会用到

extern CDaoDatabase db;    //数据库



// CDlgNewTrip 对话框
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
	//透明按钮
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

	CString ProjectPath= GetMoudulePath();    //调用函数获得工程目录
	CString mapPath="\\map.htm";            // 在  “\\”后面加上自己的html名称  注：html最好放在工程目录下
	mapPath=ProjectPath+mapPath;          //获得本地网址
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


// CDlgNewTrip 消息处理程序
void CDlgNewTrip::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y)); 
	CDialog::OnLButtonDown(nFlags, point);
}

void CDlgNewTrip::OnBnClickedButtonAddrode()
{
	// TODO: 在此添加控件通知处理程序代码
	CComQIPtr<IHTMLDocument2> spDoc = m_web.get_Document();
	CComDispatchDriver spScript;
	spDoc->get_Script(&spScript);
	CComVariant  var;
	spScript.Invoke1(L"drivecar",&var);

}


void CDlgNewTrip::OnBnClickedButtonsavepath()
{
	// TODO: 在此添加控件通知处理程序代码
	ZeroMemory(savepath,   sizeof(savepath));   
	BROWSEINFO       bi;   
	bi.hwndOwner   =   m_hWnd;   
	bi.pidlRoot   =   NULL;   
	bi.pszDisplayName   =   savepath;   
	bi.lpszTitle   =   "请选择行程保存路径：";   
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
	// TODO: 在此添加控件通知处理程序代码
	CString text;
	text.Format("已将此行程路径保存在 %s !", savepath);
	MessageBox(text, "温馨提示");
	CString ProjectPath = GetMoudulePath();    //调用函数获得工程目录
	CString mapPath = "\\map.htm";            // 在  “\\”后面加上自己的html名称  注：html最好放在工程目录下
	mapPath = ProjectPath + mapPath;          //获得本地网址
	m_web.Navigate(mapPath, NULL, NULL, NULL, NULL);

	CDlgTripName DlgTripName;
	if (DlgTripName.DoModal() == IDOK)
	{
		m_TripName = DlgTripName.m_TripNameSon;
	}

	CFile file;
	CString filenametxt, filepath;
	filepath = savepath;


	filenameDirectory = "";  //文件名
	filenameDirectory.Format(_T("\\%s"), m_TripName);//1..9个命名		
	filenameDirectory = filepath + filenameDirectory;  //文件路径
	CreateDirectory(filenameDirectory, NULL);

	filenametxt = "";  //文件名
	filenametxt.Format(_T("\\%s\\%s.txt"), m_TripName, m_TripName);//1..9个命名		
	filenametxt = filepath + filenametxt;  //txt文件路径
	file.Open(filenametxt, CFile::modeCreate | CFile::modeWrite);//建立文件


	//数据库加入
	CDaoRecordset Dbset(&db);    //记录集，有了他才能进行读写以及删除操作
	CString Filepath = "TripData.mdb";
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE, "SELECT * FROM TripDataTable", 0);
	Dbset.AddNew();  //在无记录集的队尾添加
	Dbset.SetFieldValue("TripName", m_TripName.GetBuffer());//将cstring格式转换为数据库规定的格式
	m_TripName.ReleaseBuffer();
	Dbset.SetFieldValue("DirectPath", filenameDirectory.GetBuffer());
	filenameDirectory.ReleaseBuffer();
	Dbset.SetFieldValue("TxtPath", filenametxt.GetBuffer());
	filenametxt.ReleaseBuffer();
	Dbset.Update();    //一定要及时更新
	Dbset.Close();
	db.Close();   //并关闭	
}


void CDlgNewTrip::OnBnClickedButtonAdddarry()
{
	// TODO: 在此添加控件通知处理程序代码
	filenametxt="";  //文件名
	filenametxt.Format(_T("\\%s.txt"),m_TripName);//1..9个命名		
	filenametxt=filenameDirectory+filenametxt;  //文件路径
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
	MessageBox("图片保存成功！","温馨提示");
	
}


void CDlgNewTrip::OnBnClickedButtonPicin()
{
	// TODO: 在此添加控件通知处理程序代码
	CFileDialog ff(TRUE,NULL,NULL,OFN_ENABLESIZING|OFN_ALLOWMULTISELECT|OFN_FILEMUSTEXIST|OFN_PATHMUSTEXIST,_T("All Files (*.*)|*.*||"),this);
	int MIN_FILE_NUMBER = 500;//最多同时选中文件数
	ff.m_ofn.lpstrFile = new TCHAR[_MAX_PATH * MIN_FILE_NUMBER]; //重新定义缓冲区大小
	memset(ff.m_ofn.lpstrFile, 0, _MAX_PATH * MIN_FILE_NUMBER);  //初始化定义的缓冲区
	ff.m_ofn.nMaxFile = _MAX_PATH * MIN_FILE_NUMBER;
	CString dir;	
	if(IDOK==ff.DoModal())
	{
		POSITION pos = ff.GetStartPosition();	
		
		while (NULL != pos)
		{
			dir = ff.GetNextPathName(pos);//获取文件名			
			PicPath[num]=dir;
			num++;
			char aFilename[100] ;
			LPCWSTR lpcwStr=dir.AllocSysString();
			int iByteLen = WideCharToMultiByte(CP_ACP,0, lpcwStr, dir.GetLength(),NULL,0,NULL,NULL);
			//将CString转换成char*
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
					spScript.Invoke1(L"Picture",&varpic,&varmap); //varpic 是图片的地址 

					CFile fFile(filenametxt,CFile::modeRead);   
					CStringA strFile ;  
					fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()),fFile.GetLength());  
					fFile.Close(); 
					strFile.ReleaseBuffer();
					CComVariant vartxt=strFile;
					spScript.Invoke1(L"Message",&vartxt,&varmap); //vatxt3 是txt的地址 

					CComVariant varJD,varWD;
					varJD=m_exifinfo.Longitude;
					varWD=m_exifinfo.Latitude;
					spScript.Invoke2(L"MakePoint", &varJD, &varWD, &varmap);


					spScript.Invoke1(L"goodview", &varmap);

					//数据库加入
					/*readTripPic();

					CString Filepath="TripPic.mdb";
					DB.Open(Filepath);
					DBset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripPicTable",0);
					DBset.AddNew();  //在无记录集的队尾添加
					DBset.SetFieldValue("PicPath",_variant_t(dir));//将cstring格式转换为数据库规定的格式
					DBset.SetFieldValue("JD",_variant_t(m_exifinfo.Longitude));
					DBset.SetFieldValue("WD",_variant_t(m_exifinfo.Latitude));
					DBset.Update();    //一定要及时更新
					DBset.Close();
					DB.Close();   //并关闭
					*/
				}
			}	
		}	
		PicPath[num]='\0';


	}
	MessageBox("点击图标上的红色标记有惊喜！","温馨提示");	
}


void CDlgNewTrip::OnBnClickedButtonSavetrack()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("      行程保存成功！","温馨提示");
}



void CDlgNewTrip::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (HTCAPTION == nHitTest) 
	{
		return;
	}
	CDialogEx::OnNcLButtonDown(nHitTest, point);	
}



/*void CDlgNewTrip::readTripPic()
{
	CString Filepath="TripPic.mdb";  //将数据库文件Data.mdb在程序的同一目录下
	CFileFind Ffind;             //先看看存不存在数据库文件
	BOOL flag=Ffind.FindFile(Filepath);
	Ffind.Close();

	if(!flag)  //如果没有，我们就创建
	{
		DB.Create(Filepath);
		CString sqlcmd="CREATE TABLE TripPicTable(PicPath VARCHAR(200),JD VARCHAR(200),WD VARCHAR(200))";  //创建内部表，并设置两个属性（姓名，年龄）
		DB.Execute(sqlcmd);    //执行sql指令
		DB.Close();//创建完成一定要关闭，否则出错
		//MessageBox("图片数据库已建立成功！","温情提示");
	}

	_variant_t varPicPath,varJD,varWD;	
	CString SPicPath,SJD,SWD;
	int i=0;
	DB.Open(Filepath);
	DBset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripPicTable",0);
	while(!DBset.IsEOF())
	{
		varPicPath=DBset.GetFieldValue("PicPath");		
		SPicPath=(LPCSTR)_bstr_t(varPicPath); //分别将数据库里面读出来的文件转换成cstring

		varJD=DBset.GetFieldValue("JD");		
		SJD=(LPCSTR)_bstr_t(varJD); //分别将数据库里面读出来的文件转换成cstring

		varWD=DBset.GetFieldValue("WD");		
		SWD=(LPCSTR)_bstr_t(varWD); //分别将数据库里面读出来的文件转换成cstring
		i++;
	}
	DBset.Close();
	DB.Close();
}
*/