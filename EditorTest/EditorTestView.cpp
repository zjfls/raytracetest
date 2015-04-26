
// EditorTestView.cpp : CEditorTestView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "EditorTest.h"
#endif

#include "EditorTestDoc.h"
#include "EditorTestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEditorTestView

IMPLEMENT_DYNCREATE(CEditorTestView, CView)

BEGIN_MESSAGE_MAP(CEditorTestView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEditorTestView 构造/析构

CEditorTestView::CEditorTestView()
{
	// TODO:  在此处添加构造代码

}

CEditorTestView::~CEditorTestView()
{
}

BOOL CEditorTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEditorTestView 绘制

void CEditorTestView::OnDraw(CDC* /*pDC*/)
{
	CEditorTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CEditorTestView 打印


void CEditorTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEditorTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEditorTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CEditorTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CEditorTestView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEditorTestView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEditorTestView 诊断

#ifdef _DEBUG
void CEditorTestView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorTestDoc* CEditorTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorTestDoc)));
	return (CEditorTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditorTestView 消息处理程序
