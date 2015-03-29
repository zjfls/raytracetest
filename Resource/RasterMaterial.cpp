#include "stdafx.h"
#include "RasterMaterial.h"


RasterMaterial::RasterMaterial()

{
}


RasterMaterial::~RasterMaterial()
{
}

void RasterMaterial::AddPass(string strName, RenderPass* pPass)
{
	if (m_RenderPassMap.find(strName) != std::end(m_RenderPassMap))
	{
		return;
	}
	m_RenderPassMap[strName] = pPass;
}
