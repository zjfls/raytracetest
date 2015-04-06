#include "stdafx.h"
#include "RenderSystem.h"
#include "RasterRender.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "ShaderGenerator.h"
RenderSystem::RenderSystem()
{
}


RenderSystem::~RenderSystem()
{
}

void RenderSystem::InitRender(RasterRender* pRender)
{
	pRender->m_pRenderSystem = this;
}

RasterRender* RenderSystem::GetDefaultRender() const
{
	return m_pDefaultRender;
}

RenderView* RenderSystem::GetDefaultRenderView() const
{
	return m_pDefaultRenderView;
}

const char* RenderSystem::GetFragShaderCode(const FragShaderDesc& fragShaderDesc)
{
	if (fragShaderDesc.m_eFragShaderDesc == EFRAGSHADERORIGIN)
	{
		return fragShaderDesc.m_pFragShader->m_pCodeBuffer;
	}
	else if (fragShaderDesc.m_eFragShaderDesc == EFRAGSHADERSURFACE)
	{
		const char* pCode = ShaderGenerator::GetFragShader(fragShaderDesc);
		return pCode;
	}
	return nullptr;
}

const char* RenderSystem::GetVertexShaderCode(const VertexShaderDesc& vertexShaderDesc)
{
	if (vertexShaderDesc.m_eVShaderDesc == EVERTEXSHADERORIGIN)
	{
		return vertexShaderDesc.m_pVertexShader->m_pCodeBuffer;
	}
	return nullptr;
}

std::string RenderSystem::GenerateVertexShaderDescString(const VertexShaderDesc& vertexShaderDesc)
{
	if (vertexShaderDesc.m_eVShaderDesc == EVERTEXSHADERORIGIN)
	{
		return vertexShaderDesc.m_pVertexShader->GetRefPath();
	}
	char temp[128];
	sprintf_s(temp, "%d%d%d%d%d", int(vertexShaderDesc.m_pVertexShader.get()), vertexShaderDesc.m_bSkinInfo, vertexShaderDesc.m_bSkinNum, vertexShaderDesc.m_bSkinNum, vertexShaderDesc.m_eStageDesc);
	return temp;
}

std::string RenderSystem::GenerateFragShaderDescString(const FragShaderDesc& fragShaderDesc)
{
	if (fragShaderDesc.m_eFragShaderDesc == EFRAGSHADERORIGIN)
	{
		return fragShaderDesc.m_pFragShader->GetRefPath();
	}
	char temp[128];
	sprintf_s(temp, "%d%d%d%d%d%d", int(fragShaderDesc.m_pFragShader.get()), fragShaderDesc.m_eFragShaderDesc, fragShaderDesc.m_eStageDesc, fragShaderDesc.m_nDirLightNum, fragShaderDesc.m_nPointLightNum, fragShaderDesc.m_nSpotLightNum);
	return temp;
}

IRenderTarget* RenderSystem::GetDefaultRenderTarget() const
{
	return m_pDefaultRenderTarget;
}
