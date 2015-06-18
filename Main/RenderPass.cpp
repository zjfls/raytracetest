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
#include "DirectionalLight.h"
#include "PointLight.h"
#include "EnviromentSetting.h"
#include "VertexData.h"
//#include "GlobalRenderConfig.h"

RenderPass::RenderPass()
	//:m_MaterialPass(nullptr)
{
}

RenderPass::RenderPass(MaterialPass* pPass)
{
	//m_MaterialPass = pPass;
	m_vecRenderState = pPass->m_vecRenderState;
	m_pFragShader = pPass->m_pFragShader;
	m_pVertexShader = pPass->m_pVertexShader;
	m_eVertexShaderType = pPass->m_eVertexShaderType;
	m_eFragShaderType = pPass->m_eFragShaderType;
	m_vecRenderState = pPass->m_vecRenderState;
}


RenderPass::~RenderPass()
{
	for each (std::pair<std::string, MaterialArg*> p in m_ArgLib)
	{
		delete p.second;
	}
	//for each (std::pair<std::string, MaterialArg*> p in m_FragShaderArgs)
	//{
	//	delete p.second;
	//}
}

void RenderPass::Render(RasterRender* pRender, SmartPointer<IRenderable> pRenderable, ESTAGESHADERTYPE eStageShaderType, const RenderStateCollection& mapStates)
{	

	//std::cout << "pRender->SetAlphaTest(true);" << std::endl;
	pRender->SetAlphaTest(true);
	pRender->SetAlphaTestFactor(128);
	pRender->SetAlphaFunc(RENDERCMP_GREATER);
	//
	SmartPointer<RasterMaterial> pMat = pRenderable->getRenderMaterial().SmartPointerCast<RasterMaterial>();

	HardwareIndexBuffer* pIndexBuff = pRender->m_pRenderSystem->GetHardwareIndexBuffer(pRenderable->m_pIndexData.get());
	HardwareVertexBuffer* pVertexBuff = pRender->m_pRenderSystem->GetHardwareVertexBuffer(pRenderable->m_pVertexData.get());



	//
	VertexShaderDesc vsdesc;
	vsdesc.m_pVertexShader = m_pVertexShader;
	vsdesc.m_eStageDesc = eStageShaderType;
	vsdesc.m_eVShaderDesc = m_eVertexShaderType;

	FragShaderDesc fsDesc;
	fsDesc.m_eStageDesc = eStageShaderType;
	fsDesc.m_eFragShaderDesc = m_eFragShaderType;
	fsDesc.m_pFragShader = m_pFragShader;

	//
	//HardwareVertexShader* pVertexShader;
	//HardwareFragShader* pFragShader;
	if (eStageShaderType == ESTAGESHADERRADIANCEALLLIGHTING || fsDesc.m_eFragShaderDesc == EFRAGSHADERORIGIN)
	{
		//std::cout << "eStageShaderType == ESTAGESHADERRADIANCEALLLIGHTING || fsDesc.m_eFragShaderDesc == EFRAGSHADERORIGIN" << std::endl;
		HardwareVertexShader* pVertexShader = pRender->m_pRenderSystem->GetHardwareVertexShader(vsdesc);
		if (nullptr == pVertexShader)
		{
			//std::cout << "can not get hardware shader:" << vsdesc.m_pVertexShader->GetRefPath() << std::endl;
			return;
		}
		HardwareFragShader* pFragShader = pRender->m_pRenderSystem->GetHardwareFragShader(fsDesc);
		if (nullptr == pFragShader)
		{
			//std::cout << "can not get hardware shader:" << fsDesc.m_pFragShader->GetRefPath() << std::endl;
			return;
		}
		//
		pRender->SetVertexShader(pVertexShader);
		pRender->SetFragShader(pFragShader);
		//std::cout << "pRender->SetFragShader(pFragShader);" << std::endl;
		//
		BuildShaderArgs(pRender, pRenderable, pMat, eStageShaderType, pVertexShader, pFragShader);
		//std::cout << "SetPassStates(pRender, mapStates);" << std::endl;
		//
		SetPassStates(pRender, mapStates);
		//std::cout << "SetShaderArgs(pRender, pVertexShader, pFragShader);" << std::endl;
		//
		SetShaderArgs(pRender, pVertexShader, pFragShader);

		//std::cout << "SetShaderArgs(pRender, pVertexShader, pFragShader);" << std::endl;
		//
		pRender->Render(pIndexBuff, pVertexBuff);
	}
	else if (eStageShaderType == ESTAGESHADERRADIANCEONLIGHTING)
	{
		//std::cout << "else if (eStageShaderType == ESTAGESHADERRADIANCEONLIGHTING)" << std::endl;
		int index = 0;
		for each (SmartPointer<LightBase> pLight in pRenderable->m_vecLight)
		{
			if (index != 0)//index 0 render ambient
			{
				//pRender->SetZTestEnable(false);
				pRender->SetBlendEnable(true);
				pRender->SetBlendSrc(BLEND_ONE);
				pRender->SetBlendDst(BLEND_ONE);
			}
			else
			{
				//pRender->SetZTestEnable(false);
				fsDesc.m_bAmbient = true;
			}
			HardwareVertexShader* pVertexShader = pRender->m_pRenderSystem->GetHardwareVertexShader(vsdesc);
			if (nullptr == pVertexShader)
			{
				std::cout << "can not get hardware shader:" << vsdesc.m_pVertexShader->GetRefPath() << std::endl;
				return;
			}
			fsDesc.m_eLightType = pLight->m_eLightType;
			HardwareFragShader* pFragShader = pRender->m_pRenderSystem->GetHardwareFragShader(fsDesc);
			if (nullptr == pFragShader)
			{
				std::cout << "can not get hardware shader:" << fsDesc.m_pFragShader->GetRefPath() << std::endl;
				return;
			}
			//
			pRender->SetVertexShader(pVertexShader);
			pRender->SetFragShader(pFragShader);
			SetPerLightArg(pRender, pLight, pFragShader,fsDesc);
			//
			BuildShaderArgs(pRender, pRenderable, pMat, eStageShaderType, pVertexShader, pFragShader);
			//
			SetPassStates(pRender, mapStates);
			//
			SetShaderArgs(pRender, pVertexShader, pFragShader);
			//
			
			pRender->Render(pIndexBuff, pVertexBuff);
			index++;
		}
		pRender->SetBlendEnable(false);
	}






	
	

}

