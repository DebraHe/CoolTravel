// DlgOldTrip.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "DlgOldTrip.h"
#include "afxdialogex.h"

#include <afxdao.h>         //dao������ʵ�����ݿ�Ķ�д
#include <comdef.h>         //�����ݸ�ʽת����ʱ����õ�

// CDlgOldTrip �Ի���
extern CDaoDatabase db;    //���ݿ�

//CDaoRecordset Dbset(&db);    //��¼�������������ܽ��ж�д�Լ�ɾ������


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

	CString ProjectPath= GetMoudulePath();    //���ú�����ù���Ŀ¼
	CString mapPath="\\mapold.htm";            // ��  ��\\����������Լ���html����  ע��html��÷��ڹ���Ŀ¼��
	mapPath=ProjectPath+mapPath;          //��ñ�����ַ
	m_oldmap.Navigate(mapPath,NULL,NULL,NULL,NULL);	


	DDX_Text(pDX, IDC_EDIT_Trip, m_trip);
	DDV_MaxChars(pDX, m_trip, 500);
	DDX_Control(pDX, IDC_LIST_TripName, m_list);

	CRect rect;
	m_list.GetClientRect(&rect);
	double nColInterval = rect.Width();
	m_list.SetExtendedStyle(LVS_EX_FLATSB|LVS_EX_FULLROWSELECT|LVS_EX_HEADERDRAGDROP|LVS_EX_ONECLICKACTIVATE|LVS_EX_GRIDLINES);  //������չ��ʽ
	m_list.InsertColumn(0,"�ҵ������г�",LVCFMT_LEFT,nColInterval);    //����г�����

	m_list.DeleteAllItems();
	//��ȡ���ݿ�����
	CDaoRecordset Dbset(&db);    //��¼�����ļ���д��ɾ������

	CString Filepath = "TripData.mdb";
	CString STripName, SDirectPath, STxtPath;
	int i = 0;
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE, "SELECT * FROM TripDataTable", 0);
	while (!Dbset.IsEOF())
	{
		COleVariant var1;                // �ֶ�����
		var1.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("TripName", var1);
		STripName = (LPCSTR)var1.pbstrVal;

		COleVariant var2;                // �ֶ�����
		var2.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("DirectPath", var2);
		SDirectPath = (LPCSTR)var2.pbstrVal;

		COleVariant var3;                // �ֶ�����
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


// CDlgOldTrip ��Ϣ�������




void CDlgOldTrip::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (HTCAPTION == nHitTest) 
	{
		return;
	}
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


void CDlgOldTrip::OnBnClickedButtonLoadpoint()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//�������ݿ�
	/*CString ProjectPath = GetMoudulePath();    //���ú�����ù���Ŀ¼
	CString mapPath = "\\mapold.htm";            // ��  ��\\����������Լ���html����  ע��html��÷��ڹ���Ŀ¼��
	mapPath = ProjectPath + mapPath;          //��ñ�����ַ
	m_oldmap.Navigate(mapPath, NULL, NULL, NULL, NULL);
	*/


	CString DirectPath, TxtPath;
	const int pos =m_list.GetSelectionMark();   //ѡ���е�������
	if(!(pos+1))   //���û��ѡ�дӵ�һ�е����һ�У�����ʾѡ����
	{
		MessageBox("����ѡ����Ҫ�鿴���г̣�","������ʾ");
	}
	else
	{
		CString Filepath="TripData.mdb";
		db.Open(Filepath);
		CDaoRecordset Dbset(&db);    //��¼�����ļ���д��ɾ������
		Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT *FROM TripDataTable",0);		
		int i=0;		
		while(!Dbset.IsEOF())
		{
			if(i==pos)
			{
				COleVariant var2;                // �ֶ�����
				var2.ChangeType(VT_BSTR,NULL);
				Dbset.GetFieldValue("DirectPath",var2);
				DirectPath= (LPCSTR)var2.pbstrVal;

				COleVariant var3;                // �ֶ�����
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
		spScript.Invoke1(L"Picture", &varpic, &varmap); //varpic ��ͼƬ�ĵ�ַ 

		CFile fFile(TxtPath, CFile::modeRead);
		CStringA strFile;
		fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());
		fFile.Close();
		strFile.ReleaseBuffer();
		CComVariant vartxt = strFile;
		spScript.Invoke1(L"Message", &vartxt, &varmap); //vatxt3 ��txt�ĵ�ַ 

		CComVariant varJD, varWD;
		varJD = JD[m];
		varWD = WD[m];
		spScript.Invoke2(L"MakePoint", &varJD, &varWD, &varmap);
		spScript.Invoke1(L"goodview", &varmap);
	}
	

	CEdit* pedit = (CEdit*)GetDlgItem(IDC_EDIT_Trip);
	pedit->LineScroll(pedit->GetLineCount());
	CFile file;                                         // �ļ�����
	DWORD len;                                    // ���ڱ����ļ�����
	// ��ȡ����
	file.Open(TxtPath, CFile::modeReadWrite);
	len = file.GetLength();
	char *pReadData = new char[len + 1]; // �����ڴ�
	file.Read(pReadData, len);                                       //  ���ﱣ��Ķ�ȡ�ļ�������
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
	//��CStringת����char*
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
			spScript.Invoke1(L"Picture", &varpic, &varmap); //varpic ��ͼƬ�ĵ�ַ 

			CFile fFile(filenametxt, CFile::modeRead);
			CStringA strFile;
			fFile.Read(strFile.GetBufferSetLength(fFile.GetLength()), fFile.GetLength());
			fFile.Close();
			strFile.ReleaseBuffer();
			CComVariant vartxt = strFile;
			spScript.Invoke1(L"Message", &vartxt, &varmap); //vatxt3 ��txt�ĵ�ַ 

			CComVariant varJD, varWD;
			varJD = m_exifinfo.Longitude;
			varWD = m_exifinfo.Latitude;
			spScript.Invoke2(L"MakePoint", &varJD, &varWD, &varmap);


			//spScript.Invoke1(L"goodview", &varmap);
		}
	}
	MessageBox("���ͼ���ϵĺ�ɫ����о�ϲ��", "��ܰ��ʾ");	
	*/
}

