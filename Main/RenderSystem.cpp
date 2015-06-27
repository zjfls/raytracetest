#include "stdafx.h"
#include "RenderSystem.h"
#include "RasterRender.h"
#include "VertexShader.h"
#include "FragShader.h"
#include "ShaderGenerator.h"
#include "VertexIndexDataEventProxy.h"
#include "HardwareVertexBuffer.h"
#include "RenderView.h"
#include "HardwareVertexShader.h"
#include "HardwareFragShader.h"
#include "Texture.h"
#include "IWorldObj.h"
#include "IRenderable.h"
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

RasterRender* RenderSystem::GetDefaultRender()
{
	return dynamic_cast<RasterRender*>(m_pDefaultRender.get());
}

RenderView* RenderSystem::GetDefaultRenderView() const
{
	return m_pDefaultRenderView.get();
}

const char* RenderSystem::GetFragShaderCode(FragShaderDesc& fragShaderDesc)
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

const char* RenderSystem::GetVertexShaderCode(VertexShaderDesc& vertexShaderDesc)
{
	if (vertexShaderDesc.m_eVShaderDesc == EVERTEXSHADERORIGIN)
	{
		return vertexShaderDesc.m_pVertexShader->m_pCodeBuffer;
	}
	return nullptr;
}

std::string RenderSystem::GenerateVertexShaderDescString(VertexShaderDesc& vertexShaderDesc)
{
	if (vertexShaderDesc.m_eVShaderDesc == EVERTEXSHADERORIGIN)
	{
		return vertexShaderDesc.m_pVertexShader->GetRefPath();
	}
	char temp[128];
	sprintf_s(temp, "%d%d%d%d%d", int(vertexShaderDesc.m_pVertexShader.get()), vertexShaderDesc.m_bSkinInfo, vertexShaderDesc.m_bSkinNum, vertexShaderDesc.m_bSkinNum, vertexShaderDesc.m_eStageDesc);
	return temp;
}

std::string RenderSystem::GenerateFragShaderDescString(FragShaderDesc& fragShaderDesc)
{
	if (fragShaderDesc.m_eFragShaderDesc == EFRAGSHADERORIGIN)
	{
		return fragShaderDesc.m_pFragShader->GetRefPath();
	}
	char temp[128];
	sprintf_s(temp, "%d%d%d%d%d%d%d%d", int(fragShaderDesc.m_pFragShader.get()), fragShaderDesc.m_eFragShaderDesc, fragShaderDesc.m_eStageDesc, fragShaderDesc.m_nDirLightNum, fragShaderDesc.m_nPointLightNum, fragShaderDesc.m_nSpotLightNum,fragShaderDesc.m_bAmbient,fragShaderDesc.m_eLightType);
	return temp;
}

//IRenderTarget* RenderSystem::GetDefaultRenderTarget() const
//{
//	return m_pDefaultRenderTarget.get();
//}

void RenderSystem::ReleaseRenderTarget(IRenderTarget* pTarget)
{
	std::vector<SmartPointer<IRenderTarget>>::iterator iter = m_vecRenderTarget.begin();
	for (; iter != m_vecRenderTarget.end(); ++iter)
	{
		if (*iter == pTarget)
		{
			*iter == nullptr;
			m_vecRenderTarget.erase(iter);
		}
	}
}

void RenderSystem::OnVertexDataDelete(ZG::VertexDataEventArg& e)
{
	if (m_VertexDataMap.find(e.m_pVertexData) != std::end(m_VertexDataMap))
	{
		//delete m_VertexDataMap[e.m_pVertexData];

		HardwareVertexBuffer *pBuffer = m_VertexDataMap[e.m_pVertexData];
		delete pBuffer;
		m_VertexDataMap.erase(e.m_pVertexData);
	}
	return;
}

void RenderSystem::OnIndexDataDelete(ZG::IndexDataEventArg& e)
{
	if (m_IndexDataMap.find(e.m_pIndexData) != std::end(m_IndexDataMap))
	{
		delete m_IndexDataMap[e.m_pIndexData];
		m_IndexDataMap.erase(e.m_pIndexData);
	}
	return;
}

void ZG::RenderSystem::SetActiveRenderView(RenderView* pView)
{
	m_pActiveView = pView;
}