void RenderPass::BuildShaderArgs(RasterRender* pRender, SmartPointer<IRenderable> pRenderable, SmartPointer<RasterMaterial> pMaterial, ESTAGESHADERTYPE eShaderType, HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader)
{
	m_VertexShaderArgs.clear();
	m_FragShaderArgs.clear();

	//
	std::unordered_map<string, ShaderConstantInfo>& vertexShaderParam = pVertexShader->GetContants();
	std::unordered_map<string, ShaderConstantInfo>& fragShaderParam = pFragShader->GetContants();
	//std::cout << "SetBuiltInArgs(pRender, pRenderable,m_VertexShaderArgs, vertexShaderParam);" << std::endl;
	SetBuiltInArgs(pRender, pRenderable,m_VertexShaderArgs, vertexShaderParam);
	//std::cout << "SetBuiltInArgs(pRender, pRenderable,m_FragShaderArgs, fragShaderParam);" << std::endl;
	SetBuiltInArgs(pRender, pRenderable,m_FragShaderArgs, fragShaderParam);
	//std::cout << "for each (std::pair<string, MaterialArg*> p in pMaterial->m_matArgs)" << std::endl;
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


}

void RenderPass::SetPassStates(RasterRender* pRender, const RenderStateCollection& mapStates)
{

	bool bFillModeChanged = false;
	for each (stRenderState rs in m_vecRenderState)
	{
		switch (rs.m_eRenderState)
		{
			case ALPHATEST:
			{
				pRender->SetAlphaTest((bool)rs.m_nValue);
			}
			break;
			case ALPHATESTREF:
			{
				pRender->SetAlphaTestFactor((int)rs.m_nValue);
			}
			break;
			case ALPHABLEND:
			{
				pRender->SetBlendEnable((bool)rs.m_nValue);
			}
			break;
			case ZTEST:
			{
				pRender->SetZTestEnable((bool)rs.m_nValue);
			}
			break;
			case ZFUNC:
			{
				pRender->SetZFunc((ERENDERCMPFUNC)rs.m_nValue);
			}
			break;
			case FILLMODE:
			{
				pRender->SetFillMode((EFILLMODE)rs.m_nValue);
				bFillModeChanged = true;
			}
			break;
			default:
			break;
		}
	}
	if (bFillModeChanged == false)
	{
		pRender->SetFillMode(EFILLMODE_SOLID);
	}
}
void RenderPass::SetShaderArgs(RasterRender* pRender,HardwareVertexShader* pVertexShader, HardwareFragShader* pFragShader)
{
	pRender->SetTexture(0, nullptr);
	pRender->SetTexture(1, nullptr);
	pRender->SetTexture(2, nullptr);
	pRender->SetTexture(3, nullptr);
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

void RenderPass::SetBuiltInArgs(RasterRender* pRender, SmartPointer<IRenderable> pRenderable, std::unordered_map<string, MaterialArg*>& argToBuild, std::unordered_map<string, ShaderConstantInfo>& argIn)
{

	if (pRender == nullptr || pRender->m_pCurrentRenderCamera == nullptr || pRenderable == nullptr || pRenderable->m_pOwnerObj == nullptr || pRenderable->m_pOwnerObj->m_pTransform == nullptr)
	{
		if (pRender == nullptr)
		{
			std::cout << "render is null" << std::endl;
		}
		if (pRender->m_pCurrentRenderCamera == nullptr)
		{
			std::cout << "render camera is null" << std::endl;
		}
		if (pRenderable == nullptr)
		{
			std::cout << "renderable is null" << std::endl;
		}
		if (pRenderable->m_pOwnerObj == nullptr)
		{
			std::cout << "pRenderable->m_pOwnerObj is null" << std::endl;
		}
		if (pRenderable->m_pOwnerObj->m_pTransform == nullptr)
		{
			std::cout << "pRenderable->m_pOwnerObj->m_pTransform is null" << std::endl;
		}
		*((int*)0) = 11;
		//std::cout << "pRener is null" << std::endl;
		return;
	}
	if (pRenderable->m_pVertexData->m_SkinMatrix != nullptr)
	{
		TMatArg<SmartPointer<SkinMatrixInfo>>& skinArg = *(GetArgFromLib<SmartPointer<SkinMatrixInfo>>("SKINMATRIX_ARRAY", EMATARGMATRIX44ARRAY));;
		skinArg.m_Data = pRenderable->m_pVertexData->m_SkinMatrix;
		if (pRenderable->m_pVertexData->m_SkinMatrix->nSize > 256)
		{
			int c = 0;
		}
		argToBuild["SKINMATRIX_ARRAY"] = &skinArg;
	}
	//
	Matrix44 matWorld = pRenderable->m_pOwnerObj->m_pTransform->GetWorldMatrix();
	Matrix44 matView = pRender->m_pCurrentRenderCamera->GetViewMatrix();
	Matrix44 matProj = pRender->m_pCurrentRenderCamera->GetProjMatrix();
	Vector3	CameraView = pRender->m_pCurrentRenderCamera->m_pOwnerObj->m_pTransform->GetWorldTranslate();

	for each (std::pair<string, ShaderConstantInfo> p in argIn)
	{
		//std::cout << p.first << std::endl;

		//  MATRIX_WORLD
		//	MATRIX_VIEW
		//	MATRIX_PROJ
		//	MATRIX_WV
		//	MATRIX_WVP
		//	MATRIX_INVERSEWV
		//	VIEW_POS
		
		if (p.first == "MATRIX_WORLD")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matWorld;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_VIEW")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matView;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_PROJ")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matProj;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_WV")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matWorld * matView;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_VP")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			arg.m_Data = matView * matProj;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_WVP")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			arg.m_Data = matWorld * matView * matProj;
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_INVERSETRANSPOSEWV")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			Matrix44 matWV = matWorld * matView;
			arg.m_Data = Matrix44::QuikInverse(matWV);
			arg.m_Data = arg.m_Data.Transpose();
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "MATRIX_INVERSEWV")
		{
			TMatArg<Matrix44>& arg = *(GetArgFromLib<Matrix44>(p.first, EMATARGMATRIX44));
			//TMatArg<Matrix44> arg(EMATARGMATRIX44);
			Matrix44 matWV = matWorld * matView;
			arg.m_Data = Matrix44::QuikInverse(matWV);
			argToBuild[p.first] = &arg;
		}
		else if (p.first == "VIEW_POS")
		{
			TMatArg<Vector3>& arg = *(GetArgFromLib<Vector3>(p.first, EMATARGTYPEFLOAT3));
			Vector3 vecPos = CameraView;
			arg.m_Data = vecPos;
			argToBuild[p.first] = &arg;
		}
	}
}

