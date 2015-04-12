
// TestEditorView.cpp : CTestEditorView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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

// CTestEditorView 构造/析构

CTestEditorView::CTestEditorView()
{
	// TODO:  在此处添加构造代码

}

CTestEditorView::~CTestEditorView()
{
}

BOOL CTestEditorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CTestEditorView 绘制

void CTestEditorView::OnDraw(CDC* /*pDC*/)
{
	CTestEditorDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
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


// CTestEditorView 诊断

#ifdef _DEBUG
void CTestEditorView::AssertValid() const
{
	CView::AssertValid();
}

void CTestEditorView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestEditorDoc* CTestEditorView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestEditorDoc)));
	return (CTestEditorDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestEditorView 消息处理程序
