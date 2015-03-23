#pragma once
#include "HardwareVertexShader.h"
struct IDirect3DVertexShader9;
class D3D9VertexShader :
	public HardwareVertexShader
{
public:
	D3D9VertexShader();
	virtual ~D3D9VertexShader();


	IDirect3DVertexShader9* m_pVertexShader;
};

