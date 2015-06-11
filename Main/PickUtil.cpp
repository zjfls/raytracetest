#include "stdafx.h"
#include "PickUtil.h"
#include "CameraBase.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "IWorldObj.h"
PickUtil::PickUtil()
{
}


PickUtil::~PickUtil()
{

}

Vector3 PickUtil::ScreenPosToWorldPos(Vector2& screenPos, float fDistToCamera, SmartPointer<CameraBase> pCamera, int nScreenWidth, int nScreenHeight)
{
	Vector3 vecRt;
	Vector3 posInCamera;
	posInCamera.m_fz = 1.0f;
	posInCamera.m_fy = tan(pCamera->m_fFovy/2) * (nScreenHeight / 2 - screenPos.m_fy) / (nScreenHeight / 2);
	posInCamera.m_fx = tan(pCamera->m_fFovy/2) * pCamera->m_fAspect * (screenPos.m_fx - nScreenWidth / 2) / (nScreenWidth / 2);

	//
	Matrix44& matWorld = pCamera->m_pOwnerObj->m_pTransform->GetWorldMatrix();
	Vector4 vWorldDir;
	vWorldDir.Vector3ToDirection(posInCamera);
	vWorldDir = vWorldDir * matWorld;
	//
	Vector3 v3WorldDir;
	v3WorldDir.m_fx = vWorldDir.m_fx;
	v3WorldDir.m_fy = vWorldDir.m_fy;
	v3WorldDir.m_fz = vWorldDir.m_fz;
	v3WorldDir = v3WorldDir.normalize();


	Vector3 cameraPos = pCamera->m_pOwnerObj->m_pTransform->GetWorldTranslate();
	vecRt = cameraPos + v3WorldDir * fDistToCamera;
	return vecRt;
}

ZG::Vector3 ZG::PickUtil::ScreenPosToWorldDir(Vector2& screenPos, SmartPointer<CameraBase> pCamera, int nScreenWidth, int nScreenHeight)
{
	Vector3 vecRt;
	Vector3 posInCamera;
	posInCamera.m_fz = 1.0f;
	posInCamera.m_fy = tan(pCamera->m_fFovy / 2) * (nScreenHeight / 2 - screenPos.m_fy) / (nScreenHeight / 2);
	posInCamera.m_fx = tan(pCamera->m_fFovy / 2) * pCamera->m_fAspect * (screenPos.m_fx - nScreenWidth / 2) / (nScreenWidth / 2);

	//
	Matrix44& matWorld = pCamera->m_pOwnerObj->m_pTransform->GetWorldMatrix();
	Vector4 vWorldDir;
	vWorldDir.Vector3ToDirection(posInCamera);
	vWorldDir = vWorldDir * matWorld;
	//
	Vector3 v3WorldDir;
	v3WorldDir.m_fx = vWorldDir.m_fx;
	v3WorldDir.m_fy = vWorldDir.m_fy;
	v3WorldDir.m_fz = vWorldDir.m_fz;
	v3WorldDir = v3WorldDir.normalize();
	return v3WorldDir;
}
