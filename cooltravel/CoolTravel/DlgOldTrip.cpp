// DlgOldTrip.cpp : 实现文件
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgOldTrip.h"
#include "afxdialogex.h"

#include <afxdao.h>         //dao操作来实现数据库的读写
#include <comdef.h>         //在数据格式转换的时候会用到

// CDlgOldTrip 对话框
extern CDaoDatabase db;    //数据库

//CDaoRecordset Dbset(&db);    //记录集，有了他才能进行读写以及删除操作


IMPLEMENT_DYNAMIC(CDlgOldTrip, CDialogEx)

CDlgOldTrip::CDlgOldTrip(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgOldTrip::IDD, pParent)
{

	m_trip = _T("");
}

CDlgOldTrip::~CDlgOldTrip()
{
}

void CDlgOldTrip::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EXPLORER1, m_oldmap);

	CString ProjectPath= GetMoudulePath();    //调用函数获得工程目录
	CString mapPath="\\mapold.htm";            // 在  “\\”后面加上自己的html名称  注：html最好放在工程目录下
	mapPath=ProjectPath+mapPath;          //获得本地网址
	m_oldmap.Navigate(mapPath,NULL,NULL,NULL,NULL);	


	DDX_Text(pDX, IDC_EDIT_Trip, m_trip);
	DDV_MaxChars(pDX, m_trip, 500);
	DDX_Control(pDX, IDC_LIST_TripName, m_list);

	CRect rect;
	m_list.GetClientRect(&rect);
	double nColInterval = rect.Width();
	m_list.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);  //设置扩展样式
	m_list.InsertColumn(0,"我的已有行程",LVCFMT_LEFT,nColInterval);    //添加行程名项

	m_list.DeleteAllItems();
	//读取数据库数据
	CDaoRecordset Dbset(&db);    //记录集，文件读写和删除操作

	CString Filepath = "TripData.mdb";
	CString STripName, SDirectPath, STxtPath;
	int i = 0;
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE, "SELECT * FROM TripDataTable", 0);
	while (!Dbset.IsEOF())
	{
		COleVariant var1;                // 字段类型
		var1.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("TripName", var1);
		STripName = (LPCSTR)var1.pbstrVal;

		COleVariant var2;                // 字段类型
		var2.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("DirectPath", var2);
		SDirectPath = (LPCSTR)var2.pbstrVal;

		COleVariant var3;                // 字段类型
		var3.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("TxtPath", var3);
		STxtPath = (LPCSTR)var3.pbstrVal;

		m_list.InsertItem(i, "");
		m_list.SetItemText(i, 0, STripName);
		i++;
		Dbset.MoveNext();
	}
	Dbset.Close();
	db.Close();

	m_list.UpdateWindow();
	
}

CString CDlgOldTrip::GetMoudulePath()
{
	char pFileName[MAX_PATH];   
	int nPos = GetCurrentDirectory( MAX_PATH, pFileName);   

	CString csFullPath(pFileName);    
	if( nPos < 0 )   
		return CString("");   
	else   
		return csFullPath;   
}



BEGIN_MESSAGE_MAP(CDlgOldTrip, CDialogEx)
	ON_WM_NCLBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_LoadPoint, &CDlgOldTrip::OnBnClickedButtonLoadpoint)
	ON_BN_CLICKED(IDC_BUTTON_DeleteTrip, &CDlgOldTrip::OnBnClickedButtonDeletetrip)
	ON_BN_CLICKED(IDC_BUTTON_LookPic, &CDlgOldTrip::OnBnClickedButtonLookpic)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_TripName, &CDlgOldTrip::OnLvnItemchangedListTripname)
	ON_BN_CLICKED(IDC_BUTTON_LookTrack, &CDlgOldTrip::OnBnClickedButtonLooktrack)
END_MESSAGE_MAP()


// CDlgOldTrip 消息处理程序




void CDlgOldTrip::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (HTCAPTION == nHitTest) 
	{
		return;
	}
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


