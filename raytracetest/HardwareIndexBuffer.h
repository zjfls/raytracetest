#pragma once
#include "HardwareBuffer.h"
#include "RenderEnum.h"
class HardwareIndexBuffer:public HardwareBuffer
{
public:
	HardwareIndexBuffer();
	virtual ~HardwareIndexBuffer();


	//
	//
	EnumIndexDesc m_IndexDesc;
	unsigned int m_nIndexNum;
};

