#include "stdafx.h"
#include "RenderPath.h"
#include "RenderStage.h"
#include "IRenderable.h"
#include "RenderManager.h"
#include "RenderSystem.h"

RenderPath::RenderPath(string strName)
	:m_strName(strName)
	, m_bGetPerObjLightInfo(true)
{
}


RenderPath::~RenderPath()
{
}

unsigned int RenderPath::GetStageCount() const
{
	return m_vecStages.size();
}

RenderStage* RenderPath::GetStage(unsigned int i) const
{
	if (i >= m_vecStages.size())
	{
		return nullptr;
	}
	return m_vecStages[i];
}

void RenderPath::AddStage(RenderStage* stage)
{
	m_vecStages.push_back(stage);
}


void RenderPath::InitTargetBuffer()
{
	if (m_strName == "Forward")
	{
		IRenderTarget* pTarget = RenderManager::GetInstance()->GetDefaultRenderSystem()->GetDefaultRenderTarget();
		m_RenderTargetGroup.SetRenderTarget(0, pTarget);
		for each (RenderStage* pState in m_vecStages)
		{
			pState->m_RenderTargetGroup = m_RenderTargetGroup;
		}
	}
	else if (m_strName == "Deferred")
	{

	}
}
