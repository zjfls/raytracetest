
// EditorMFCView.cpp : CEditorMFCView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "EditorMFC.h"
#endif

#include "EditorMFCDoc.h"
#include "EditorMFCView.h"
#include <iostream>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "ChildFrm.h"
#include "EditorSceneView.h"
#include "EditorGameView.h"
#include "EditorRenderView.h"
#include "EditorApplication.h"
#include "Vector2.h"
// CEditorMFCView

IMPLEMENT_DYNCREATE(CEditorMFCView, CView)

BEGIN_MESSAGE_MAP(CEditorMFCView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorMFCView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CEditorMFCView 构造/析构

CEditorMFCView::CEditorMFCView()
{
	// TODO:  在此处添加构造代码
	m_pView = nullptr;

}

CEditorMFCView::~CEditorMFCView()
{
}

BOOL CEditorMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CEditorMFCView 绘制

void CEditorMFCView::OnDraw(CDC* /*pDC*/)
{
	CEditorMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
}


// CEditorMFCView 打印


void CEditorMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEditorMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CEditorMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CEditorMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CEditorMFCView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CEditorMFCView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CEditorMFCView 诊断

#ifdef _DEBUG
void CEditorMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorMFCDoc* CEditorMFCView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorMFCDoc)));
	return (CEditorMFCDoc*)m_pDocument;
}

BOOL CEditorMFCView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	//
	CChildFrame* pFrame = (CChildFrame*)GetParentFrame();
	//pFrame->m_bPseudoInactive
	//
	Vector2 v;
	v.m_fx = pt.x;
	v.m_fy = pt.y;
	m_pView->OnMouseWheel(zDelta, v);
	return true;
}

void CEditorMFCView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	std::cout << "view resize:" << cx << " " << cy << std::endl;
	//
	if (cx == 0 && cy == 0)
	{
		return;
	}
	std::cout << "window resize x:" << cx << "y:" << cy << std::endl;
	if (m_pView != nullptr)
	{
		m_pView->Resize(cx, cy);
	}
	else
	{
		m_pView = new EditorSceneView();
		m_pView->Create(10, 10, (int)m_hWnd);
		EditorApplication::GetInstance()->AddView((int)m_hWnd, m_pView);
	}
}

void CEditorMFCView::OnClose()
{
	delete m_pView;
	m_pView = nullptr;
	EditorApplication::GetInstance()->RemoveView((int)m_hWnd);
}

#endif //_DEBUG


// CEditorMFCView 消息处理程序
