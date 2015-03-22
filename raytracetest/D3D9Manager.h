#pragma once
#include "d3dx9.h"
#include "d3d9.h"
class D3D9Render;
class D3D9RenderView;
//class D3DRenderView;
class D3D9Manager:public Singleton<D3D9Manager>
{
public:
	D3D9Manager();
	virtual ~D3D9Manager();

	bool Init();
	void CreateDevice();

public:
	LPDIRECT3D9EX             m_pD3D;
	LPDIRECT3DDEVICE9EX		m_pD3DDevice;
	D3D9RenderView*			m_pDefaultRenderView;
	D3D9Render*				m_pDefaultRender;
};

