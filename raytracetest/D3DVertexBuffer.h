#pragma once
#include "HardwareVertexBuffer.h"

class IDirect3DVertexBuffer9;
class D3DVertexBuffer :
	public HardwareVertexBuffer
{
public:

	virtual ~D3DVertexBuffer();


	IDirect3DVertexBuffer9* m_pVertexBuffer;
private:
	D3DVertexBuffer();
	friend class D3DRenderSystem;
};

