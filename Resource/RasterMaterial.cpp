#include "stdafx.h"
#include "RasterMaterial.h"
#include "MaterialArg.h"
#include "MaterialPass.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "RenderBaseClass.h"
using namespace ZG;
RasterMaterial::RasterMaterial()

{
}


RasterMaterial::~RasterMaterial()
{
	for each (std::pair<string, SmartPointer<ZG::MaterialPass>> p in m_MaterialPass)
	{
	}
}

//void RasterMaterial::AddPass(string strName, RenderPass* pPass)
//{
//	if (m_RenderPassMap.find(strName) != std::end(m_RenderPassMap))
//	{
//		return;
//	}
//	m_RenderPassMap[strName] = pPass;
//}

void RasterMaterial::AddPass(string strName, ZG::MaterialPass* pPass)
{
	if (m_MaterialPass.find(strName) != std::end(m_MaterialPass))
	{
		return;
	}
	m_MaterialPass[strName] = pPass;
}

SmartPointer<MaterialResource> RasterMaterial::clone()
{
	SmartPointer<RasterMaterial> pMaterial = new RasterMaterial;
	for each (std::pair<string,MaterialArg*> p in m_matArgs)
	{
		pMaterial->m_matArgs[p.first] = p.second->clone();
	}
	//for each (std::pair<string,RenderPass*> p in m_RenderPassMap)
	//{
	//	pMaterial->m_RenderPassMap[p.first] = p.second->clone();
	//}
	for each (std::pair<string,SmartPointer<ZG::MaterialPass>> p in m_MaterialPass)
	{
		pMaterial->m_MaterialPass[p.first] = p.second->clone();
	}
	return pMaterial.SmartPointerCast<MaterialResource>();
}

void ZG::RasterMaterial::SetRenderState(stRenderState& s)
{
	for each (std::pair<string, SmartPointer<ZG::MaterialPass>> p in m_MaterialPass)
	{
		p.second->SetRenderState(s);
	}
}
