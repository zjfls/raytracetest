#include "stdafx.h"
#include "RenderPathManager.h"
#include "RenderPath.h"
#include "RenderStage.h"
shared_ptr<RenderPathManager> Singleton<RenderPathManager>::_instance = nullptr;

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
	RenderPath* pForwardPath = new RenderPath("Forward");
	RenderStage* pOpaqueStage = new RenderStage("Opaque", EFILLTEROPAUE, ERSM_RADIANCEDEPTHOPAQUE);
	//pOpaqueStage->m_eFillter = EFILLTEROPAUE;
	pForwardPath->AddStage(pOpaqueStage);
	
	RenderStage* pTransStage = new RenderStage("Transparency", EFILLTERTRANSPARENCY, ERSM_RADIANCEDEPTHTRANSPACENCY);
	//pTransStage->m_eFillter = EFILLTERTRANSPARENCY;
	//pTransStage->m_eFillter = EFILLTERTRANSPARENCY;
	pForwardPath->AddStage(pTransStage);

	AddRenderPath("Forward", pForwardPath);

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