void CDlgOldTrip::OnBnClickedButtonLoadpoint()
{
	// TODO: 在此添加控件通知处理程序代码
	//调用数据库
	/*CString ProjectPath = GetMoudulePath();    //调用函数获得工程目录
	CString mapPath = "\\mapold.htm";            // 在  “\\”后面加上自己的html名称  注：html最好放在工程目录下
	mapPath = ProjectPath + mapPath;          //获得本地网址
	m_oldmap.Navigate(mapPath, NULL, NULL, NULL, NULL);
	*/


	CString DirectPath, TxtPath;
	const int pos =m_list.GetSelectionMark();   //选中行的索引号
	if(!(pos+1))   //如果没有选中从第一行到最后一行，则提示选中先
	{
		MessageBox("请先选择想要查看的行程！","温情提示");
	}
	else
	{
		CString Filepath="TripData.mdb";
		db.Open(Filepath);
		CDaoRecordset Dbset(&db);    //记录集，文件读写和删除操作
		Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT *FROM TripDataTable",0);		
		int i=0;		
		while(!Dbset.IsEOF())
		{
			if(i==pos)
			{
				COleVariant var2;                // 字段类型
				var2.ChangeType(VT_BSTR,NULL);
				Dbset.GetFieldValue("DirectPath",var2);
				DirectPath= (LPCSTR)var2.pbstrVal;

				COleVariant var3;                // 字段类型
				var3.ChangeType(VT_BSTR, NULL);
				Dbset.GetFieldValue("TxtPath", var3);
				TxtPath = (LPCSTR)var3.pbstrVal;
				break;			
			}
			else
			{
				i++;
				Dbset.MoveNext();		
			}
		}
		Dbset.Close();
		db.Close();
	}	
	GetInfo(DirectPath);
	PicPath[i] = '\0';
	JD[i] = '\0';
	WD[i] = '\0';
	
	for (int m = 0; m < i; m++)
	{
		CComQIPtr<IHTMLDocument2> spDoc = m_oldmap.get_Document();
		CComDispatchDriver spScript;
		spDoc->get_Script(&spScript);
		CComVariant varmap;

		CComVariant varpic = PicPath[m];
		spScript.Invoke1(L"Picture", &varpic, &varmap); //varpic 是图片的地址 

		CFile fFile(TxtPath, CFile::modeRead);
		CStringA strFile;
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());
		fFile.Close();
		strFile.ReleaseBuffer();
		CComVariant vartxt = strFile;
		spScript.Invoke1(L"Message", &vartxt, &varmap); //vatxt3 是txt的地址 

		CComVariant varJD, varWD;
		varJD = JD[m];
		varWD = WD[m];
		spScript.Invoke2(L"MakePoint", &varJD, &varWD, &varmap);
		spScript.Invoke1(L"goodview", &varmap);
	}
	

	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_Trip);
	pedit->LineScroll(pedit->GetLineCount());
	CFile file;                                         // 文件对象
	DWORD len;                                    // 用于保存文件长度
	// 读取数据
	file.Open(TxtPath, CFile::modeReadWrite);
	len = file.GetLength();
	char *pReadData = new char[len + 1]; // 分配内存
	file.Read(pReadData, len);                                       //  这里保存的读取文件的数据
	pReadData[len] = 0;
	file.Close();

	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT_Trip);
	::SetWindowTextA(pBoxOne->m_hWnd, pReadData);



	
	memset(PicPath, 0, i);
	memset(JD, 0, i);
	memset(WD, 0, i);
	DirectPath = "";
	TxtPath = "";
	i = 0;
	/*char aFilename[100];
	LPCWSTR lpcwStr = dir.AllocSysString();
	int iByteLen = WideCharToMultiByte(CP_ACP, 0, lpcwStr, dir.GetLength(), NULL, 0, NULL, NULL);
	//将CString转换成char*
	WideCharToMultiByte(CP_ACP, 0, lpcwStr, dir.GetLength(), aFilename, iByteLen, NULL, NULL);
	aFilename[iByteLen] = '\0';
	FILE* hFile = fopen(aFilename, "rb");
	if (hFile)
	{
		memset(&m_exifinfo, 0, sizeof(EXIFINFO));
		Cexif exif(&m_exifinfo);
		exif.DecodeExif(hFile);
		fclose(hFile);
		if (m_exifinfo.IsExif)
		{
			CComQIPtr<IHTMLDocument2> spDoc = m_web.get_Document();
			CComDispatchDriver spScript;
			spDoc->get_Script(&spScript);
			CComVariant varmap;

			CComVariant varpic = dir;
			spScript.Invoke1(L"Picture", &varpic, &varmap); //varpic 是图片的地址 

			CFile fFile(filenametxt, CFile::modeRead);
			CStringA strFile;
			fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());
			fFile.Close();
			strFile.ReleaseBuffer();
			CComVariant vartxt = strFile;
			spScript.Invoke1(L"Message", &vartxt, &varmap); //vatxt3 是txt的地址 

			CComVariant varJD, varWD;
			varJD = m_exifinfo.Longitude;
			varWD = m_exifinfo.Latitude;
			spScript.Invoke2(L"MakePoint", &varJD, &varWD, &varmap);


			//spScript.Invoke1(L"goodview", &varmap);
		}
	}
	MessageBox("点击图标上的红色标记有惊喜！", "温馨提示");	
	*/
}

void CDlgOldTrip::GetInfo(CString str)
{
	
	i++;
	//遍历
	CFileFind f;
	bool t = f.FindFile(str + "\\*.jpg");
	while (t)
	{ 
		
		t = f.FindNextFile();
		if (!f.IsDots())
		{
			//描点的一些准备
			CString aFilename = "";
			aFilename = f.GetFilePath();
			PicPath[i]=aFilename;
			FILE* hFile= fopen(aFilename,"rb");
			if (hFile)
			{
				memset(&m_exifinfo,0,sizeof(EXIFINFO));
				Cexif exif(&m_exifinfo);
				exif.DecodeExif(hFile);
				fclose(hFile);
				//获取经纬度
				if (m_exifinfo.IsExif) 
				{
					if(m_exifinfo.Latitude > 0.0)
					{
						WD[i]=(double)m_exifinfo.Latitude;
					}
					if(m_exifinfo.Longitude > 0.0)
					{
						JD[i]=(double)m_exifinfo.Longitude;
					}
				}
			}
			GetInfo(f.GetFilePath());
		}
	}
}


