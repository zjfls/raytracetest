#pragma once
#include "RenderView.h"
#include "d3d9.h"

class D3D9RenderView :
	public RenderView
{
public:
	D3D9RenderView();
	virtual ~D3D9RenderView();
	virtual bool Present();


	IDirect3DSwapChain9Ex* m_pSwapChain;
};

