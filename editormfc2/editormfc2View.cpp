
// editormfc2View.cpp : Ceditormfc2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "editormfc2.h"
#endif

#include "editormfc2Doc.h"
#include "editormfc2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ceditormfc2View

IMPLEMENT_DYNCREATE(Ceditormfc2View, CView)

BEGIN_MESSAGE_MAP(Ceditormfc2View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &Ceditormfc2View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// Ceditormfc2View ����/����

Ceditormfc2View::Ceditormfc2View()
{
	// TODO:  �ڴ˴���ӹ������

}

Ceditormfc2View::~Ceditormfc2View()
{
}

BOOL Ceditormfc2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// Ceditormfc2View ����

void Ceditormfc2View::OnDraw(CDC* /*pDC*/)
{
	Ceditormfc2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// Ceditormfc2View ��ӡ


void Ceditormfc2View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL Ceditormfc2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void Ceditormfc2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void Ceditormfc2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void Ceditormfc2View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void Ceditormfc2View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// Ceditormfc2View ���

#ifdef _DEBUG
void Ceditormfc2View::AssertValid() const
{
	CView::AssertValid();
}

void Ceditormfc2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Ceditormfc2Doc* Ceditormfc2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Ceditormfc2Doc)));
	return (Ceditormfc2Doc*)m_pDocument;
}
#endif //_DEBUG


// Ceditormfc2View ��Ϣ�������
