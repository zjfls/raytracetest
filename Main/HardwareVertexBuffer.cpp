#include "stdafx.h"
#include "HardwareVertexBuffer.h"


HardwareVertexBuffer::HardwareVertexBuffer()
	:m_nNumVertex(0)
	, m_eType(EPRIMITIVE_TRIANGLE)
	//, m_pVertexData(nullptr)
{
}


HardwareVertexBuffer::~HardwareVertexBuffer()
{
}
