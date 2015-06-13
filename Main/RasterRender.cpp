#include "stdafx.h"
#include "RasterRender.h"
#include "IWorld.h"
#include "RenderPath.h"
#include "RenderStage.h"
#include "MaterialResource.h"
#include "IRenderable.h"
#include "RenderTargetGroup.h"
#include "EnviromentSetting.h"
#include "RenderSystem.h"
#include "CameraBase.h"
#include "RenderView.h"
#include "RasterMaterial.h"
#include "Culler.h"
//RasterRender::RasterRender
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

int RasterRender::Render(SmartPointer<CameraBase> pCamera, SmartPointer<IWorld> pWorld, IRenderTarget* pTarget)
{
	SetRenderTarget(0, pTarget);
	SetDepthBuffer(pTarget->m_DepthBuffer.get());
	ClearTarget(pCamera->m_bClearColor, pCamera->m_clrColr, pCamera->m_bClearDepth, pCamera->m_fDepth);
	
	if (RenderBegin() == false)
	{
		std::cout << "Begin Scene Failed!" << std::endl;
		return -1;
	}
	if (m_pCurrentRenderCamera == nullptr)
	{
		m_pCurrentRenderCamera = pCamera;
	}
	std::vector<SmartPointer<IRenderable>> vecRenderables = pWorld->GetAllRenderables();
	if (m_pRenderPath->m_bGetPerObjLightInfo == true)
	{
		pWorld->GetRenderablesLightInfo(vecRenderables);
	}
	//
	Culler culler;
	std::vector<SmartPointer<IRenderable>> vecCulled;
	culler.cull(vecRenderables, vecCulled, pCamera);
	//
	//std::cout << "int nRet = Render(vecCulled, pTarget);" << std::endl;
	int nRet = Render(vecCulled, pTarget);
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

int RasterRender::Render(std::vector<SmartPointer<IRenderable>>& pRenderableList, IRenderTarget* pTarget)
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
		std::vector<SmartPointer<IRenderable>> vec;
		GetRenderables(pRenderableList,vec, pStage->m_eFillter);
		//SetRenderStageState(pStage->m_eFillter);
		//std::cout << "pStage->Render(this,vec);" << std::endl;
		//pStage->SetStageRenderState(this);
		pStage->Render(this,vec);
		//std::cout << "pStage->Render(this,vec); end" << std::endl;

	}
	return 0;
}

void RasterRender::GetRenderables(std::vector<SmartPointer<IRenderable>>& vecRenderableIn,std::vector<SmartPointer<IRenderable>>& vecRenderable, ERENDERTYPEFILTER eFillter)
{
	for each (SmartPointer<IRenderable> pRenderable in vecRenderableIn)
	{
		SmartPointer<MaterialResource> pMatRes = pRenderable->getRenderMaterial();
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

void RasterRender::DrawScreen(IRenderTarget* pSource, IRenderTarget* pTarget, SmartPointer<RasterMaterial> pMat)
{
	
}

void RasterRender::RenderCamera(CameraRenderEvent& rEvent)
{

	SmartPointer<CameraBase> pCamera = rEvent.m_pTargetCamera;
	if (pCamera == nullptr || pCamera->m_pTarget == nullptr)
	{
		return;
	}

	//std::cout << "fsdffffffffffffffffffffffffffffffffff"<<(int)pCamera.get() << std::endl;
	m_pCurrentRenderCamera = pCamera;
	IRenderTarget* pTarget = nullptr;
	RenderView* pView = dynamic_cast<RenderView*>(rEvent.m_pTargetCamera->m_pTarget.get());
	if (pView != nullptr)
	{
		ClearTarget(pCamera->m_bClearColor, pCamera->m_clrColr, pCamera->m_bClearDepth, pCamera->m_fDepth);
		if (EnviromentSetting::GetInstance()->GetIntSetting("HDR") == true && pCamera->m_bHDR)
		{
			//SetRenderTarget(0, pView->m_pHDRTarget.get());
			pTarget = pView->m_pHDRTarget.get();
		}
		else
		{
			//SetRenderTarget(0, pView);
			pTarget = pView;
		}
	}
	else
	{
		//SetRenderTarget(0, rEvent.m_pTargetCamera->m_pTarget.get());
		pTarget = rEvent.m_pTargetCamera->m_pTarget.get();
	}


	//IRenderTarget* pTarget = nullptr;
	//if (EnviromentSetting::GetInstance()->GetIntSetting("HDR") == true)
	//{
	//	pTarget = m_pRenderSystem->GetDef;
	//}
	//else
	//{
	//	pTarget = pCamera->m_pTarget.get();
	//}
	
	SetDepthBuffer(rEvent.m_pTargetCamera->m_pTarget->m_DepthBuffer.get());
	
	//
	Render(pCamera, pCamera->m_pWorld, pTarget);

	SmartPointer<RasterMaterial> mat = ResourceManager<MaterialResource>::GetInstance()->GetResource("./data/material/builtin/quad.smat.xml").SmartPointerCast<RasterMaterial>();

	if (pView != nullptr)
	{
		if (EnviromentSetting::GetInstance()->GetIntSetting("HDR") == true && pCamera->m_bHDR)
		{
			DrawScreen(pTarget, pView, mat);
		}
	}

}
