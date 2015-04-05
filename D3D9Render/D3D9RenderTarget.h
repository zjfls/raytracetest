#pragma once
#include "IRenderTarget.h"
class IDirect3DSurface9;
class D3D9RenderTarget :
	public IRenderTarget
{
public:
	D3D9RenderTarget();
	virtual ~D3D9RenderTarget();


	IDirect3DSurface9* m_pSurface;
};