void CDlgOldTrip::GetInfo(CString str)
{
	
	i++;
	//����
	CFileFind f;
	bool t = f.FindFile(str + "\\*.jpg");
	while (t)
	{ 
		
		t = f.FindNextFile();
		if (!f.IsDots())
		{
			//����һЩ׼��
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
				//��ȡ��γ��
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	const int pos =m_list.GetSelectionMark();   //ѡ���е�������
	if(!(pos+1))   //���û��ѡ�дӵ�һ�е����һ�У�����ʾѡ����
	{
		MessageBox("����ѡ����Ҫɾ�����г̣�","������ʾ");
	}
	else
	{
		CString Filepath="TripData.mdb";
		db.Open(Filepath);
		CDaoRecordset Dbset(&db);    //��¼�����ļ���д��ɾ������
		Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT *FROM TripDataTable",0);
		Dbset.Move(pos);   //����¼����ָ���ƶ�����ǰ���ݵ�����
		Dbset.Delete();    //ɾ������
		Dbset.Close();
		db.Close();
		m_list.DeleteAllItems();
		OnInitDialog();   //��������������ˢ���б�

	
		/*CString SDirectPath;
		int i=0;
		db.Open(Filepath);
		Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripDataTable",0);
		while(!Dbset.IsEOF())
		{
			if(i==pos)
			{
				COleVariant var2;                // �ֶ�����
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


//ɾ��ָ��Ŀ¼�ļ���
bool CDlgOldTrip::DeleteDirectory(CString DirName)
{

	//AfxMessageBox("ִ��ɾ���ļ���:"+DirName);
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
				SetFileAttributes(strDirName,FILE_ATTRIBUTE_NORMAL); //ȥ���ļ���ϵͳ����������
				DeleteFile(strDirName);
			}
		}
	}
	tempFind.Close();
	if(!RemoveDirectory(PUBPATH))
	{
		return false ;
	}
	AfxMessageBox("�г�ɾ���ɹ�");
	return true;
}



void CDlgOldTrip::OnBnClickedButtonLookpic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDlgTripPic m_DlgTripPic;
	m_DlgTripPic.DoModal();
}





void CDlgOldTrip::OnLvnItemchangedListTripname(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int pos=m_list.GetSelectionMark();
	//UpdateData(FALSE);
	*pResult = 0;
}




void CDlgOldTrip::OnBnClickedButtonLooktrack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CComQIPtr<IHTMLDocument2> spDoc = m_oldmap.get_Document();
	CComDispatchDriver spScript;
	spDoc->get_Script(&spScript);
	CComVariant  var;
	spScript.Invoke1(L"drivecar", &var);
}


void CDlgOldTrip::dataupdate()
{
	m_list.DeleteAllItems();
	CDaoRecordset Dbset(&db);    //��¼�����ļ���д��ɾ������

	CString Filepath = "TripData.mdb";
	CString STripName, SDirectPath, STxtPath;
	int i = 0;
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE, "SELECT * FROM TripDataTable", 0);
	while (!Dbset.IsEOF())
	{
		COleVariant var1;                // �ֶ�����
		var1.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("TripName", var1);
		STripName = (LPCSTR)var1.pbstrVal;

		COleVariant var2;                // �ֶ�����
		var2.ChangeType(VT_BSTR, NULL);
		Dbset.GetFieldValue("DirectPath", var2);
		SDirectPath = (LPCSTR)var2.pbstrVal;

		COleVariant var3;                // �ֶ�����
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
