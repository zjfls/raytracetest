#include "stdafx.h"
#include "RenderSystem.h"
#include "RasterRender.h"
#include "VertexShader.h"
#include "FragShader.h"
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
	return vertexShaderDesc.m_pVertexShader->GetRefPath();
}

std::string RenderSystem::GenerateFragShaderDescString(const FragShaderDesc& fragShaderDesc)
{
	return fragShaderDesc.m_pFragShader->GetRefPath();
}
