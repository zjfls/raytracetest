#pragma once
#include "LightBase.h"
namespace ZG
{
	class MAIN_API DirectionalLight :
		public LightBase
	{
	public:
		virtual ~DirectionalLight();
		virtual float GetIrradiance(const Vector3& vecWorldPosition, const Vector3& vecNormal);
		virtual Vector3  GetLightDirection(const Vector3& vecWorldPosition);
		virtual SmartPointer<ModuleBase> Clone();

	private:
		DirectionalLight();
		friend class IWorldObj;
	};
}