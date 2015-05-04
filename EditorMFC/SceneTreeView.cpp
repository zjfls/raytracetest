#include "stdafx.h"
#include "SceneTreeView.h"
#include "Resource.h"
#include "EditorMFC.h"
#include "IWorld.h"
#include "IWorldObj.h"
#include "EditorApplication.h"
#include "PropertiesWnd.h"
#include "MainFrm.h"
extern CEditorMFCApp theApp;

struct stSceneNodeAttribute
{
	std::shared_ptr<IWorldObj> m_pObj;
};

class CSceneTreeViewMenuButton : public CMFCToolBarMenuButton
{
	friend class CClassView;

	DECLARE_SERIAL(CSceneTreeViewMenuButton)

public:
	CSceneTreeViewMenuButton(HMENU hMenu = NULL) : CMFCToolBarMenuButton((UINT)-1, hMenu, -1)
	{
	}

	virtual void OnDraw(CDC* pDC, const CRect& rect, CMFCToolBarImages* pImages, BOOL bHorz = TRUE,
		BOOL bCustomizeMode = FALSE, BOOL bHighlight = FALSE, BOOL bDrawBorder = TRUE, BOOL bGrayDisabledButtons = TRUE)
	{
		pImages = CMFCToolBar::GetImages();

		CAfxDrawState ds;
		pImages->PrepareDrawImage(ds);

		CMFCToolBarMenuButton::OnDraw(pDC, rect, pImages, bHorz, bCustomizeMode, bHighlight, bDrawBorder, bGrayDisabledButtons);

		pImages->EndDrawImage(ds);
	}
	shared_ptr<IWorldObj> m_pTarget;
};
IMPLEMENT_SERIAL(CSceneTreeViewMenuButton, CMFCToolBarMenuButton, 1)
///
CSceneTreeView::CSceneTreeView()
{
	m_nCurrSort = ID_SORTING_GROUPBYTYPE;
}
BEGIN_MESSAGE_MAP(CSceneTreeView, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
	ON_COMMAND(ID_NEW_FOLDER, OnNewFolder)
	ON_NOTIFY(TVN_SELCHANGED, 2,OnTreeSelect)
END_MESSAGE_MAP()

CSceneTreeView::~CSceneTreeView()
{
}

int CSceneTreeView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// 创建视图: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	if (!m_wndTreeView.Create(dwViewStyle, rectDummy, this, 2))
	{
		TRACE0("未能创建场景视图\n");
		return -1;      // 未能创建
	}


	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_SORT);
	m_wndToolBar.LoadToolBar(IDR_SORT, 0, 0, TRUE /* 已锁定*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);
	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// 所有命令将通过此控件路由，而不是通过主框架路由: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	CMenu menuSort;
	menuSort.LoadMenu(IDR_POPUP_SORT);

	m_wndToolBar.ReplaceButton(ID_SORT_MENU, CSceneTreeViewMenuButton(menuSort.GetSubMenu(0)->GetSafeHmenu()));

	CSceneTreeViewMenuButton* pButton = DYNAMIC_DOWNCAST(CSceneTreeViewMenuButton, m_wndToolBar.GetButton(0));
	if (pButton != NULL)
	{
		pButton->m_bText = FALSE;
		pButton->m_bImage = TRUE;
		pButton->SetImage(GetCmdMgr()->GetCmdImage(m_nCurrSort));
		pButton->SetMessageWnd(this);
	}


	return 0;
}

void CSceneTreeView::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CSceneTreeView::OnPaint()
{
	CPaintDC dc(this); // 用于绘制的设备上下文

	CRect rectTree;
	m_wndTreeView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CSceneTreeView::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndTreeView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CSceneTreeView::OnChangeVisualStyle()
{
	m_SceneTreeViewImg.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_CLASS_VIEW_24 : IDB_CLASS_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("无法加载位图:  %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_SceneTreeViewImg.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_SceneTreeViewImg.Add(&bmp, RGB(255, 0, 0));

	m_wndTreeView.SetImageList(&m_SceneTreeViewImg, TVSIL_NORMAL);

	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_SORT_24 : IDR_SORT, 0, 0, TRUE /* 锁定*/);
}

void CSceneTreeView::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndTreeView.SetFocus();
}

void CSceneTreeView::OnNewFolder()
{

}

void CSceneTreeView::InitSceneTreeView()
{
	shared_ptr<IWorldObj> pObj = EditorApplication::GetInstance()->m_pWorld->m_pRoot;
	for (int i = 0; i < pObj->GetChildCount(); ++i)
	{
		AddWorldObj(pObj->GetChild(i),nullptr);
	}
}

void CSceneTreeView::AddWorldObj(shared_ptr<IWorldObj> pObj, HTREEITEM* pParent)
{
	HTREEITEM hItem;
	if (pParent == nullptr)
	{
		hItem = m_wndTreeView.InsertItem(pObj->m_strName.c_str(), 0, 0);
	}
	else
	{
		hItem = m_wndTreeView.InsertItem(pObj->m_strName.c_str(), 0, 0, *pParent);
	}
	stSceneNodeAttribute* pNodeAttribute = new stSceneNodeAttribute();
	pNodeAttribute->m_pObj = pObj;
	m_wndTreeView.SetItemData(hItem, DWORD_PTR(pNodeAttribute));
	for (int i = 0; i < pObj->GetChildCount(); ++i)
	{
		AddWorldObj(pObj->GetChild(i),&hItem);
	}
}

void CSceneTreeView::OnTreeSelect(NMHDR * pNMHDR, LRESULT * pResult)
{
	HTREEITEM item = m_wndTreeView.GetSelectedItem();
	CString str = m_wndTreeView.GetItemText(item);
	//std::cout << "select tree item:"<<LPCSTR(str) << std::endl;
	stSceneNodeAttribute* pAttribute = (stSceneNodeAttribute*)m_wndTreeView.GetItemData(item);
	shared_ptr<IWorldObj> pObj = pAttribute->m_pObj;
	EditorApplication::GetInstance()->OnSelectChange(pObj);
}

