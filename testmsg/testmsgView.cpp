
// testmsgView.cpp : CtestmsgView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "testmsg.h"
#endif

#include "testmsgDoc.h"
#include "testmsgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CtestmsgView

IMPLEMENT_DYNCREATE(CtestmsgView, CView)

BEGIN_MESSAGE_MAP(CtestmsgView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CtestmsgView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CtestmsgView ����/����

CtestmsgView::CtestmsgView()
{
	// TODO:  �ڴ˴���ӹ������

}

CtestmsgView::~CtestmsgView()
{
}

BOOL CtestmsgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CtestmsgView ����

void CtestmsgView::OnDraw(CDC* /*pDC*/)
{
	CtestmsgDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CtestmsgView ��ӡ


void CtestmsgView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CtestmsgView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CtestmsgView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CtestmsgView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CtestmsgView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CtestmsgView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CtestmsgView ���

#ifdef _DEBUG
void CtestmsgView::AssertValid() const
{
	CView::AssertValid();
}

void CtestmsgView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CtestmsgDoc* CtestmsgView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CtestmsgDoc)));
	return (CtestmsgDoc*)m_pDocument;
}
#endif //_DEBUG


// CtestmsgView ��Ϣ�������
