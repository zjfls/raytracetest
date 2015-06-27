#pragma once
#include "RenderEnum.h"
namespace ZG
{
	class MAIN_API HardwareBuffer:public GameObjectBase
	{
	public:
		HardwareBuffer();
		virtual ~HardwareBuffer();


		EMAMANGETYPE m_eManageType;
	};
}


