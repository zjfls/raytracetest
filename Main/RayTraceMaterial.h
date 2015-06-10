#pragma once
#include "MaterialResource.h"
namespace ZG
{
	class MAIN_API RayTraceMaterial :
		public MaterialResource
	{
	public:
		RayTraceMaterial();
		virtual ~RayTraceMaterial();
	};

}