
#include "stdafx.h"

#include "PropertiesWnd.h"
#include "Resource.h"
#include "MainFrm.h"
#include "EditorMFC.h"
#include "IWorldObj.h"
#include "ModuleBase.h"
#include "Mesh.h"
#include "Transform.h"
#include "RasterCamera.h"
#include "MathDefine.h"
#include "MeshResource.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
//
class CMFCFloatGridProperty :public CMFCPropertyGridProperty
{
public:
	//CMFCFloatGridProperty(){};
	CMFCFloatGridProperty(const CString& strGroupName, DWORD_PTR dwData = 0, BOOL bIsValueList = FALSE)
		:CMFCPropertyGridProperty(strGroupName,dwData,bIsValueList)
	{

	}
	CMFCFloatGridProperty(const CString& strName, const COleVariant& varValue, LPCTSTR lpszDescr = NULL, DWORD_PTR dwData = 0,
		LPCTSTR lpszEditMask = NULL, LPCTSTR lpszEditTemplate = NULL, LPCTSTR lpszValidChars = NULL)
		:CMFCPropertyGridProperty(strName,varValue,lpszDescr,dwData,lpszEditMask,lpszEditTemplate,lpszValidChars)
	{

	}
	virtual ~CMFCFloatGridProperty(){};
	//virtual CString FormatProperty()
	//{
	//	float value = *m_varValue.pfltVal;
	//	return CMFCFloatGridProperty::FormatProperty();
	//}
};
//

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar

CPropertiesWnd::CPropertiesWnd()
{
	m_nComboHeight = 0;
}

CPropertiesWnd::~CPropertiesWnd()
{
}

BEGIN_MESSAGE_MAP(CPropertiesWnd, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_EXPAND_ALL, OnExpandAllProperties)
	ON_UPDATE_COMMAND_UI(ID_EXPAND_ALL, OnUpdateExpandAllProperties)
	ON_COMMAND(ID_SORTPROPERTIES, OnSortProperties)
	ON_UPDATE_COMMAND_UI(ID_SORTPROPERTIES, OnUpdateSortProperties)
	ON_COMMAND(ID_PROPERTIES1, OnProperties1)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES1, OnUpdateProperties1)
	ON_COMMAND(ID_PROPERTIES2, OnProperties2)
	ON_UPDATE_COMMAND_UI(ID_PROPERTIES2, OnUpdateProperties2)
	ON_WM_SETFOCUS()
	ON_WM_SETTINGCHANGE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResourceViewBar 消息处理程序

void CPropertiesWnd::AdjustLayout()
{
	if (GetSafeHwnd () == NULL || (AfxGetMainWnd() != NULL && AfxGetMainWnd()->IsIconic()))
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndObjectCombo.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), m_nComboHeight, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPropList.SetWindowPos(NULL, rectClient.left, rectClient.top + m_nComboHeight + cyTlb, rectClient.Width(), rectClient.Height() -(m_nComboHeight+cyTlb), SWP_NOACTIVATE | SWP_NOZORDER);
}

int CPropertiesWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建组合: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_BORDER | CBS_SORT | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndObjectCombo.Create(dwViewStyle, rectDummy, this, 1))
	{
		TRACE0("未能创建属性组合 \n");
		return -1;      // 未能创建
	}

	m_wndObjectCombo.AddString(_T("应用程序"));
	m_wndObjectCombo.AddString(_T("属性窗口"));
	m_wndObjectCombo.SetCurSel(0);

	CRect rectCombo;
	m_wndObjectCombo.GetClientRect (&rectCombo);

	m_nComboHeight = rectCombo.Height();

	if (!m_wndPropList.Create(WS_VISIBLE | WS_CHILD, rectDummy, this, 2))
	{
		TRACE0("未能创建属性网格\n");
		return -1;      // 未能创建
	}

	InitPropList();

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_PROPERTIES);
	m_wndToolBar.LoadToolBar(IDR_PROPERTIES, 0, 0, TRUE /* 已锁定*/);
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_PROPERTIES_HC : IDR_PROPERTIES, 0, 0, TRUE /* 锁定*/);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));
	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	AdjustLayout();
	return 0;
}

void CPropertiesWnd::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPropertiesWnd::OnExpandAllProperties()
{
	m_wndPropList.ExpandAll();
}

