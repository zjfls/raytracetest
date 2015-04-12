#include "stdafx.h"
#include "RenderTargetGroup.h"


RenderTargetGroup::RenderTargetGroup()
{
}


RenderTargetGroup::~RenderTargetGroup()
{
}

void RenderTargetGroup::SetRenderTarget(int nIndex, IRenderTarget* pTarget)
{
	m_Map[nIndex] = pTarget;
}
