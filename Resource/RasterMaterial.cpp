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

shared_ptr<MaterialResource> RasterMaterial::clone()
{
	shared_ptr<RasterMaterial> pMaterial(new RasterMaterial);
	for each (std::pair<string,MaterialArg*> p in m_matArgs)
	{
		pMaterial->m_matArgs[p.first] = p.second;
	}
	for each (std::pair<string,RenderPass*> p in m_RenderPassMap)
	{
		pMaterial->m_RenderPassMap[p.first] = p.second;
	}
	return pMaterial;
}
