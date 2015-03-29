#include "stdafx.h"
#include "RayTraceRender.h"
#include "RayTraceCamera.h"
#include "RayTraceViewPort.h"
#include "Ray3D.h"
#include "IWorld.h"
#include "IntersectTest.h"
#include "ImageFileHelper.h"
#include "SimpleRTMaterial.h"
#include <assert.h>
#include "IWorldObj.h"
#include "IRenderable.h"
#include "MathFunc.h"
int RayTraceRender::MAXDEPTH = 3;
RayTraceRender::RayTraceRender()
{
	
}


RayTraceRender::~RayTraceRender()
{

}

int RayTraceRender::Render(CameraBase* pCamera, IWorld* pWorld)
{
	
	
	RayTraceCamera* pRTCamera = dynamic_cast<RayTraceCamera*>(pCamera);
	assert(pRTCamera != nullptr && pRTCamera->GetPerpViewPort() != nullptr);
	m_pCachedCamera = pRTCamera;
	m_pCachedWorld = pWorld;
	m_vecRenderables = pWorld->GetAllComponent<IRenderable>();
	m_vecLights = pWorld->GetAllComponent<LightBase>();
	const RayTraceViewPort* pViewPort = pRTCamera->GetPerpViewPort();
	assert(pViewPort != nullptr);



	float fLeftHeight, fRightHeight, fLeftHeightStepSize, fRightHeightStepSize;
	Vector3 vecLeftDir, vecRightDir;
	vecLeftDir = pViewPort->m_vecPt[2] - pViewPort->m_vecPt[0];
	vecRightDir = pViewPort->m_vecPt[3] - pViewPort->m_vecPt[1];
	fLeftHeight = vecLeftDir.length();
	fRightHeight = vecRightDir.length();
	vecLeftDir.normalize();
	vecRightDir.normalize();
	assert(pViewPort->m_pixHeight != 0 && pViewPort->m_pixWidth != 0);
	fLeftHeightStepSize = fLeftHeight / pViewPort->m_pixHeight;
	fRightHeightStepSize = fRightHeight / pViewPort->m_pixHeight;


	Color* cBuffer = new Color[pViewPort->m_pixWidth * pViewPort->m_pixHeight];

	for (int i = 0; i < pViewPort->m_pixHeight; ++i)
	{
		//system("cls");
		std::cout << i << "th row!" << std::endl;
		Vector3 vecLeft, vecRight;
		vecLeft = pViewPort->m_vecPt[0] + (i + 0.5f) * fLeftHeightStepSize * vecLeftDir;
		vecRight = pViewPort->m_vecPt[1] + (i + 0.5f) * fRightHeightStepSize * vecRightDir;


		Vector3 vecHorzDiff = vecRight - vecLeft;
		float fHorzLength = vecHorzDiff.length();
		float fHorzStepSize = fHorzLength / pViewPort->m_pixWidth;
		Vector3 vecHorzDir = vecHorzDiff;
		vecHorzDir.normalize();
		for (int j = 0; j < pViewPort->m_pixWidth; ++j)
		{
			Vector3 vecTarget;
			if (fHorzLength == 0)
			{
				vecTarget = vecLeft;
			}
			else
			{
				vecTarget = vecLeft + fHorzStepSize * (j + 0.5f) * vecHorzDir;
			}
			//
			Vector3 vecPri;
			vecPri = vecTarget - m_pCachedCamera->m_pOwnerObj->m_pTransform->GetWorldTranslate();
			vecPri.normalize();
			Ray3D r(m_pCachedCamera->m_pOwnerObj->m_pTransform->GetWorldTranslate(), vecPri);
			cBuffer[i * pViewPort->m_pixWidth + j] = RayTrace(r,1);
			//std::cout << i << " " << j << " " << cBuffer[i * pViewPort->m_pixWidth + j].m_fR << ":" << cBuffer[i * pViewPort->m_pixWidth + j].m_fG << ":" << cBuffer[i * pViewPort->m_pixWidth + j].m_fB << std::endl;

		}
		
	}
	system("pause");
	//
	ppmImage* pImage = new ppmImage("./output.ppm", pViewPort->m_pixWidth, pViewPort->m_pixHeight);
	for (int i = 0; i < pViewPort->m_pixWidth * pViewPort->m_pixHeight; ++i)
	{
		pImage->stream << (unsigned char)(std::min(cBuffer[i].m_fR, 1.0f) * 255)
			<< (unsigned char)(std::min(cBuffer[i].m_fG, 1.0f) * 255)
			<< (unsigned char)(std::min(cBuffer[i].m_fB, 1.0f) * 255);
	}
	pImage->Save();
	//
	return 0;
}