void CPropertiesWnd::OnUpdateExpandAllProperties(CCmdUI* /* pCmdUI */)
{
}

void CPropertiesWnd::OnSortProperties()
{
	m_wndPropList.SetAlphabeticMode(!m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnUpdateSortProperties(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndPropList.IsAlphabeticMode());
}

void CPropertiesWnd::OnProperties1()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties1(CCmdUI* /*pCmdUI*/)
{
	// TODO:  在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::OnProperties2()
{
	// TODO:  在此处添加命令处理程序代码
}

void CPropertiesWnd::OnUpdateProperties2(CCmdUI* /*pCmdUI*/)
{
	// TODO:  在此处添加命令更新 UI 处理程序代码
}

void CPropertiesWnd::InitPropList()
{
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();

	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("外观"));

	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("三维外观"), (_variant_t) false, _T("指定窗口的字体不使用粗体，并且控件将使用三维边框")));

	CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("边框"), _T("对话框外框"), _T("其中之一: “无”、“细”、“可调整大小”或“对话框外框”"));
	pProp->AddOption(_T("无"));
	pProp->AddOption(_T("细"));
	pProp->AddOption(_T("可调整大小"));
	pProp->AddOption(_T("对话框外框"));
	pProp->AllowEdit(FALSE);

	pGroup1->AddSubItem(pProp);
	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("标题"), (_variant_t) _T("关于"), _T("指定窗口标题栏中显示的文本")));

	m_wndPropList.AddProperty(pGroup1);

	CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("窗口大小"), 0, TRUE);

	pProp = new CMFCPropertyGridProperty(_T("高度"), (_variant_t) 250l, _T("指定窗口的高度"));
	pProp->EnableSpinControl(TRUE, 50, 300);
	pSize->AddSubItem(pProp);

	pProp = new CMFCPropertyGridProperty( _T("宽度"), (_variant_t) 150l, _T("指定窗口的宽度"));
	pProp->EnableSpinControl(TRUE, 50, 200);
	pSize->AddSubItem(pProp);

	m_wndPropList.AddProperty(pSize);

	CMFCPropertyGridProperty* pGroup2 = new CMFCPropertyGridProperty(_T("字体"));

	LOGFONT lf;
	CFont* font = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	font->GetLogFont(&lf);

	lstrcpy(lf.lfFaceName, _T("宋体, Arial"));

	pGroup2->AddSubItem(new CMFCPropertyGridFontProperty(_T("字体"), lf, CF_EFFECTS | CF_SCREENFONTS, _T("指定窗口的默认字体")));
	pGroup2->AddSubItem(new CMFCPropertyGridProperty(_T("使用系统字体"), (_variant_t) true, _T("指定窗口使用“MS Shell Dlg”字体")));

	m_wndPropList.AddProperty(pGroup2);

	CMFCPropertyGridProperty* pGroup3 = new CMFCPropertyGridProperty(_T("杂项"));
	pProp = new CMFCPropertyGridProperty(_T("(名称)"), _T("应用程序"));
	pProp->Enable(FALSE);
	pGroup3->AddSubItem(pProp);

	CMFCPropertyGridColorProperty* pColorProp = new CMFCPropertyGridColorProperty(_T("窗口颜色"), RGB(210, 192, 254), NULL, _T("指定默认的窗口颜色"));
	pColorProp->EnableOtherButton(_T("其他..."));
	pColorProp->EnableAutomaticButton(_T("默认"), ::GetSysColor(COLOR_3DFACE));
	pGroup3->AddSubItem(pColorProp);

	static const TCHAR szFilter[] = _T("图标文件(*.ico)|*.ico|所有文件(*.*)|*.*||");
	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("图标"), TRUE, _T(""), _T("ico"), 0, szFilter, _T("指定窗口图标")));

	pGroup3->AddSubItem(new CMFCPropertyGridFileProperty(_T("文件夹"), _T("c:\\")));

	m_wndPropList.AddProperty(pGroup3);

	CMFCPropertyGridProperty* pGroup4 = new CMFCPropertyGridProperty(_T("层次结构"));

	CMFCPropertyGridProperty* pGroup41 = new CMFCPropertyGridProperty(_T("第一个子级"));
	pGroup4->AddSubItem(pGroup41);

	CMFCPropertyGridProperty* pGroup411 = new CMFCPropertyGridProperty(_T("第二个子级"));
	pGroup41->AddSubItem(pGroup411);

	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 1"), (_variant_t) _T("值 1"), _T("此为说明")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 2"), (_variant_t) _T("值 2"), _T("此为说明")));
	pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 3"), (_variant_t) _T("值 3"), _T("此为说明")));

	pGroup4->Expand(FALSE);
	m_wndPropList.AddProperty(pGroup4);
}

