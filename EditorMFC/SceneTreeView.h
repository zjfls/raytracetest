#pragma once
#include "afxdockablepane.h"
#include "ViewTree.h"

namespace ZG
{
	class CSceneToolBar : public CMFCToolBar
	{
		virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
		{
			CMFCToolBar::OnUpdateCmdUI((CFrameWnd*)GetOwner(), bDisableIfNoHndler);
		}

		virtual BOOL AllowShowOnList() const { return FALSE; }
	};
	class IWorldObj;
	//
	class CSceneTreeView :
		public CDockablePane
	{
	public:
		CSceneTreeView();
		virtual ~CSceneTreeView();
		virtual void AdjustLayout();
		//
		void OnChangeVisualStyle();
		//
		void InitSceneTreeView();
	private:
		void AddWorldObj(SmartPointer<IWorldObj> pObj, HTREEITEM* pItem);
	protected:
		afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		afx_msg void OnSize(UINT nType, int cx, int cy);
		afx_msg void OnPaint();
		afx_msg void OnSetFocus(CWnd* pOldWnd);
		afx_msg void OnNewFolder();
		afx_msg void OnTreeSelect(NMHDR *, LRESULT *);
		DECLARE_MESSAGE_MAP()
	protected:
		CViewTree m_wndTreeView;
		CSceneToolBar m_wndToolBar;
		CImageList m_SceneTreeViewImg;
		UINT m_nCurrSort;
		friend class CMainFrame;
	};
}


