#pragma once
#include "HardwareShader.h"
#include "MaterialArg.h"
namespace ZG
{
	class MAIN_API HardwareVertexShader :
		public HardwareShader
	{
	public:
		HardwareVertexShader();
		virtual ~HardwareVertexShader();
	};
}

