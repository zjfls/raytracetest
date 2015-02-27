#include "stdafx.h"
#include "Transform.h"
#include "Orientation.h"


Transform::Transform()
:m_bDirt(true)
, m_bThisFrameUpdated(false)
{
	m_vecTranslate = Vector3::ZERO;
	m_vecScale = Vector3::ONE;
	m_Orientation.m_vecEulerAngle = Vector3::ZERO;
}


Transform::~Transform()
{
}

Vector3 Transform::GetRight()
{
	float (*m)[4] = &(*m_TransformMatrixWorld.M);
	return Vector3(m[0][0], m[0][1], m[0][2]);
}

Vector3 Transform::GetUp()
{
	float(*m)[4] = &(*m_TransformMatrixWorld.M);
	return Vector3(m[1][0], m[1][1], m[1][2]);
}

Vector3 Transform::GetForward()
{
	float(*m)[4] = &(*m_TransformMatrixWorld.M);
	return Vector3(m[2][0], m[2][1], m[2][2]);
}

void Transform::Update()
{
	m_bThisFrameUpdated = false;
	if (m_bDirt == false)
	{
		return;
	}
	assert(m_pOwnerObj != nullptr);
	Matrix33 matScale;
	matScale.ScaleMatrix(m_vecScale.m_fx,m_vecScale.m_fy,m_vecScale.m_fz);
	Matrix33 matRot = m_Orientation.ToMatrix33();
	Matrix44 matTraslate;
	matTraslate.TraslateMatrix(m_vecTranslate.m_fx, m_vecTranslate.m_fy, m_vecTranslate.m_fz);


	m_TransformMatrixLocal = Matrix44::Identity;
	Matrix44 mat44s, mat44r;
	mat44s.FromMatrix33(&matScale);
	mat44r.FromMatrix33(&matRot);
	m_TransformMatrixLocal = matTraslate * mat44s * mat44r;

	if (m_pOwnerObj->m_pParent == nullptr)
	{
		m_TransformMatrixWorld = m_TransformMatrixLocal;
	}
	else
	{
		m_TransformMatrixWorld = m_TransformMatrixLocal * m_pOwnerObj->m_pParent->m_pTransform->m_TransformMatrixWorld;
	}
	m_bThisFrameUpdated = true;
	m_bDirt = false;
	NotifyNeedTransform();

}

void Transform::NotifyNeedTransform()
{
	for each (IWorldObj* var in m_pOwnerObj->m_vecChildren)
	{
		var->m_pTransform->m_bDirt = true;
	}
}

void Transform::SetTranslate(float fX, float fY, float fZ)
{
	m_vecTranslate = Vector3(fX, fY, fZ);
	m_bDirt = true;
}

void Transform::SetOrientation(float fX, float fY, float fZ)
{
	m_Orientation.m_vecEulerAngle = Vector3(fX, fY, fZ);
	m_bDirt = true;
}

void Transform::SetScale(float fx, float fY, float fZ)
{
	m_vecScale = Vector3(fx, fY, fZ);
	m_bDirt = true;
}

Vector3 Transform::GetWorldTranslate() const
{
	return Vector3(m_TransformMatrixWorld.M[3][0], m_TransformMatrixWorld.M[3][1], m_TransformMatrixWorld.M[3][2]);
}

//ModuleBase* TransformCreator::CreateModule()
//{
//	return new Transform;
//}
//
//TransformCreator::TransformCreator()
//{
//
//}
//
//TransformCreator::~TransformCreator()
//{
//
//}
