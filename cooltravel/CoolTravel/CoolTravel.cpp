
// CoolTravel.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "CoolTravel.h"
#include "CoolTravelDlg.h"
#include <afxdao.h>
#include<comdef.h>  //用于数据格式转换

#include "DlgLand.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//建立全局变量，在别的地方调用时

CDaoDatabase db;
CDaoRecordset Dbset(&db);    //记录集，文件读写和删除操作
// CCoolTravelApp

BEGIN_MESSAGE_MAP(CCoolTravelApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCoolTravelApp 构造

CCoolTravelApp::CCoolTravelApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCoolTravelApp 对象

CCoolTravelApp theApp;


// CCoolTravelApp 初始化

BOOL CCoolTravelApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	
	CString Filepath="TripData.mdb";  //将数据库文件Data.mdb在程序的同一目录下
	CFileFind Ffind;             //先看看存不存在数据库文件
	BOOL flag=Ffind.FindFile(Filepath);
	Ffind.Close();

	if(!flag)  //如果没有，我们就创建
	{
		db.Create(Filepath);
		CString sqlcmd="CREATE TABLE TripDataTable(TripName VARCHAR(200),DirectPath VARCHAR(200),TxtPath VARCHAR(200))";  //创建内部表，并设置两个属性（姓名，年龄）
		db.Execute(sqlcmd);    //执行sql指令
		db.Close();//创建完成一定要关闭，否则出错
		//MessageBox("行程数据库已建立成功！","温情提示");
	}
	CString STripName,SDirectPath,STxtPath;
	int i=0;
	db.Open(Filepath);
	Dbset.Open(AFX_DAO_USE_DEFAULT_TYPE,"SELECT * FROM TripDataTable",0);
	while(!Dbset.IsEOF())
	{
		COleVariant var1;                // 字段类型
		var1.ChangeType(VT_BSTR,NULL);
		Dbset.GetFieldValue("TripName",var1);
		STripName= (LPCSTR)var1.pbstrVal;

		COleVariant var2;                // 字段类型
		var2.ChangeType(VT_BSTR,NULL);
		Dbset.GetFieldValue("DirectPath",var2);
		SDirectPath= (LPCSTR)var2.pbstrVal;

		COleVariant var3;                // 字段类型
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
			// TODO: 在此放置处理何时用
			//  “确定”来关闭对话框的代码
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: 在此放置处理何时用
			//  “取消”来关闭对话框的代码
		}
	}
	//else
		//return FALSE;
	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

