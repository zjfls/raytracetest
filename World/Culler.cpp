#include "stdafx.h"
#include "Culler.h"
#include "CameraBase.h"
#include "AABBBox.h"
#include "IRenderable.h"
#include "IntersectTest.h"
#include "Vector4.h"

ZG::Culler::Culler()
{

}

ZG::Culler::~Culler()
{

}

void ZG::Culler::cull(const std::vector<SmartPointer<IRenderable>>& vecRend, std::vector<SmartPointer<IRenderable>>& vecOut,SmartPointer<CameraBase> pCamera)
{
	AABBBox cvv;
	cvv.m_Min = Vector3(-1.0f, -1.0f, 0.0f);
	cvv.m_Max = Vector3(1.0f, 1.0f, 1.0f);
	Matrix44 matViewProj = pCamera->m_MatViewProj;
	//
	for each (SmartPointer<IRenderable> var in vecRend)
	{
		AABBBox* pBox = dynamic_cast<AABBBox*>(var->m_pBounding);
		if (pBox != nullptr)
		{
			AABBBox box = *pBox;
			{
				AABBBox box2 = *pBox;
				box2.Transform(pCamera->m_MatView);
				box2.Transform(pCamera->m_MatViewProj);
				

				Vector4 vPos;
				vPos.Vector3ToPoint(pBox->m_Min);
				Vector4 vPos2 = vPos;
				vPos = vPos * pCamera->m_MatView;
				vPos = vPos * pCamera->m_MatProj;
				vPos2 = vPos2 * pCamera->m_MatViewProj;
			}
			box.Transform(matViewProj);
			if (IntersectTest::AABBBox_AABBBoxTest(cvv, box) == true)
			{
				vecOut.push_back(var);
			}
		}
	}
	//
	//vecOut = vecRend;
}
