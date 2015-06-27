#pragma once
#include "CameraBase.h"
#include "Matrix44.h"
namespace ZG
{
	class MAIN_API RasterCamera :
		public CameraBase
	{
	public:
		RasterCamera();
		~RasterCamera();
		virtual void OnUpdate();

		virtual SmartPointer<ModuleBase> Clone();
		//
		//
	};

}