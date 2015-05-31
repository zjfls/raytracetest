#include "stdafx.h"
#include "RasterRender.h"
#include "IWorld.h"
#include "RenderPath.h"
#include "RenderStage.h"
#include "MaterialResource.h"
#include "IRenderable.h"
#include "RenderTargetGroup.h"
//RasterRender::RasterRender()
//	:m_pRenderPath(nullptr)
//{
//}

RasterRender::RasterRender(const RenderPath* pPath)
	: m_pRenderPath(pPath)
	, m_pRenderSystem(nullptr)
{

}


RasterRender::~RasterRender()
{
}

int RasterRender::Render(shared_ptr<CameraBase> pCammera, shared_ptr<IWorld> pWorld, IRenderTarget* pTarget)
{
	if (RenderBegin() == false)
	{
		std::cout << "Begin Scene Failed!" << std::endl;
		return -1;
	}

	std::vector<std::shared_ptr<IRenderable>> vecRenderables = pWorld->GetAllRenderables();
	if (m_pRenderPath->m_bGetPerObjLightInfo == true)
	{
		pWorld->GetRenderablesLightInfo(vecRenderables);
	}
	int nRet = Render(vecRenderables,pTarget);
	if (RenderEnd() == false)
	{
		std::cout << "End Scene Failed!" << std::endl;
		return -1;
	}
	return nRet;
}

void RasterRender::Render(IRenderable* pRender)
{
	return;
}

int RasterRender::Render(std::vector<shared_ptr<IRenderable>>& pRenderableList, IRenderTarget* pTarget)
{
	if (m_pRenderPath == nullptr)
	{
		return -1;
	}
	unsigned int nStageCount = m_pRenderPath->GetStageCount();
	for (unsigned int i = 0; i < nStageCount; ++i)
	{
		RenderStage* pStage = m_pRenderPath->GetStage(i);
		//
		pStage->m_RenderTargetGroup.SetRenderTarget(0, pTarget);
		
		//
		std::vector<shared_ptr<IRenderable>> vec;
		GetRenderables(pRenderableList,vec, pStage->m_eFillter);
		//SetRenderStageState(pStage->m_eFillter);

		//pStage->SetStageRenderState(this);
		pStage->Render(this,vec);

	}
	return 0;
}

void RasterRender::GetRenderables(std::vector<std::shared_ptr<IRenderable>>& vecRenderableIn,std::vector<std::shared_ptr<IRenderable>>& vecRenderable, ERENDERTYPEFILTER eFillter)
{
	for each (shared_ptr<IRenderable> pRenderable in vecRenderableIn)
	{
		shared_ptr<MaterialResource> pMatRes = pRenderable->getRenderMaterial();
		if (pMatRes == nullptr)
		{
			pMatRes = pRenderable->GetDefaultMaterial();
			pRenderable->m_pSharedMaterial = pMatRes;
		}
		if (pMatRes != nullptr && pMatRes->m_eFillter == eFillter)
		{
			vecRenderable.push_back(pRenderable);
		}
	}
}

void RasterRender::SetRenderTarget(int nIndex, IRenderTarget* pTarget)
{
	m_TargetGroup.m_Map[nIndex] = pTarget;
}

void RasterRender::SetRenderTargetGroup(RenderTargetGroup* pTargetGroup)
{
	for each (std::pair<int, IRenderTarget*> p in pTargetGroup->m_Map)
	{
		SetRenderTarget(p.first, p.second);
	}
}

void RasterRender::DrawScreen(IRenderTarget* pSource, IRenderTarget* pTarget, shared_ptr<RasterMaterial> pMat)
{
	
}

//void RasterRender::SetRenderStageState(ERENDERTYPEFILTER eFillter)
//{
//	//
//}
