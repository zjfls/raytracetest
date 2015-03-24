#pragma once
#include "HardwareVertexBuffer.h"
#include "d3d9.h"
struct IDirect3DVertexBuffer9;
class D3D9VertexBuffer :
	public HardwareVertexBuffer
{
public:

	virtual ~D3D9VertexBuffer();
private:
	D3D9VertexBuffer();
	IDirect3DVertexDeclaration9* m_pVertexDecal;
	IDirect3DVertexBuffer9* m_pVertexBuffer;
	friend class D3D9RenderSystem;
	friend class D3D9Render;
};

