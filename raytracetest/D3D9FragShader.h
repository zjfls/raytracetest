#pragma once
#include "HardwareFragShader.h"
struct IDirect3DPixelShader9;
class D3D9FragShader :
	public HardwareFragShader
{
public:
	D3D9FragShader();
	virtual ~D3D9FragShader();

	IDirect3DPixelShader9* m_pFragShader;
};

