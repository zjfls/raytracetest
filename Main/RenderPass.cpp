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
#include "IRenderable.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "Color.h"
#include "TextureSampler.h"
#include "IWorldObj.h"
#include "Transform.h"
#include "RasterRender.h"
#include "CameraBase.h"
#include "HardwareShader.h"
RenderPass::RenderPass()
{
}


RenderPass::~RenderPass()
{
}

void RenderPass::Render(RasterRender* pRender, IRenderable* pRenderable, ESTAGESHADERTYPE eStageShaderType, const RenderStateCollection& mapStates)
{
	shared_ptr<RasterMaterial> pMat = dynamic_pointer_cast<RasterMaterial>(pRenderable->m_pSharedMaterial);

	HardwareIndexBuffer* pIndexBuff = pRender->m_pRenderSystem->GetHardwareIndexBuffer(pRenderable->m_pIndexData);
	HardwareVertexBuffer* pVertexBuff = pRender->m_pRenderSystem->GetHardwareVertexBuffer(pRenderable->m_pVertexData);



	//
	VertexShaderDesc vsdesc;
	vsdesc.m_pVertexShader = m_pVertexShader;
	vsdesc.m_eStageDesc = eStageShaderType;
	vsdesc.m_eVShaderDesc = m_eVertexShaderType;
	HardwareVertexShader* pVertexShader = pRender->m_pRenderSystem->GetHardwareVertexShader(vsdesc);
	if (nullptr == pVertexShader)
	{
		std::cout << "can not get hardware shader:" << vsdesc.m_pVertexShader->GetRefPath() << std::endl;
		return;
	}
	FragShaderDesc fsDesc;
	fsDesc.m_eStageDesc = eStageShaderType;
	fsDesc.m_eFragShaderDesc = m_eFragShaderType;
	fsDesc.m_pFragShader = m_pFragShader;
	HardwareFragShader* pFragShader = pRender->m_pRenderSystem->GetHardwareFragShader(fsDesc);
	if (nullptr == pFragShader)
	{
		std::cout << "can not get hardware shader:" << fsDesc.m_pFragShader->GetRefPath() << std::endl;
		return;
	}
	//
	pRender->SetVertexShader(pVertexShader);
	pRender->SetFragShader(pFragShader);
	
	//
	BuildShaderArgs(pRender, pRenderable,pMat, eStageShaderType,pVertexShader,pFragShader);
	//
	SetPassStates(pRender, mapStates);
	//
	SetShaderArgs(pRender,pVertexShader, pFragShader);



	pRender->Render(pIndexBuff, pVertexBuff);
	

}

void RenderPass::BuildShaderArgs(RasterRender* pRender, IRenderable* pRenderable, shared_ptr<RasterMaterial> pMaterial, ESTAGESHADERTYPE eShaderType, HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader)
{
	m_VertexShaderArgs.clear();
	m_FragShaderArgs.clear();

	//
	std::unordered_map<string, ShaderConstantInfo>& vertexShaderParam = pVertexShader->GetContants();
	std::unordered_map<string, ShaderConstantInfo>& fragShaderParam = pFragShader->GetContants();

	SetBuiltInMatrixArg(pRender, pRenderable,m_VertexShaderArgs, vertexShaderParam);
	SetBuiltInMatrixArg(pRender, pRenderable,m_FragShaderArgs, fragShaderParam);

	//
	for each (std::pair<string, MaterialArg*> p in pMaterial->m_matArgs)
	{
		if (vertexShaderParam.find(p.first) != std::end(vertexShaderParam))
		{
			m_VertexShaderArgs[p.first] = p.second;
		}
		if (fragShaderParam.find(p.first) != std::end(fragShaderParam))
		{
			m_FragShaderArgs[p.first] = p.second;
		}
	}
	//

}

void RenderPass::SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates)
{

}
void RenderPass::SetShaderArgs(RasterRender* pRender,HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader)
{
	//TextureSampler* pSampler = p.second->GetData<TextureSampler>();
	//HardwareTexture* pHardwareTex = pRender->m_pRenderSystem->GetHardwareTexture(pSampler->m_pTexture);
	//SetTexture(pSampler->m_byRegisterIndex, pHardwareTex);
	for each (std::pair<string, MaterialArg*> p in m_VertexShaderArgs)
	{
		pVertexShader->SetShaderArg(pRender,p.first, p.second);
	}

	
	for each (std::pair<string, MaterialArg*> p in m_FragShaderArgs)
	{
		pFragShader->SetShaderArg(pRender, p.first, p.second);
	}
}

void RenderPass::SetBuiltInMatrixArg(RasterRender* pRender, IRenderable* pRenderable, std::unordered_map<string, MaterialArg*>& argToBuild, std::unordered_map<string, ShaderConstantInfo>& argIn)
{


	Matrix44 matWorld = pRenderable->m_pOwnerObj->m_pTransform->GetWorldMatrix();
	Matrix44 matView = pRender->m_pCurrentRenderCamera->GetViewMatrix();
	Matrix44 matProj = pRender->m_pCurrentRenderCamera->GetProjMatrix();

	for each (std::pair<string, ShaderConstantInfo> p in argIn)
	{

		//  MATRIX_WORLD
		//	MATRIX_VIEW
		//	MATRIX_PROJ
		//	MATRIX_WV
		//	MATRIX_WVP
		//	MATRIX_INVERSEWV
		TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
		if (p.first == "MATRIX_WORLD")
		{
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matWorld;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_VIEW")
		{
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matView;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_PROJ")
		{
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matProj;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_WV")
		{
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matWorld * matView;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_VP")
		{
			arg.m_Data = matView * matProj;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_WVP")
		{
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matWorld * matView * matProj;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_INVERSEWV")
		{
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			Matrix44 matWV = matWorld * matView;
			arg.m_Data = Matrix44::QuikInverse(matWV);
			argToBuild[p.first] = &arg;
		}
	}
}