void CDlgOldTrip::OnBnClickedButtonDeletetrip()
{
	// TODO: 在此添加控件通知处理程序代码
	const int pos =m_list.GetSelectionMark();   //选中行的索引号
	if(!(pos+1))   //如果没有选中从第一行到最后一行，则提示选中先
	{
		MessageBox("请先选择需要删除的行程！","温情提示");
	}
	else
	{
		CString Filepath="TripData.mdb";
		db.Open(Filepath);
		CDaoRecordset Dbset(&db);    //记录集，文件读写和删除操作
		Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT *FROM TripDataTable",0);
		Dbset.Move(pos);   //将记录集的指针移动到当前数据的索引
		Dbset.Delete();    //删除数据
		Dbset.Close();
		db.Close();
		m_list.DeleteAllItems();
		OnInitDialog();   //最后两句的作用是刷新列表

	
		/*CString SDirectPath;
		int i=0;
		db.Open(Filepath);
		Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripDataTable",0);
		while(!Dbset.IsEOF())
		{
			if(i==pos)
			{
				COleVariant var2;                // 字段类型
				var2.ChangeType(VT_BSTR,NULL);
				Dbset.GetFieldValue("DirectPath",var2);
				SDirectPath= (LPCSTR)var2.pbstrVal;	
				break;
			}
			else
			{
				i++;
				Dbset.MoveNext();
			}

		}
		Dbset.Close();
		db.Close();
		DeleteDirectory(SDirectPath);
		*/
	}	
	
}


//删除指定目录文件夹
bool CDlgOldTrip::DeleteDirectory(CString DirName)
{

	//AfxMessageBox("执行删除文件夹:"+DirName);
	CString PUBPATH;
	PUBPATH=DirName;
	CFileFind tempFind;
	DirName+="\\*.*";
	BOOL IsFinded=(BOOL)tempFind.FindFile(DirName);
	while(IsFinded)
	{
		IsFinded=(BOOL)tempFind.FindNextFile();
		if(!tempFind.IsDots())
		{
			CString strDirName;
			strDirName+=PUBPATH;
			strDirName+="\\";
			strDirName+=tempFind.GetFileName();
			//AfxMessageBox("strDirName :"+strDirName);
			if(tempFind.IsDirectory())
			{
				//strDirName += PUBPATH;
				DeleteDirectory(strDirName);
			}
			else
			{
				SetFileAttributes(strDirName,FILE_ATTRIBUTE_NORMAL); //去掉文件的系统和隐藏属性
				DeleteFile(strDirName);
			}
		}
	}
	tempFind.Close();
	if(!RemoveDirectory(PUBPATH))
	{
		return false ;
	}
	AfxMessageBox("行程删除成功");
	return true;
}



void CDlgOldTrip::OnBnClickedButtonLookpic()
{
	// TODO: 在此添加控件通知处理程序代码
	CDlgTripPic m_DlgTripPic;
	m_DlgTripPic.DoModal();
}





void CDlgOldTrip::OnLvnItemchangedListTripname(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	int pos=m_list.GetSelectionMark();
	//UpdateData(FALSE);
	*pResult = 0;
}




void CDlgOldTrip::OnBnClickedButtonLooktrack()
{
	// TODO: 在此添加控件通知处理程序代码
	CComQIPtr<IHTMLDocument2> spDoc = m_oldmap.get_Document();
	CComDispatchDriver spScript;
	spDoc->get_Script(&spScript);
	CComVariant  var;
	spScript.Invoke1(L"drivecar", &var);
}


void CDlgOldTrip::dataupdate()
{
	m_list.DeleteAllItems();
	CDaoRecordset Dbset(&db);    //记录集，文件读写和删除操作

	CString Filepath = "TripData.mdb";
	CString STripName, SDirectPath, STxtPath;
	int i = 0;
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE, "SELECT * FROM TripDataTable", 0);
	while (!Dbset.IsEOF())
	{
		COleVariant var1;                // 字段类型
		var1.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("TripName", var1);
		STripName = (LPCSTR)var1.pbstrVal;

		COleVariant var2;                // 字段类型
		var2.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("DirectPath", var2);
		SDirectPath = (LPCSTR)var2.pbstrVal;

		COleVariant var3;                // 字段类型
		var3.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("TxtPath", var3);
		STxtPath = (LPCSTR)var3.pbstrVal;

		m_list.InsertItem(i, "");
		m_list.SetItemText(i, 0, STripName);
		i++;
		Dbset.MoveNext();
	}
	Dbset.Close();
	db.Close();

	m_list.UpdateWindow();
}
