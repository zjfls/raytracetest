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
	virtual	void OnDeviceLost();
	virtual void OnDeviceReset();

	IDirect3DSwapChain9* m_pSwapChain;
	int						m_nIndex;
	IDirect3DDevice9*	m_pD3DDevice;

};

