
// TestEditorView.h : CTestEditorView ��Ľӿ�
//

#pragma once


class CTestEditorView : public CView
{
protected: // �������л�����
	CTestEditorView();
	DECLARE_DYNCREATE(CTestEditorView)

// ����
public:
	CTestEditorDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CTestEditorView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestEditorView.cpp �еĵ��԰汾
inline CTestEditorDoc* CTestEditorView::GetDocument() const
   { return reinterpret_cast<CTestEditorDoc*>(m_pDocument); }
#endif

