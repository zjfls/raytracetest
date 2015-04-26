nullptr_t
new_handler

// ChildFrm.cpp : CChildFrame ���ʵ��
//

#include "stdafx.h"
#include "EditorMFC.h"

#include "ChildFrm.h"
#include <iostream>
#include "EditorRenderView.h"
#include "EditorApplication.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWndEx)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWndEx)
	ON_WM_SIZE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CChildFrame ����/����

CChildFrame::CChildFrame()
{
	m_pView = nullptr;
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CChildFrame::~CChildFrame()
{

}

BOOL CChildFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/, CCreateContext* pContext)
{

	//EditorApplication::GetInstance()->AddView((int)m_hWnd, m_pView);
	return m_wndSplitter.Create(this,
		2, 2,			// TODO:  ��������������
		CSize(10, 10),	// TODO:  ������С�����С
		pContext);
	//

	//EditorApplication::GetInstance()->AddView();
}

BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ��������ʽ
	if( !CMDIChildWndEx::PreCreateWindow(cs) )
		return FALSE;

	return TRUE;
}

// CChildFrame ���

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWndEx::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWndEx::Dump(dc);
}

void CChildFrame::OnSize(UINT nType, int cx, int cy)
{
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
		m_pView = new EditorRenderView();
		m_pView->Create(10, 10, (int)m_hWnd);
		EditorApplication::GetInstance()->AddView((int)m_hWnd, m_pView);
	}


}

void CChildFrame::OnClose()
{
	delete m_pView;
	m_pView = nullptr;
	EditorApplication::GetInstance()->RemoveView((int)m_hWnd);
	CMDIChildWndEx::OnClose();

	
}

#endif //_DEBUG

// CChildFrame ��Ϣ�������
