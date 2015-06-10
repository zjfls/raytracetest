
// EditorMFCView.h : CEditorMFCView 类的接口
//

#pragma once
namespace ZG
{
	class EditorRenderView;
	class CEditorMFCView : public CView
	{
	protected: // 仅从序列化创建
		CEditorMFCView();
		DECLARE_DYNCREATE(CEditorMFCView)

		// 特性
	public:
		CEditorMFCDoc* GetDocument() const;

		// 操作
	public:

		// 重写
	public:
		virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
		virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
		virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
		virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
		virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

		// 实现
	public:
		virtual ~CEditorMFCView();
#ifdef _DEBUG
		virtual void AssertValid() const;
		virtual void Dump(CDumpContext& dc) const;
#endif

	protected:

		// 生成的消息映射函数
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

#ifndef _DEBUG  // EditorMFCView.cpp 中的调试版本
	inline CEditorMFCDoc* CEditorMFCView::GetDocument() const
	{
		return reinterpret_cast<CEditorMFCDoc*>(m_pDocument);
	}
#endif
}


