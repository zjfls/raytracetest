#include "stdafx.h"
#include "RenderStage.h"
#include "RasterRender.h"
#include "RasterMaterial.h"

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
		shared_ptr<RasterMaterial> pMaterial = dynamic_pointer_cast<RasterMaterial>(pRenderable->m_pMaterial);
		for each (std::pair<string,RenderPass*> p in pMaterial->m_RenderPassMap)
		{	
			SetRenderStateCollection(pRender, p.second->m_RenderState);
			p.second->Render(pRender, pRenderable,ESTAGESHADERRADIANCE);
		}
	}
}

int RenderStage::SetRenderStateCollection(RasterRender* pRender,const RenderStateCollection& mapStates)
{
	return 0;
}
