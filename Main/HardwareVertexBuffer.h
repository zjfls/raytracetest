#pragma once
#include "HardwareBuffer.h"
#include "RenderEnum.h"
class MAIN_API HardwareVertexBuffer :public HardwareBuffer
{
public:
	HardwareVertexBuffer();
	virtual ~HardwareVertexBuffer();



	unsigned int m_nNumVertex;
	unsigned int m_nStrip;


	EDRAWPRIMITIVETYPE m_eType;
};

