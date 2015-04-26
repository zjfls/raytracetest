#include "stdafx.h"
#include "EditorRenderView.h"
#include "RenderManager.h"
#include "RenderSystem.h"
#include "RenderView.h"
EditorRenderView::EditorRenderView()
{
	m_pRenderView = nullptr;
}


EditorRenderView::~EditorRenderView()
{
	
}

void EditorRenderView::Create(unsigned int nWidth, unsigned int nHeight, int windowID)
{
	stRenderViewInfo renderView;
	renderView.m_nWidth = nWidth;
	renderView.m_nHeight = nHeight;
	renderView.m_windowID = windowID;
	m_pRenderView = RenderManager::GetInstance()->GetDefaultRenderSystem()->CreateRenderView(renderView);




}

void EditorRenderView::Resize(unsigned int nWidth, unsigned int nHeight)
{
	m_pRenderView->Resize(nWidth, nHeight);
}
