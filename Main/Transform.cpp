#include "stdafx.h"
#include "Transform.h"
#include "Orientation.h"
#include "IWorldObj.h"
#include <iostream>

Transform::Transform()
:m_bDirt(true)
, m_bThisFrameUpdated(false)
{
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
	matScale.ScaleMatrix(GetScale().m_fx, GetScale().m_fy, GetScale().m_fz);
	Matrix33 matRot;
	matRot.FromEulerAngleXYZ(GetRotation());
	Matrix44 matTraslate;
	matTraslate.TraslateMatrix(GetLocalTranslate().m_fx, GetLocalTranslate().m_fy, GetLocalTranslate().m_fz);


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
	m_TransformData.m_vecTranslate = Vector3(fX, fY, fZ);
	SetDirty(true);
}

void Transform::SetTranslate(const Vector3& vecIn)
{
	m_TransformData.m_vecTranslate = vecIn; 
	SetDirty(true);
}

void Transform::SetOrientation(float fX, float fY, float fZ)
{
	m_TransformData.m_vecRotation = Vector3(fX, fY, fZ);
	SetDirty(true);
}

void Transform::SetScale(float fx, float fY, float fZ)
{
	m_TransformData.m_vecScale = Vector3(fx, fY, fZ);
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
	pTransform->m_TransformData = m_TransformData;
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
	m_TransformData.m_vecTranslate = matLocal.GetTranslate();
	m_TransformData.m_vecScale = matLocal.GetScale();
	m_TransformData.m_vecRotation = matLocal.GetRotation();
}

void ZG::Transform::SetWorldTranslate(const Vector3& vecTrans)
{
	SetDirty(true);
	if (m_pOwnerObj != nullptr && m_pOwnerObj->m_pParent == nullptr)
	{
		m_TransformData.m_vecTranslate = vecTrans;
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
	m_TransformData.m_vecTranslate = matLocal.GetTranslate();


	Matrix44 matworld2 = matLocal * matParent;

	Matrix44 matIdentity = matParent * Matrix44::QuikInverse(matParent);
	//
}

ZG::Matrix44 ZG::Transform::GetLocalMatrix() const
{
	return m_TransformMatrixLocal;
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

ZG::stTransformData ZG::stTransformData::operator+(const stTransformData& data)
{
	stTransformData rt;
	rt.m_vecTranslate = m_vecTranslate + data.m_vecTranslate;
	rt.m_vecRotation = m_vecRotation + data.m_vecRotation;
	rt.m_vecScale = m_vecScale + data.m_vecScale;
	return rt;
}

ZG::stTransformData ZG::stTransformData::operator*(const float fValue)
{
	stTransformData rt;
	rt.m_vecTranslate = m_vecTranslate * fValue;
	rt.m_vecRotation = m_vecRotation * fValue;
	rt.m_vecScale = m_vecScale * fValue;
	return rt;
}

ZG::stTransformData& ZG::stTransformData::operator=(const stTransformData& data)
{
	m_vecTranslate = data.m_vecTranslate;
	m_vecRotation = data.m_vecRotation;
	m_vecScale = data.m_vecScale;
	return *this;
}
