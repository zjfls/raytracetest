#pragma once
#include "RayTraceViewPort.h"
namespace ZG
{
	//��ֱ�����ӿ�
	class RayTraceCamera;
	class RayTracePerpViewPort :
		public RayTraceViewPort
	{
	public:
		RayTracePerpViewPort();
		RayTracePerpViewPort(const Point3D& vecPt, const Direction3D& vecNormal, float fVertFov, float fHorzFov, int pixWidth, int pixHeight);
		virtual ~RayTracePerpViewPort();

		virtual void OnTransformChanged(RayTraceCamera* pCamera);

	public:
		float m_fVertFov;
		float m_fHorzFov;
		float m_fNear;



	};
}

