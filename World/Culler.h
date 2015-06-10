#pragma once
#include <vector>

namespace ZG
{
	class IRenderable;
	class Matrix44;
	class CameraBase;
	class WORLD_API Culler
	{
	public:
		Culler();
		virtual ~Culler();


		void cull(const std::vector<SmartPointer<IRenderable>>& vecRend, std::vector<SmartPointer<IRenderable>>& vecOut, SmartPointer<CameraBase> pCamera);
	};
}


