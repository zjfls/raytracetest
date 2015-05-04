
// EditorMFCView.h : CEditorMFCView ��Ľӿ�
//

#pragma once

class EditorRenderView;
class CEditorMFCView : public CView
{
protected: // �������л�����
	CEditorMFCView();
	DECLARE_DYNCREATE(CEditorMFCView)

// ����
public:
	CEditorMFCDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CEditorMFCView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt); 
	DECLARE_MESSAGE_MAP()
public:
	EditorRenderView* m_pView;
};

#ifndef _DEBUG  // EditorMFCView.cpp �еĵ��԰汾
inline CEditorMFCDoc* CEditorMFCView::GetDocument() const
   { return reinterpret_cast<CEditorMFCDoc*>(m_pDocument); }
#endif
