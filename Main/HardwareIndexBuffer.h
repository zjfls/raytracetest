#pragma once
#include "HardwareBuffer.h"
#include "RenderEnum.h"
namespace ZG
{
	class MAIN_API HardwareIndexBuffer :public HardwareBuffer
	{
	public:
		HardwareIndexBuffer();
		virtual ~HardwareIndexBuffer();


		//
		//
		EnumIndexDesc m_IndexDesc;
		unsigned int m_nIndexNum;
	};
}


