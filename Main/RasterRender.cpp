#include "stdafx.h"
#include "RasterRender.h"
#include "IWorld.h"
#include "RenderPath.h"
#include "RenderStage.h"
#include "MaterialResource.h"
#include "IRenderable.h"
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

int RasterRender::Render(CameraBase* pCammera, IWorld* pWorld)
{
	if (RenderBegin() == false)
	{
		return -1;
	}
	std::vector<IRenderable*> vecRenderables = pWorld->GetAllRenderables();
	int nRet = Render(vecRenderables);
	if (RenderEnd() == false)
	{
		return -1;
	}
	return nRet;
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
		//SetRenderStageState(pStage->m_eFillter);

		//pStage->SetStageRenderState(this);
		pStage->Render(this,vec);

	}
	return 0;
}

void RasterRender::GetRenderables(std::vector<IRenderable*>& vecRenderableIn,std::vector<IRenderable*>& vecRenderable, ERENDERTYPEFILTER eFillter)
{
	for each (IRenderable* pRenderable in vecRenderableIn)
	{
		shared_ptr<MaterialResource> pMatRes = pRenderable->m_pSharedMaterial;
		if (pMatRes == nullptr)
		{
			pMatRes = pRenderable->GetDefaultMaterial();
		}
		if (pMatRes->m_eFillter & eFillter != 0)
		{
			vecRenderable.push_back(pRenderable);
		}
	}
}

//void RasterRender::SetRenderStageState(ERENDERTYPEFILTER eFillter)
//{
//	//
//}