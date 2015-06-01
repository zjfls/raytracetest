#include "stdafx.h"
#include "RenderStage.h"
#include "RasterRender.h"
#include "RasterMaterial.h"
#include "IRenderable.h"
#include "RenderPass.h"
#include "RenderStateCollection.h"
#include "EnviromentSetting.h"
#include "MaterialPass.h"
using namespace ZG;
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
	switch (m_eMethod)
	{
		case ERSM_DEPTHANDAMBIENT:
		break;
		case ERSM_RADIANCEDEPTHOPAQUE:
		{
			pRender->SetZTestEnable(true);
			pRender->SetZFunc(RENDERCMP_LESSEQUAL);
			pRender->SetZWriteEnable(true);
			pRender->SetBlendEnable(false);
			pRender->SetAlphaFunc(RENDERCMP_GREATER);
		}
		break;
		case ERSM_RADIANCEDEPTHTRANSPACENCY:
		{
			//RenderDepthAndRadiance(pRender, vecRenderabls);
		}
		break;
		default:
		break;
	}
}

void RenderStage::Render(RasterRender* pRender,std::vector<shared_ptr<IRenderable>>& vecRenderabls)
{
	pRender->SetRenderTargetGroup(&m_RenderTargetGroup);
	SetStageRenderState(pRender);
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

void RenderStage::RenderDepthAndRadiance(RasterRender* pRender,std::vector<std::shared_ptr<IRenderable>>& vecRenderabls)
{

	bool bAllLight = EnviromentSetting::GetInstance()->GetIntSetting("FOWARDLIGHTONEPASS");
	for each (shared_ptr<IRenderable>	pRenderable in vecRenderabls)
	{
		shared_ptr<RasterMaterial> pMaterial = dynamic_pointer_cast<RasterMaterial>(pRenderable->getRenderMaterial());
		for each (std::pair<string,SmartPointer<MaterialPass>> p in pMaterial->m_MaterialPass)
		{	
			RenderPass rPass(p.second.get());
			SetRenderStateCollection(pRender, rPass.m_RenderState);
			if (bAllLight)
			{
				rPass.Render(pRender, pRenderable, ESTAGESHADERRADIANCEALLLIGHTING, rPass.m_RenderState);
			}
			else
			{
				rPass.Render(pRender, pRenderable, ESTAGESHADERRADIANCEONLIGHTING, rPass.m_RenderState);
			}
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
