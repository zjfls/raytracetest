#include "stdafx.h"
#include "RenderPathManager.h"
#include "RenderPath.h"
#include "RenderStage.h"
RenderPathManager* Singleton<RenderPathManager>::_instance = nullptr;

RenderPathManager::RenderPathManager()
{
	std::map<string, RenderPath*>::iterator iter = m_mapRenderPath.begin();
	while (iter != m_mapRenderPath.end())
	{
		delete iter->second;
		iter->second = nullptr;
		iter = m_mapRenderPath.erase(iter);
	}
}


RenderPathManager::~RenderPathManager()
{
}

bool RenderPathManager::Init()
{
	//forward path
	RenderPath* pForwardPath = new RenderPath("Foward");
	RenderStage* pOpaqueStage = new RenderStage("Opaque", EFILLTEROPAUE);
	//pOpaqueStage->m_eFillter = EFILLTEROPAUE;
	pForwardPath->AddStage(pOpaqueStage);
	
	RenderStage* pTransStage = new RenderStage("Transparency", EFILLTERTRANSPARENCY);
	//pTransStage->m_eFillter = EFILLTERTRANSPARENCY;
	//pTransStage->m_eFillter = EFILLTERTRANSPARENCY;
	pForwardPath->AddStage(pTransStage);

	AddRenderPath("Foward", pForwardPath);

	//
	return true;

}

RenderPath* RenderPathManager::GetRenderPath(string strName)
{
	if (m_mapRenderPath.find(strName) != std::end(m_mapRenderPath))
	{
		return m_mapRenderPath[strName];
	}
	return nullptr;
}

void RenderPathManager::AddRenderPath(string strName, RenderPath* pPath)
{
	if (m_mapRenderPath.find(strName) != std::end(m_mapRenderPath))
	{
		return;
	}
	m_mapRenderPath[strName] = pPath;
}