void RenderPass::SetPerLightArg(RasterRender* pRender, SmartPointer<LightBase> pLight, HardwareFragShader* pFragShader, FragShaderDesc& desc)
{
	GameColor c = pLight->m_Color;
	Vector4 vec;
	vec.m_fx = c.m_fR;
	vec.m_fy = c.m_fG;
	vec.m_fz = c.m_fB;
	vec.m_fw = c.m_fA;
	pFragShader->SetVector("GAMELIGHTCOLOR", vec);
	if (desc.m_bAmbient == true)
	{
		GameColor c = EnviromentSetting::GetInstance()->GetAmbientColor();
		Vector4 vec;
		vec.m_fx = c.m_fR;
		vec.m_fy = c.m_fG;
		vec.m_fz = c.m_fB;
		vec.m_fw = c.m_fA;
		pFragShader->SetVector("GAMEAMBIENTCOLOR", vec);
	}
	//
	//
	pFragShader->SetFloat("GAMELIGHTINTENSITY", pLight->m_fIntensity);
	//
	if (pLight->m_eLightType == EDIRLIGHT)
	{
		SmartPointer<DirectionalLight> pDirLight = pLight.SmartPointerCast<DirectionalLight>();
		Vector3 dir = -pDirLight->m_pOwnerObj->m_pTransform->GetForward();
		Vector4 v = Vector4( dir.m_fx, dir.m_fy, dir.m_fz ,0.0f);
		pFragShader->SetVector("GAMELIGHTDIR", v);
	}
	else if (pLight->m_eLightType == EPOINTLIGHT)
	{
		SmartPointer<PointLight> pPointLight = pLight.SmartPointerCast<PointLight>();
		Vector3 position = pPointLight->m_pOwnerObj->m_pTransform->GetWorldTranslate();
		Vector4 v = Vector4(position.m_fx, position.m_fy, position.m_fz, 1.0f);
		pFragShader->SetVector("GAMELIGHTPOS", v);

	}
}

RenderPass* RenderPass::clone()
{
	RenderPass* pPass = new RenderPass();
	return pPass;
}
