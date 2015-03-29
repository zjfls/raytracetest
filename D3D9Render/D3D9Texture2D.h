#pragma once
#include "HardwareTexture.h"
#include "d3d9.h"
#include "d3dx9.h"
class D3D9Texture2D :
	public HardwareTexture
{
public:
	D3D9Texture2D();
	virtual ~D3D9Texture2D();


	IDirect3DTexture9* m_pTexture;
};

