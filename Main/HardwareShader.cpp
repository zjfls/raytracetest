#include "stdafx.h"
#include "HardwareShader.h"
#include "Color.h"
#include "Vector4.h"
#include "Matrix44.h"
#include "TextureSampler.h"
#include "HardwareTexture.h"
#include "Texture.h"
#include "RasterRender.h"
#include "RenderSystem.h"
HardwareShader::HardwareShader()
{
}


HardwareShader::~HardwareShader()
{
}

bool HardwareShader::SetShaderArg(RasterRender* pRender, string strName, MaterialArg* pArg)
{
	switch (pArg->m_EType)
	{
		case	EMATARGTYPEFLOAT1:
		{
			float* fValue = pArg->GetData<float>();
			return SetFloat(strName, *fValue);
		}
		break;
		case EMATARGTYPEFLOAT3:
		{

		}
		break;
		case	EMATARGTYPEFLOAT4:
		{
			Vector4* vecValue = pArg->GetData<Vector4>();
			return SetVector(strName, *vecValue);
		}
		break;
		case	EMATARGTYPECOLOR:
		{
			Color* colorValue = pArg->GetData<Color>();
			Vector4 vecColor = Vector4(colorValue->m_fR, colorValue->m_fG, colorValue->m_fB, colorValue->m_fB);
			return SetVector(strName, vecColor);
		}
		break;
		case	EMATARGTYPEINT:
		{
			int* nValue = pArg->GetData<int>();
			return SetInt(strName, *nValue);
		}
		break;
		case EMATARGMATRIX44:
		{
			Matrix44* pMat = pArg->GetData<Matrix44>();
			return SetMatrix(strName, *pMat);
		}
		case EMATARGTYPESAMPLER:
		{
			TextureSampler* pSampler = pArg->GetData<TextureSampler>();
			ShaderConstantInfo info = m_mapConstants[strName];

			HardwareTexture* pTex = pRender->m_pRenderSystem->GetHardwareTexture(pSampler->m_pTexture);
			pRender->SetTexture(info.m_nRegIndex, pTex);
		}
		break;
		default:
		{

		}
		break;
	}
	return false;
}
