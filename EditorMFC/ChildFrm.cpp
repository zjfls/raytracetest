

// ChildFrm.cpp : CChildFrame ���ʵ��
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

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{

}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{

	//EditorApplication::GetInstance()->AddView((int)m_hWnd, m_pView);
	return m_wndSplitter.Create(this,
		2, 2,			// TODO:  ��������������
		CSize(10, 10),	// TODO:  ������С�����С
		pContext);
	//

	//EditorApplication::GetInstance()->AddView();
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���
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

// CChildFrame ��Ϣ�������
