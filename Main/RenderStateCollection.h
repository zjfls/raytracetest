#pragma once
#include "RenderEnum.h"
namespace ZG
{
	class RenderStateCollection
	{
	public:
		RenderStateCollection();
		virtual ~RenderStateCollection();



		std::unordered_map<RENDERSTATEMASK, void*> m_mapRenderState;
	};

}