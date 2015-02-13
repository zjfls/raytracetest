#include "stdafx.h"
#include "Transform.h"



Transform::Transform()
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
	float (*m)[4] = &(*m_TransformMatrixWorld.m_Matrix);
	return Vector3(m[0][0], m[0][1], m[0][2]);
}

Vector3 Transform::GetUp()
{
	float(*m)[4] = &(*m_TransformMatrixWorld.m_Matrix);
	return Vector3(m[1][0], m[1][1], m[1][2]);
}

Vector3 Transform::GetForward()
{
	float(*m)[4] = &(*m_TransformMatrixWorld.m_Matrix);
	return Vector3(m[2][0], m[2][1], m[2][2]);
}

void Transform::Update()
{
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
	

}