void CPropertiesWnd::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);
	m_wndPropList.SetFocus();
}

void CPropertiesWnd::OnSettingChange(UINT uFlags, LPCTSTR lpszSection)
{
	CDockablePane::OnSettingChange(uFlags, lpszSection);
	SetPropListFont();
}

void CPropertiesWnd::SetPropListFont()
{
	::DeleteObject(m_fntPropList.Detach());

	LOGFONT lf;
	afxGlobalData.fontRegular.GetLogFont(&lf);

	NONCLIENTMETRICS info;
	info.cbSize = sizeof(info);

	afxGlobalData.GetNonClientMetrics(info);

	lf.lfHeight = info.lfMenuFont.lfHeight;
	lf.lfWeight = info.lfMenuFont.lfWeight;
	lf.lfItalic = info.lfMenuFont.lfItalic;

	m_fntPropList.CreateFontIndirect(&lf);

	m_wndPropList.SetFont(&m_fntPropList);
	m_wndObjectCombo.SetFont(&m_fntPropList);
}

void CPropertiesWnd::UpdateWorldObjProperty(shared_ptr<IWorldObj> pObj)
{
	ShowPane(TRUE, FALSE, TRUE);
	SetPropListFont();

	m_wndPropList.EnableHeaderCtrl(FALSE);
	m_wndPropList.EnableDescriptionArea();
	m_wndPropList.SetVSDotNetLook();
	m_wndPropList.MarkModifiedProperties();
	//
	m_wndPropList.RemoveAll();
	if (pObj == nullptr)
	{
		return;
	}
	CMFCPropertyGridProperty* pGroup1 = new CMFCPropertyGridProperty(_T("基本信息"));


	pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("Name"), pObj->m_strName.c_str()));

	//CMFCPropertyGridProperty* pProp = new CMFCPropertyGridProperty(_T("边框"), _T("对话框外框"), _T("其中之一: “无”、“细”、“可调整大小”或“对话框外框”"));
	//pProp->AddOption(_T("无"));
	//pProp->AddOption(_T("细"));
	//pProp->AddOption(_T("可调整大小"));
	//pProp->AddOption(_T("对话框外框"));
	//pProp->AllowEdit(FALSE);

	//pGroup1->AddSubItem(pProp);
	//pGroup1->AddSubItem(new CMFCPropertyGridProperty(_T("标题"), (_variant_t)_T("关于"), _T("指定窗口标题栏中显示的文本")));

	m_wndPropList.AddProperty(pGroup1);
	//
	for (int i = 0; i < pObj->GetModuleCount(); ++i)
	{
		std::shared_ptr<ModuleBase> pModule = pObj->GetModule(i);
		AddModule(pModule);
	}
}

