
// TestEditorView.cpp : CTestEditorView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "TestEditor.h"
#endif

#include "TestEditorDoc.h"
#include "TestEditorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestEditorView

IMPLEMENT_DYNCREATE(CTestEditorView, CView)

BEGIN_MESSAGE_MAP(CTestEditorView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTestEditorView ����/����

CTestEditorView::CTestEditorView()
{
	// TODO:  �ڴ˴���ӹ������

}

CTestEditorView::~CTestEditorView()
{
}

BOOL CTestEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CTestEditorView ����

void CTestEditorView::OnDraw(CDC* /*pDC*/)
{
	CTestEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}

void CTestEditorView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTestEditorView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTestEditorView ���

#ifdef _DEBUG
void CTestEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CTestEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestEditorDoc* CTestEditorView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestEditorDoc)));
	return (CTestEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestEditorView ��Ϣ�������
