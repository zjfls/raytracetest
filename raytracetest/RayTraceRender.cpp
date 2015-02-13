#include "stdafx.h"
#include "RayTraceRender.h"
#include "RayTraceCamera.h"
#include "RayTraceViewPort.h"
#include "Ray3D.h"
#include "IWorld.h"
#include "IntersectTest.h"
#include "ImageFileHelper.h"
#include "SimpleRTMaterial.h"

RayTraceRender::RayTraceRender()
{
	
}


RayTraceRender::~RayTraceRender()
{

}

int RayTraceRender::Render(CameraBase* pCamera, IWorld* pWorld)
{
	
	
	RayTraceCamera* pRTCamera = dynamic_cast<RayTraceCamera*>(pCamera);
	assert(pRTCamera != nullptr && pRTCamera->m_pViewPort != nullptr);
	m_pCachedCamera = pRTCamera;
	m_pCachedWorld = pWorld;
	m_vecRenderables = pWorld->GetAllComponent<IRenderable>();
	m_vecLights = pWorld->GetAllComponent<LightBase>();
	RayTraceViewPort* pViewPort = pRTCamera->m_pViewPort;



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
			cBuffer[i * pViewPort->m_pixWidth + j] = RayTrace(vecTarget);
		}
	}
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

Color RayTraceRender::RayTrace(const Vector3& vecTarget)
{
//primary ray
	Color	pixColor;
	Vector3 vecPri;
	vecPri = vecTarget - m_pCachedCamera->m_pOwnerObj->m_pTransform->GetTranslate();
	vecPri.normalize();
	Ray3D r(m_pCachedCamera->m_pOwnerObj->m_pTransform->GetTranslate(),vecPri);
	//r.m_vecPos = m_pCachedCamera->m_pOwnerObj->m_pTransform->m_vecTranslate;
	//r.m_vecDirection = vecPri;
	IRenderable* pInterGeo = nullptr;
	float fInterDist = 1000000000;
	Vector3 vecInterPos = Vector3::ZERO;
	Vector3 vecNormal = Vector3::ONE;
	for each (IRenderable* var in m_vecRenderables)
	{
		IntersetResults result = IntersectTest::testRayRenderables(r, var, *var->m_pOwnerObj->m_pTransform);
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

		SimpleRTMaterial* pRTMat = dynamic_cast<SimpleRTMaterial*>(pInterGeo->m_pMaterial);
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
				Vector3 vecShadowDir = -var->m_pOwnerObj->m_pTransform->GetForward();// var->m_pOwnerObj->m_pTransform->GetTranslate() - vecShadowPos;
				vecShadowDir.normalize();
				Ray3D shadowRay(vecShadowPos, vecShadowDir);
				if (ShadowRay(shadowRay, var) == false)
				{
					cContribute = cContribute + pRTMat->m_ColorDiffuse * var->m_Color * var->m_fIntensity * std::max(vecNormal.dot(-var->m_pOwnerObj->m_pTransform->GetForward()), 0.0f);
				}
				else
				{

				}
			}
			pixColor = cContribute + pRTMat->m_ColorEmi + Color(0.1f,0.1f,0.1f,0.0f);
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

bool RayTraceRender::ShadowRay(const Ray3D& r, LightBase* pLight)
{
	for each (IRenderable* var in m_vecRenderables)
	{
		IntersetResults result = IntersectTest::testRayRenderables(r, var, *var->m_pOwnerObj->m_pTransform);
		if (result.m_bInterset == true)
		{
			return true;
		}
	}
	return false;
}
