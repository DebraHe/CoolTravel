
// CoolTravel.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "CoolTravelDlg.h"
#include <afxdao.h>
#include<comdef.h>  //�������ݸ�ʽת��

#include "DlgLand.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//����ȫ�ֱ������ڱ�ĵط�����ʱ

CDaoDatabase db;
CDaoRecordset Dbset(&db);    //��¼�����ļ���д��ɾ������
// CCoolTravelApp

BEGIN_MESSAGE_MAP(CCoolTravelApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCoolTravelApp ����

CCoolTravelApp::CCoolTravelApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCoolTravelApp ����

CCoolTravelApp theApp;


// CCoolTravelApp ��ʼ��

BOOL CCoolTravelApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	
	CString Filepath="TripData.mdb";  //�����ݿ��ļ�Data.mdb�ڳ����ͬһĿ¼��
	CFileFind Ffind;             //�ȿ����治�������ݿ��ļ�
	BOOL flag=Ffind.FindFile(Filepath);
	Ffind.Close();

	if(!flag)  //���û�У����Ǿʹ���
	{
		db.Create(Filepath);
		CString sqlcmd="CREATE TABLE TripDataTable(TripName VARCHAR(200),DirectPath VARCHAR(200),TxtPath VARCHAR(200))";  //�����ڲ����������������ԣ����������䣩
		db.Execute(sqlcmd);    //ִ��sqlָ��
		db.Close();//�������һ��Ҫ�رգ��������
		//MessageBox("�г����ݿ��ѽ����ɹ���","������ʾ");
	}
	CString STripName,SDirectPath,STxtPath;
	int i=0;
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripDataTable",0);
	while(!Dbset.IsEOF())
	{
		COleVariant var1;                // �ֶ�����
		var1.ChangeType(VT_BSTR,NULL);
		Dbset.GetFieldValue("TripName",var1);
		STripName= (LPCSTR)var1.pbstrVal;

		COleVariant var2;                // �ֶ�����
		var2.ChangeType(VT_BSTR,NULL);
		Dbset.GetFieldValue("DirectPath",var2);
		SDirectPath= (LPCSTR)var2.pbstrVal;

		COleVariant var3;                // �ֶ�����
		var3.ChangeType(VT_BSTR,NULL);
		Dbset.GetFieldValue("TxtPath",var3);
		STxtPath= (LPCSTR)var3.pbstrVal;

		i++;
		Dbset.MoveNext();
	}
	Dbset.Close();
	db.Close();



	//CDlgLand ldlg;
	//if (ldlg.DoModal() == IDOK)
	{
		CCoolTravelDlg dlg;
		m_pMainWnd = &dlg;
		INT_PTR nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: �ڴ˷��ô����ʱ��
			//  ��ȷ�������رնԻ���Ĵ���
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: �ڴ˷��ô����ʱ��
			//  ��ȡ�������رնԻ���Ĵ���
		}
	}
	//else
		//return FALSE;
	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

