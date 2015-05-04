
// EditorMFCView.cpp : CEditorMFCView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorMFCView::OnFilePrintPreview)
	ON_WM_MOUSEWHEEL()
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CEditorMFCView ����/����

CEditorMFCView::CEditorMFCView()
{
	// TODO:  �ڴ˴���ӹ������
	m_pView = nullptr;

}

CEditorMFCView::~CEditorMFCView()
{
}

BOOL CEditorMFCView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CEditorMFCView ����

void CEditorMFCView::OnDraw(CDC* /*pDC*/)
{
	CEditorMFCDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CEditorMFCView ��ӡ


void CEditorMFCView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEditorMFCView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CEditorMFCView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CEditorMFCView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
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


// CEditorMFCView ���

#ifdef _DEBUG
void CEditorMFCView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorMFCView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorMFCDoc* CEditorMFCView::GetDocument() const // �ǵ��԰汾��������
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


// CEditorMFCView ��Ϣ�������
