
// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "testmsg.h"

#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_MOUSEWHEEL()
	ON_WM_NCLBUTTONDOWN()
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
	return m_wndSplitter.Create(this,
		2, 2,			// TODO:  ��������������
		CSize(10, 10),	// TODO:  ������С�����С
		pContext);
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���
BOOL CChildFrame::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{

	return FALSE;
}
#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}

void CChildFrame::OnNcLButtonDown(UINT nHitTest, CPoint point)
{

}

#endif //_DEBUG

// CChildFrame ��Ϣ�������
