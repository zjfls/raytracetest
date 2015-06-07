
// EditorMFC.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "EditorMFC.h"
#include "MainFrm.h"

#include "ChildFrm.h"
#include "EditorMFCDoc.h"
#include "EditorMFCView.h"
#include "EditorApplication.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "MainFrm.h"
#include "SceneTreeView.h"
#include <memory>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorMFCApp

BEGIN_MESSAGE_MAP(CEditorMFCApp, CWinAppEx)
	ON_COMMAND(ID_APP_ABOUT, &CEditorMFCApp::OnAppAbout)
	// 基于文件的标准文档命令
	ON_COMMAND(ID_FILE_NEW, &CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinAppEx::OnFileOpen)
	// 标准打印设置命令
	ON_COMMAND(ID_FILE_PRINT_SETUP, &CWinAppEx::OnFilePrintSetup)
END_MESSAGE_MAP()


// CEditorMFCApp 构造

CEditorMFCApp::CEditorMFCApp()
{
	m_bHiColorIcons = TRUE;

	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// 如果应用程序是利用公共语言运行时支持(/clr)构建的，则: 
	//     1) 必须有此附加设置，“重新启动管理器”支持才能正常工作。
	//     2) 在您的项目中，您必须按照生成顺序向 System.Windows.Forms 添加引用。
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  将以下应用程序 ID 字符串替换为唯一的 ID 字符串；建议的字符串格式
	//为 CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("EditorMFC.AppID.NoVersion"));

	// TODO:  在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}

// 唯一的一个 CEditorMFCApp 对象

CEditorMFCApp theApp;
// 生成的此标识符在统计上对于您的应用程序是唯一的
// 如果您更愿选择一个特定的标识符，则可以更改它

// {7A262AAF-1B37-4978-898F-00C4484FEDA0}
static const CLSID clsid =
{ 0x7A262AAF, 0x1B37, 0x4978, { 0x89, 0x8F, 0x0, 0xC4, 0x48, 0x4F, 0xED, 0xA0 } };

const GUID CDECL _tlid = { 0x363BA34B, 0x5483, 0x4B1D, { 0x8C, 0x85, 0x8C, 0x14, 0x56, 0x40, 0x20, 0xC6 } };
const WORD _wVerMajor = 1;
const WORD _wVerMinor = 0;


// CEditorMFCApp 初始化

BOOL CEditorMFCApp::InitInstance()
{
	//
	AllocConsole();
	FILE* pFile;
	freopen_s(&pFile, "CONOUT$", "w+t", stdout);
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// 初始化 OLE 库
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction();

	// 使用 RichEdit 控件需要  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO:  应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));
	LoadStdProfileSettings(2);  // 加载标准 INI 文件选项(包括 MRU)


	InitContextMenuManager();
	InitShellManager();

	InitKeyboardManager();

	InitTooltipManager();
	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;
	theApp.GetTooltipManager()->SetTooltipParams(AFX_TOOLTIP_TYPE_ALL,
		RUNTIME_CLASS(CMFCToolTipCtrl), &ttParams);

	// 注册应用程序的文档模板。  文档模板
	// 将用作文档、框架窗口和视图之间的连接
	CMultiDocTemplate* pDocTemplate;
	pDocTemplate = new CMultiDocTemplate(IDR_EditorMFCTYPE,
		RUNTIME_CLASS(CEditorMFCDoc),
		RUNTIME_CLASS(CChildFrame), // 自定义 MDI 子框架
		RUNTIME_CLASS(CEditorMFCView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);
	// 将 COleTemplateServer 连接到文档模板
	// COleTemplateServer 通过使用
	// 文档模板中指定的信息来为请求 OLE 容器
	// 创建新文档
	m_server.ConnectTemplate(clsid, pDocTemplate, FALSE);
	// 将所有的 OLE 服务器工厂注册为正在运行。  这将启用
	//  OLE 库以从其他应用程序中创建对象
	COleTemplateServer::RegisterAll();
		// 注意:  MDI 应用程序将注册所有的服务器对象，而不管
		// 命令行上的 /Embedding 或 /Automation

	// 创建主 MDI 框架窗口
	CMainFrame* pMainFrame = new CMainFrame;
	if (!pMainFrame || !pMainFrame->LoadFrame(IDR_MAINFRAME))
	{
		delete pMainFrame;
		return FALSE;
	}
	m_pMainWnd = pMainFrame;


	// 分析标准 shell 命令、DDE、打开文件操作的命令行
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);
	//


	// 应用程序是用 /Embedding 或 /Automation 开关启动的。
	//使应用程序作为自动化服务器运行。
	if (cmdInfo.m_bRunEmbedded || cmdInfo.m_bRunAutomated)
	{
		// 不显示主窗口
		return TRUE;
	}
	// 使用 /Unregserver 或 /Unregister 开关启动应用程序。  注销
	// 类型库。  其他注销操作在 ProcessShellCommand() 中发生。
	else if (cmdInfo.m_nShellCommand == CCommandLineInfo::AppUnregister)
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT, NULL, NULL, FALSE);
		AfxOleUnregisterTypeLib(_tlid, _wVerMajor, _wVerMinor);
	}
	// 应用程序是以独立方式或用其他开关(如 /Register
	// 或 /Regserver)启动的。  更新注册表项，包括类型库。
	else
	{
		m_server.UpdateRegistry(OAT_DISPATCH_OBJECT);
		COleObjectFactory::UpdateRegistryAll();
		AfxOleRegisterTypeLib(AfxGetInstanceHandle(), _tlid);
	}
	//
	EditorApplication::GetInstance()->SetWindowID((int)pMainFrame->m_hWnd);
	EditorApplication::GetInstance()->m_pEditorApp = this;
	EditorApplication::GetInstance()->Init(0, nullptr);
	
	// 调度在命令行中指定的命令。  如果
	// 用 /RegServer、/Register、/Unregserver 或 /Unregister 启动应用程序，则返回 FALSE。
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;




	
	// 主窗口已初始化，因此显示它并对其进行更新
	pMainFrame->ShowWindow(m_nCmdShow);
	pMainFrame->UpdateWindow();

	return TRUE;
}

int CEditorMFCApp::ExitInstance()
{
	//TODO:  处理可能已添加的附加资源
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

// CEditorMFCApp 消息处理程序


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// 用于运行对话框的应用程序命令
void CEditorMFCApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CEditorMFCApp 自定义加载/保存方法

void CEditorMFCApp::PreLoadState()
{
	BOOL bNameValid;
	CString strName;
	bNameValid = strName.LoadString(IDS_EDIT_MENU);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EDIT);
	bNameValid = strName.LoadString(IDS_EXPLORER);
	ASSERT(bNameValid);
	GetContextMenuManager()->AddMenu(strName, IDR_POPUP_EXPLORER);
}

void CEditorMFCApp::LoadCustomState()
{
}

void CEditorMFCApp::SaveCustomState()
{
}



//BOOL CEditorMFCApp::OnIdle(LONG lCount)
//{
//	EditorApplication::GetInstance()->Run();
//	return FALSE;
//}

int CEditorMFCApp::Run()
{
	//return CWinAppEx::Run();
	BOOL bDoingBackgroundProcessing = TRUE;
	while (bDoingBackgroundProcessing)
	{
		MSG msg;
		while (::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
		{
			if (!AfxGetApp()->PumpMessage())
			{
				bDoingBackgroundProcessing = FALSE;
				::PostQuitMessage(0);
				break;
			}
		}
		// let MFC do its idle processing
		LONG lIdle = 0;
		while (AfxGetApp()->OnIdle(lIdle++));

		
		EditorApplication::GetInstance()->Run();
		
		// Perform some background processing here  
		// using another call to OnIdle
	}

	return 0;
}

void CEditorMFCApp::OnNotify(string msg, IListenerSubject* pSubject)
{
	CMainFrame* pFrm = (CMainFrame*)m_pMainWnd;
	if (msg == "InitScene")
	{
		pFrm->m_wndSceneTreeView.InitSceneTreeView();
	}
	if (msg == "SelectChange")
	{
		pFrm->m_wndProperties.UpdateWorldObjProperty(EditorApplication::GetInstance()->m_SelectObj);
	}
}

CEditorMFCApp::~CEditorMFCApp()
{

}

// CEditorMFCApp 消息处理程序