Color RayTraceRender::RayTrace(const Ray3D& r,int nDepth)
{
//primary ray
	Color	pixColor;
	//Vector3 vecPri;
	//vecPri = vecTarget - m_pCachedCamera->m_pOwnerObj->m_pTransform->GetWorldTranslate();
	//vecPri.normalize();
	//Ray3D r(m_pCachedCamera->m_pOwnerObj->m_pTransform->GetWorldTranslate(),vecPri);
	//r.m_vecPos = m_pCachedCamera->m_pOwnerObj->m_pTransform->m_vecTranslate;
	//r.m_vecDirection = vecPri;
	IRenderable* pInterGeo = nullptr;
	float fInterDist = 1000000000;
	Vector3 vecInterPos = Vector3::ZERO;
	Vector3 vecNormal = Vector3::ONE;
	for each (IRenderable* var in m_vecRenderables)
	{
		IntersectResults result = IntersectTest::testRayRenderables(r, var, *var->m_pOwnerObj->m_pTransform);
		if (result.m_bInterset == true)
		{
			if (fInterDist > result.m_vecIntersetDatas[0].fDist)
			{
				pInterGeo = var;
				fInterDist = result.m_vecIntersetDatas[0].fDist;
				vecInterPos = result.m_vecIntersetDatas[0].vecPos;
				vecNormal = result.m_vecIntersetDatas[0].vecNormal;
			}
		}
	}
	if (pInterGeo != nullptr)
	{

		shared_ptr<SimpleRTMaterial> pRTMat = dynamic_pointer_cast<SimpleRTMaterial>(pInterGeo->m_pMaterial);
		if (pRTMat == nullptr)
		{
			pixColor = Color::white;
		}
		else
		{
			Color cContribute = Color::black;
			//shadow ray
			for each (LightBase* var in m_vecLights)
			{
				vecNormal.normalize();
				Vector3 vecShadowPos = vecInterPos + vecNormal * 0.01f;
				Vector3 vecShadowDir = -var->GetLightDirection(vecInterPos);// var->m_pOwnerObj->m_pTransform->GetTranslate() - vecShadowPos;
				vecShadowDir.normalize();
				Ray3D shadowRay(vecShadowPos, vecShadowDir);
				if (ShadowRay(shadowRay, var) == false)
				{
					cContribute = cContribute + pRTMat->m_ColorDiffuse * var->m_Color * var->GetIrradiance(vecInterPos,vecNormal);
				}
				else
				{

				}
			}
			if (pRTMat->m_bReflection == true && nDepth <= MAXDEPTH)
			{
				Vector3 vecReflectDir = GetReflectionDir(r.GetDir(),vecNormal);
				Vector3 vecRayPos = vecInterPos + vecNormal * 0.01f;
				Ray3D rayRef(vecRayPos,vecReflectDir);
				Color refColor = RayTrace(rayRef, nDepth + 1);
				cContribute = cContribute + refColor * pRTMat->m_ColorDiffuse * GetFresnelReflectance(1.0f, pRTMat->m_fRefractiveIndex, r.GetDir(), vecNormal);
			}
			if (pRTMat->m_bRefraction == true && nDepth <= MAXDEPTH)
			{
				Vector3 vecRefractDir = GetRefracionDir(1.0f, pRTMat->m_fRefractiveIndex, r.GetDir(), vecNormal);
				Vector3 vecRefractPos = vecInterPos - vecNormal * 0.01f;
				Ray3D rayRefra(vecRefractPos, vecRefractDir);
				Color refractColor = RayTrace(rayRefra, nDepth + 1);
				if (refractColor.m_fR > 0.0f || refractColor.m_fR > 0.0f || refractColor.m_fG > 0.0f || refractColor.m_fB > 0.0f)
				{
					//std::cout << refractColor.m_fR << " " << refractColor.m_fG << " " << refractColor.m_fB << std::endl;
				}
				cContribute = cContribute + refractColor * pRTMat->m_ColorDiffuse *GetTransmitRadianceCoef(1.0f, pRTMat->m_fRefractiveIndex, r.GetDir(), vecNormal) * pRTMat->m_fTransparecy;
			}

			pixColor = cContribute + pRTMat->m_ColorEmi + Color(0.00f,0.00f,0.00f,0.0f);
		}
		//	
	}
	else
	{
		pixColor = Color::black;
	}


	pixColor.m_fR = std::powf(pixColor.m_fR, 1.0f / 2.2f);
	pixColor.m_fG = std::powf(pixColor.m_fG, 1.0f / 2.2f);
	pixColor.m_fB = std::powf(pixColor.m_fB, 1.0f / 2.2f);
	return pixColor;
}

//to do check tranparent
bool RayTraceRender::ShadowRay(const Ray3D& r, LightBase* pLight)
{
	float fDist = pLight->m_pOwnerObj->m_pTransform->GetWorldTranslate().distance(r.m_vecPos);
	for each (IRenderable* var in m_vecRenderables)
	{
		IntersectResults result = IntersectTest::testRayRenderables(r, var, *var->m_pOwnerObj->m_pTransform);
		if (result.m_bInterset == true)
		{
			for (unsigned int i = 0; i < result.m_vecIntersetDatas.size(); ++i)
			{
				if (result.m_vecIntersetDatas[i].fDist < fDist)
				{
					return true;
				}
			}
			//return true;
		}
	}
	return false;
}
