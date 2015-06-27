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
#include "EnviromentSetting.h"
#include "VertexData.h"
#include "RenderView.h"
#include "Texture.h"
#include "IWorldObj.h"
#include "IRenderable.h"
#include "HardwareVertexShader.h"
#include "HardwareFragShader.h"
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
			GameColor* colorValue = pArg->GetData<GameColor>();
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
		case EMATARGMATRIX44ARRAY:
		{
			SmartPointer<SkinMatrixInfo> pInfo = *pArg->GetData<SmartPointer<SkinMatrixInfo> >();
			return SetMatrixArray(strName, pInfo->matArray, pInfo->nSize);
		}
		case EMATARGTYPESAMPLER:
		{
			TextureSampler* pSampler = pArg->GetData<TextureSampler>();
			ShaderConstantInfo info = m_mapConstants[strName];

			HardwareTexture* pTex = pRender->m_pRenderSystem->GetHardwareTexture(pSampler->m_pTexture);
			pRender->SetTexture(info.m_nRegIndex, pTex);
			if (pSampler->m_eTextureUseType == ETU_NORMAL)
			{
				pRender->SetSamplerSRGB(info.m_nRegIndex, 0);
			}
			else
			{
				if ((bool)EnviromentSetting::GetInstance()->GetIntSetting("LinearLighting") == true)
				{
					pRender->SetSamplerSRGB(info.m_nRegIndex, 1);
				}
			}
		}
		break;
		default:
		{

		}
		break;
	}
	return false;
}

bool HardwareShader::SetTextureArg(RasterRender* pRender, string strName, HardwareTexture* pTexture,ETEXUSETYPE eTexUseType)
{
	ShaderConstantInfo info = m_mapConstants[strName];
	pRender->SetTexture(info.m_nRegIndex, pTexture);
	if (eTexUseType == ETU_NORMAL)
	{
		pRender->SetSamplerSRGB(info.m_nRegIndex, 0);
	}
	else
	{
		if ((bool)EnviromentSetting::GetInstance()->GetIntSetting("LinearLighting") == true)
		{
			pRender->SetSamplerSRGB(info.m_nRegIndex, 1);
		}
	}
	return true;
}
