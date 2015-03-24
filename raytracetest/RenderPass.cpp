#include "stdafx.h"
#include "RenderPass.h"
#include "RasterMaterial.h"
#include "RasterRender.h"
#include "RenderSystem.h"
#include "HardwareVertexBuffer.h"
#include "HardwareIndexBuffer.h"
#include "HardwareVertexShader.h"
#include "HardwareFragShader.h"
#include "VertexShader.h"
#include "FragShader.h"

RenderPass::RenderPass()
{
}


RenderPass::~RenderPass()
{
}

void RenderPass::Render(RasterRender* pRender, IRenderable* pRenderable, ESTAGESHADERTYPE eShaderType, const RenderStateCollection& mapStates)
{
	shared_ptr<RasterMaterial> pMat = dynamic_pointer_cast<RasterMaterial>(pRenderable->m_pMaterial);

	HardwareIndexBuffer* pIndexBuff = pRender->m_pRenderSystem->GetHardwareIndexBuffer(pRenderable->m_pIndexData);
	HardwareVertexBuffer* pVertexBuff = pRender->m_pRenderSystem->GetHardwareVertexBuffer(pRenderable->m_pVertexData);



	//
	VertexShaderDesc vsdesc;
	HardwareVertexShader* pVertexShader = pRender->m_pRenderSystem->GetHardwareVertexShader(vsdesc);
	FragShaderDesc fsDesc;
	HardwareFragShader* pFragShader = pRender->m_pRenderSystem->GetHardwareFragShader(fsDesc);
	//

	//
	//
	BuildShaderArgs(pRender, pRenderable, eShaderType);
	//
	SetPassStates(pRender,mapStates);
	//
	SetShaderArgs(pRender, pMat);
	//
	pRender->Render(pRenderable);
}

void RenderPass::BuildShaderArgs(RasterRender* pRender, IRenderable* pRenderabl, ESTAGESHADERTYPE eShaderType)
{

}

void RenderPass::SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates)
{

}

void RenderPass::SetShaderArgs(RasterRender* pRender, shared_ptr<RasterMaterial> pMaterial)
{

}
