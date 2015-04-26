
// EditorTestView.cpp : CEditorTestView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditorTestView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CEditorTestView ����/����

CEditorTestView::CEditorTestView()
{
	// TODO:  �ڴ˴���ӹ������

}

CEditorTestView::~CEditorTestView()
{
}

BOOL CEditorTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CEditorTestView ����

void CEditorTestView::OnDraw(CDC* /*pDC*/)
{
	CEditorTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CEditorTestView ��ӡ


void CEditorTestView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CEditorTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CEditorTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CEditorTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
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


// CEditorTestView ���

#ifdef _DEBUG
void CEditorTestView::AssertValid() const
{
	CView::AssertValid();
}

void CEditorTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEditorTestDoc* CEditorTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEditorTestDoc)));
	return (CEditorTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CEditorTestView ��Ϣ�������
