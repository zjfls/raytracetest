#pragma once
#include "RenderEnum.h"
class RenderStateCollection
{
public:
	RenderStateCollection();
	virtual ~RenderStateCollection();



	std::unordered_map<RENDERSTATEMASK, void*> m_mapRenderState;
};

