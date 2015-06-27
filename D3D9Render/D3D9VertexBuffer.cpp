#include "stdafx.h"
#include "D3D9VertexBuffer.h"


D3D9VertexBuffer::D3D9VertexBuffer()
{
}


D3D9VertexBuffer::~D3D9VertexBuffer()
{
	SAFE_RELEASE(m_pVertexBuffer);
}
