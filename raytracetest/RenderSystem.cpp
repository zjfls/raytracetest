#include "stdafx.h"
#include "RenderSystem.h"
#include "RasterRender.h"

RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::InitRender(RasterRender* pRender)
{
	pRender->m_pRenderSystem = this;
}

IRender* RenderSystem::GetDefaultRender() const
{
	return m_pDefaultRender;
}

RenderView* RenderSystem::GetDefaultRenderView() const
{
	return m_pDefaultRenderView;
}
