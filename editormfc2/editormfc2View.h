
// editormfc2View.h : Ceditormfc2View ��Ľӿ�
//

#pragma once


class Ceditormfc2View : public CView
{
protected: // �������л�����
	Ceditormfc2View();
	DECLARE_DYNCREATE(Ceditormfc2View)

// ����
public:
	Ceditormfc2Doc* GetDocument() const;

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
	virtual ~Ceditormfc2View();
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

#ifndef _DEBUG  // editormfc2View.cpp �еĵ��԰汾
inline Ceditormfc2Doc* Ceditormfc2View::GetDocument() const
   { return reinterpret_cast<Ceditormfc2Doc*>(m_pDocument); }
#endif

