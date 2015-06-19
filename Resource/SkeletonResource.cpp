#include "stdafx.h"
#include "SkeletonResource.h"
#include "ResourceManager.h"
#include "Matrix33.h"
SmartPointer<ResourceManager<SkeletonResource>> Singleton<ResourceManager<SkeletonResource>>::_instance = nullptr;

SkeletonResource::SkeletonResource()
{
}


SkeletonResource::~SkeletonResource()
{
}

void ZG::SkeletonResource::UpdateMatrix()
{
	m_pRoot->UpdateMatrix(Matrix44::Identity);
}

int Bone::GetBoneIndexByName(string name)
{
	if (name == m_strName)
	{
		return nIndex;
	}
	for each (Bone* pChild in vecChild)
	{
		int rt = pChild->GetBoneIndexByName(name);
		if (rt >= 0)
		{
			return rt;
		}
	}
	return -1;
}

void ZG::Bone::UpdateMatrix(Matrix44 parentMat)
{
	Matrix33 matScale;
	matScale.ScaleMatrix(s.m_fx, s.m_fy, s.m_fz);
	Matrix33 matRot;
	matRot.FromEulerAngleXYZ(r);
	Matrix44 matTraslate;
	matTraslate.TraslateMatrix(t.m_fx, t.m_fy, t.m_fz);


	m_SkeletonMatrix = Matrix44::Identity;
	Matrix44 mat44s, mat44r;
	mat44s.FromMatrix33(&matScale);
	mat44r.FromMatrix33(&matRot);
	//first scale ,then rotation, last translate
	m_SkeletonMatrix = mat44s * mat44r * matTraslate * parentMat;
	m_MatrixInverse = Matrix44::QuikInverse(m_SkeletonMatrix);
	int nChild = vecChild.size();
	for each (Bone* pChild in vecChild)
	{
		pChild->UpdateMatrix(m_SkeletonMatrix);
	}
}
