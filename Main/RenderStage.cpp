#include "stdafx.h"
#include "RenderStage.h"
#include "RasterRender.h"
#include "RasterMaterial.h"
#include "IRenderable.h"
#include "RenderPass.h"
#include "RenderStateCollection.h"
RenderStage::RenderStage(string strName, ERENDERTYPEFILTER eFillter, ERENDERSTAGEMETHOD eMethod)
	:m_strName(strName)
	, m_eFillter(eFillter)
	, m_eMethod(eMethod)
{
}


RenderStage::~RenderStage()
{
}

void RenderStage::SetStageRenderState(RasterRender* pRender)
{

}

void RenderStage::Render(RasterRender* pRender,std::vector<IRenderable*>& vecRenderabls)
{
	switch (m_eMethod)
	{
		case ERSM_DEPTHANDAMBIENT:
		break;
		case ERSM_RADIANCEDEPTHOPAQUE:
		{
			RenderDepthAndRadiance(pRender,vecRenderabls);
		}
		break;
		case ERSM_RADIANCEDEPTHTRANSPACENCY:
		{
			RenderDepthAndRadiance(pRender,vecRenderabls);
		}
		break;
		default:
		break;
	}
}

void RenderStage::RenderDepthAndRadiance(RasterRender* pRender,std::vector<IRenderable*>& vecRenderabls)
{
	for each (IRenderable*	pRenderable in vecRenderabls)
	{
		shared_ptr<RasterMaterial> pMaterial = dynamic_pointer_cast<RasterMaterial>(pRenderable->m_pSharedMaterial);
		for each (std::pair<string,RenderPass*> p in pMaterial->m_RenderPassMap)
		{	
			SetRenderStateCollection(pRender, p.second->m_RenderState);
			p.second->Render(pRender, pRenderable,ESTAGESHADERRADIANCE,p.second->m_RenderState);
		}
	}
}

int RenderStage::SetRenderStateCollection(RasterRender* pRender,const RenderStateCollection& mapStates)
{
	switch (m_eMethod)
	{
		case ERSM_DEPTHANDAMBIENT:
		{

		}
		break;
		case ERSM_RADIANCEDEPTHOPAQUE:
		{
			for each (std::pair<RENDERSTATEMASK, void*> p in mapStates.m_mapRenderState)
			{
				if (p.first == ALPHABLEND && *((bool*)p.second) == true)
				{
					return 1;
				}
			}
			for each (std::pair<RENDERSTATEMASK, void*> p in mapStates.m_mapRenderState)
			{

			}
		}
		break;
		case ERSM_RADIANCEDEPTHTRANSPACENCY:
		{

		}
		break;
		default:
		break;
	}
	return 0;
}