#include "stdafx.h"
#include "MaterialPass.h"
using namespace ZG;

ZG::MaterialPass::MaterialPass()
{

}

ZG::MaterialPass::~MaterialPass()
{

}

MaterialPass* ZG::MaterialPass::clone()
{
	MaterialPass* pPass = new MaterialPass;
	pPass->m_eFragShaderType = m_eFragShaderType;
	pPass->m_eVertexShaderType = m_eVertexShaderType;
	pPass->m_nRefCount = m_nRefCount;
	pPass->m_pFragShader = m_pFragShader;
	pPass->m_pVertexShader = m_pVertexShader;
	pPass->m_vecRenderState = m_vecRenderState;
	return pPass;
}