void CPropertiesWnd::AddModule(shared_ptr<ModuleBase> pModule)
{
	//CMFCPropertyGridProperty* pSize = new CMFCPropertyGridProperty(_T("窗口大小"), 0, TRUE);

	//pProp = new CMFCPropertyGridProperty(_T("高度"), (_variant_t)250l, _T("指定窗口的高度"));
	//pProp->EnableSpinControl(TRUE, 50, 300);
	//pSize->AddSubItem(pProp);

	//pProp = new CMFCPropertyGridProperty(_T("宽度"), (_variant_t)150l, _T("指定窗口的宽度"));
	//pProp->EnableSpinControl(TRUE, 50, 200);
	//pSize->AddSubItem(pProp);

	//m_wndPropList.AddProperty(pSize);
	const type_info& tinfo = typeid(*pModule.get());
	std::string className = tinfo.name();
	if (typeid(*pModule.get()) == typeid(Transform))
	{
		//
		shared_ptr<Transform> pTransform = dynamic_pointer_cast<Transform>(pModule);
		//
		CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Transform"));
		//translate
		CMFCPropertyGridProperty* pGroupTranslate = new CMFCPropertyGridProperty(_T("Translate"));
		pGroup->AddSubItem(pGroupTranslate);
		CMFCFloatGridProperty* pProp = new CMFCFloatGridProperty(_T("x"), (_variant_t)pTransform->GetLocalTranslate().m_fx, "translate_x");
		//pProp->EnableSpinControl(TRUE, MINFLOAT, MAXFLOAT);
		pGroupTranslate->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("y"), (_variant_t)pTransform->GetLocalTranslate().m_fy, "translate_y");
		pGroupTranslate->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("z"), (_variant_t)pTransform->GetLocalTranslate().m_fz, "translate_z");
		pGroupTranslate->AddSubItem(pProp);
		

		//rotation
		CMFCPropertyGridProperty* pGroupRotation = new CMFCPropertyGridProperty(_T("Rotation"));
		pGroup->AddSubItem(pGroupRotation);
		pProp = new CMFCFloatGridProperty(_T("x"), (_variant_t)pTransform->GetOrientation().m_vecEulerAngle.m_fx, "rotation_x");
		//pProp->EnableSpinControl(TRUE, MINFLOAT, MAXFLOAT);
		pGroupRotation->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("y"), (_variant_t)pTransform->GetOrientation().m_vecEulerAngle.m_fy, "rotation_y");
		pGroupRotation->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("z"), (_variant_t)pTransform->GetOrientation().m_vecEulerAngle.m_fz, "rotation_z");
		pGroupRotation->AddSubItem(pProp);

		//scale
		CMFCPropertyGridProperty* pGroupScale = new CMFCPropertyGridProperty(_T("Scale"));
		pGroup->AddSubItem(pGroupScale);
		pProp = new CMFCFloatGridProperty(_T("x"), (_variant_t)pTransform->GetScale().m_fx, "scale_x");
		//pProp->EnableSpinControl(TRUE, MINFLOAT, MAXFLOAT);
		pGroupScale->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("y"), (_variant_t)pTransform->GetScale().m_fy, "scale_y");
		pGroupScale->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("z"), (_variant_t)pTransform->GetScale().m_fz, "scale_z");
		pGroupScale->AddSubItem(pProp);

		//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 1"), (_variant_t)_T("值 1"), _T("此为说明")));
		//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 2"), (_variant_t)_T("值 2"), _T("此为说明")));
		//pGroup411->AddSubItem(new CMFCPropertyGridProperty(_T("项 3"), (_variant_t)_T("值 3"), _T("此为说明")));
		m_wndPropList.AddProperty(pGroup);
	}
	if (typeid(*pModule.get()) == typeid(Mesh))
	{
		shared_ptr<Mesh> pMesh = dynamic_pointer_cast<Mesh>(pModule);
		CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Mesh"));
		std::string pMeshRef = "";
		if (pMesh->GetMeshResource() != nullptr)
		{
			pMeshRef = pMesh->GetMeshResource()->GetRefPath();
		}
		CMFCPropertyGridFileProperty* pFile = new CMFCPropertyGridFileProperty("MeshFile", pMeshRef.c_str());
		pGroup->AddSubItem(pFile);


		m_wndPropList.AddProperty(pGroup);
	}
	if (typeid(*pModule.get()) == typeid(RasterCamera))
	{
		//float m_fFovy;
		//float m_fAspect;
		//float m_fNear;
		//float m_fFar;
		shared_ptr<RasterCamera> pCamera = dynamic_pointer_cast<RasterCamera>(pModule);
		CMFCPropertyGridProperty* pGroup = new CMFCPropertyGridProperty(_T("Camera"));
		CMFCFloatGridProperty* pProp = new CMFCFloatGridProperty(_T("FOV"), (_variant_t)pCamera->m_fFovy, "CAMERAFOV");
		pGroup->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("Aspect"), (_variant_t)pCamera->m_fAspect, "CAMERAFOV");
		pGroup->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("Near Plane"), (_variant_t)pCamera->m_fNear, "NEARPLANE");
		pGroup->AddSubItem(pProp);
		pProp = new CMFCFloatGridProperty(_T("Far Plane"), (_variant_t)pCamera->m_fFar, "FARPLANE");
		pGroup->AddSubItem(pProp);
		m_wndPropList.AddProperty(pGroup);
	}
}
