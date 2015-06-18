#include "stdafx.h"
#include "Transform.h"
#include "Orientation.h"
#include "IWorldObj.h"
#include <iostream>

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

void Transform::OnUpdate()
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
	//first scale ,then rotation, last translate
	m_TransformMatrixLocal = mat44s * mat44r * matTraslate;

	if (m_pOwnerObj->m_pParent == nullptr)
	{
		m_TransformMatrixWorld = m_TransformMatrixLocal;
	}
	else
	{
		m_TransformMatrixWorld = m_TransformMatrixLocal * m_pOwnerObj->m_pParent->m_pTransform->m_TransformMatrixWorld;
	}
	m_bThisFrameUpdated = true;
	SetDirty(false);
	NotifyNeedTransform();
	//std::cout << m_pOwnerObj->m_strName << "  updated" << std::endl;
}

void Transform::NotifyNeedTransform()
{
	for each (SmartPointer<IWorldObj> var in m_pOwnerObj->m_vecChildren)
	{
		var->m_pTransform->SetDirty(true);;
	}
	for each (SmartPointer<ModuleBase> var in m_pOwnerObj->m_vecModules)
	{
		var->m_bTransformUpdated = true;
	}
}

void Transform::SetTranslate(float fX, float fY, float fZ)
{
	m_vecTranslate = Vector3(fX, fY, fZ);
	SetDirty(true);
}

void Transform::SetTranslate(const Vector3& vecIn)
{
	m_vecTranslate = vecIn; 
	SetDirty(true);
}

void Transform::SetOrientation(float fX, float fY, float fZ)
{
	m_Orientation.m_vecEulerAngle = Vector3(fX, fY, fZ);
	SetDirty(true);
}

void Transform::SetScale(float fx, float fY, float fZ)
{
	m_vecScale = Vector3(fx, fY, fZ);
	SetDirty(true);
}

Vector3 Transform::GetWorldTranslate() const
{
	return Vector3(m_TransformMatrixWorld.M[3][0], m_TransformMatrixWorld.M[3][1], m_TransformMatrixWorld.M[3][2]);
}

SmartPointer<ModuleBase> Transform::Clone()
{
	SmartPointer<Transform> pTransform = SmartPointer<Transform>(new Transform());
	pTransform->SetDirty(true);
	//pTransform->m_TransformMatrixLocal = m_TransformMatrixLocal;
	pTransform->m_TransformMatrixWorld = m_TransformMatrixWorld;
	//pTransform->m_vecTranslate = m_TransformMatrixWorld.GetTranslate();
	//pTransform->m_vecScale = m_TransformMatrixWorld.GetScale();
	//pTransform->m_Orientation.m_vecEulerAngle = m_TransformMatrixWorld.GetRotation();
	pTransform->m_vecTranslate = m_vecTranslate;
	pTransform->m_Orientation = m_Orientation;
	pTransform->m_vecScale = m_vecScale;
	return pTransform.get();
}

Matrix44 Transform::GetWorldMatrix() const
{
	return m_TransformMatrixWorld;
}

void ZG::Transform::SetWorldTransform(const Matrix44& mat)
{
	Matrix44 matParent;
	if (m_pOwnerObj != nullptr && m_pOwnerObj->m_pParent != nullptr)
	{
		matParent = m_pOwnerObj->m_pTransform->m_TransformMatrixWorld;
	}
	//
	//
	Matrix44 matLocal = mat * Matrix44::QuikInverse(matParent);
	m_vecTranslate = matLocal.GetTranslate();
	m_vecScale = matLocal.GetScale();
	m_Orientation.m_vecEulerAngle = matLocal.GetRotation();
}

void ZG::Transform::SetWorldTranslate(const Vector3& vecTrans)
{
	SetDirty(true);
	if (m_pOwnerObj != nullptr && m_pOwnerObj->m_pParent == nullptr)
	{
		m_vecTranslate = vecTrans;
		return;
	}
	//
	Vector3 vecScale = m_TransformMatrixWorld.GetScale();
	Vector3 vecRot = m_TransformMatrixWorld.GetRotation();

	//
	Matrix33 matScale;
	matScale.ScaleMatrix(vecScale.m_fx, vecScale.m_fy, vecScale.m_fz);
	Matrix33 matRot;//
	matRot.FromEulerAngleXYZ(vecRot);
	Matrix44 matTraslate;
	matTraslate.TraslateMatrix(vecTrans.m_fx, vecTrans.m_fy, vecTrans.m_fz);


	;
	Matrix44 mat44s, mat44r;
	mat44s.FromMatrix33(&matScale);
	mat44r.FromMatrix33(&matRot);

	Matrix44 matWorld = mat44s * mat44r * matTraslate;
	//
	Matrix44 matParent = m_pOwnerObj->m_pParent->m_pTransform->GetWorldMatrix();
	//m_TransformMatrixWorld = m_pOwnerObj->m_pTransform->m_TransformMatrixWorld;
	//
	Matrix44 matLocal = matWorld * Matrix44::QuikInverse(matParent);
	m_vecTranslate = matLocal.GetTranslate();


	Matrix44 matworld2 = matLocal * matParent;

	Matrix44 matIdentity = matParent * Matrix44::QuikInverse(matParent);
	int i = 3;
	//
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
