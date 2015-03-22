#include "stdafx.h"
#include "RenderPath.h"
#include "RenderStage.h"

RenderPath::RenderPath(string strName)
	:m_strName(strName)
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
