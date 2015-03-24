#pragma once
#include "HardwareIndexBuffer.h"
class IDirect3DIndexBuffer9;
class D3DIndexBuffer :
	public HardwareIndexBuffer
{
public:
	D3DIndexBuffer();
	virtual ~D3DIndexBuffer();


	IDirect3DIndexBuffer9* m_pIndexBuffer;
};

