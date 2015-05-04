

// ChildFrm.cpp : CChildFrame 类的实现
//

#include "stdafx.h"
#include "EditorMFC.h"

#include "ChildFrm.h"
#include <iostream>
#include "EditorSceneView.h"
#include "EditorGameView.h"
#include "EditorApplication.h"
#include "Vector2.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEHWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame 构造/析构

CChildFrame::CChildFrame()
{
	
	// TODO:  在此添加成员初始化代码
}

CChildFrame::~CChildFrame()
{

}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{

	//EditorApplication::GetInstance()->AddView((int)m_hWnd, m_pView);
	return m_wndSplitter.Create(this,
		2, 2,			// TODO:  调整行数和列数
		CSize(10, 10),	// TODO:  调整最小窗格大小
		pContext);
	//

	//EditorApplication::GetInstance()->AddView();
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改 CREATESTRUCT cs 来修改窗口类或样式
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame 诊断
void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
	CMDIChildWndEx::OnSize(nType, cx, cy);



}

void CChildFrame::OnClose()
{

	CMDIChildWndEx::OnClose();
}
//BOOL CChildFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	Vector2 v;
//	v.m_fx = pt.x;
//	v.m_fy = pt.y;
//	m_pView->OnMouseWheel(zDelta, v);
//	return FALSE;
//}
//
//void CChildFrame::OnMouseMove(UINT nFlags, CPoint point)
//{
//
//}
//
//void CChildFrame::OnLButtonUp(UINT nFlags, CPoint point)
//{
//	SetCapture();
//}
////
//void CChildFrame::OnMouseHWheel(UINT nFlags, short zDelta, CPoint pt)
//{
//	Vector2 v;
//	v.m_fx = pt.x;
//	v.m_fy = pt.y;
//	m_pView->OnMouseWheel(zDelta, v);
//}

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}






#endif //_DEBUG

// CChildFrame 消息处理程序
