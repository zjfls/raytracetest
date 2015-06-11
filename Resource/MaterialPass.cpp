#include "stdafx.h"
#include "MaterialPass.h"
#include "VertexShader.h"
#include "FragShader.h"
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
	//pPass->m_nRefCount = m_nRefCount;
	pPass->m_pFragShader = m_pFragShader;
	pPass->m_pVertexShader = m_pVertexShader;
	pPass->m_vecRenderState = m_vecRenderState;
	return pPass;
}

void ZG::MaterialPass::SetRenderState(stRenderState state)
{
	int nSize = m_vecRenderState.size();
	for (int i = 0; i < nSize; ++i)
	{
		if (m_vecRenderState[i].m_eRenderState == state.m_eRenderState)
		{
			m_vecRenderState[i] = state;
			return;
		}
	}
	m_vecRenderState.push_back(state);
}
