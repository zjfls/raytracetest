#include "stdafx.h"
#include "RasterRender.h"
#include "IWorld.h"
#include "RenderPath.h"
#include "RenderStage.h"
#include "MaterialResource.h"
//RasterRender::RasterRender()
//	:m_pRenderPath(nullptr)
//{
//}

RasterRender::RasterRender(const RenderPath* pPath)
	: m_pRenderPath(pPath)
{

}


RasterRender::~RasterRender()
{
}

int RasterRender::Render(CameraBase* pCammera, IWorld* pWorld)
{
	std::vector<IRenderable*> vecRenderables = pWorld->GetAllRenderables();
	return Render(vecRenderables);
}

void RasterRender::Render(IRenderable* pRender)
{
	return;
}

int RasterRender::Render(std::vector<IRenderable*>& pRenderableList)
{
	if (m_pRenderPath == nullptr)
	{
		return -1;
	}
	unsigned int nStageCount = m_pRenderPath->GetStageCount();
	for (unsigned int i = 0; i < nStageCount; ++i)
	{
		RenderStage* pStage = m_pRenderPath->GetStage(i);
		std::vector<IRenderable*> vec;
		GetRenderables(pRenderableList,vec, pStage->m_eFillter);
		SetRenderStageState(pStage->m_eFillter);
		for each (IRenderable* pRenderable in vec)
		{
			Render(pRenderable);
		}

	}
	return 0;
}

void RasterRender::GetRenderables(std::vector<IRenderable*>& vecRenderableIn,std::vector<IRenderable*>& vecRenderable, ERENDERTYPEFILTER eFillter)
{
	for each (IRenderable* pRenderable in vecRenderableIn)
	{
		shared_ptr<MaterialResource> pMatRes = pRenderable->m_pMaterial;
		if (pMatRes == nullptr)
		{
			pMatRes = pRenderable->GetDefaultMaterial();
		}
		if (pMatRes->m_eFillter == eFillter)
		{
			vecRenderable.push_back(pRenderable);
		}
	}
}

void RasterRender::SetRenderStageState(ERENDERTYPEFILTER eFillter)
{
	//
}
