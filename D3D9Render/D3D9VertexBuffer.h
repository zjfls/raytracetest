#pragma once
#include "HardwareVertexBuffer.h"
#include "d3d9.h"
#include "VertexData.h"
struct IDirect3DVertexBuffer9;

struct stD3DVertexBuffDecal
{
	std::vector<VertexData::VertexDataDesc> m_vecDataDesc;
	IDirect3DVertexDeclaration9* m_pVertexDecal;
};
class D3D9VertexBuffer :
	public HardwareVertexBuffer
{
public:

	virtual ~D3D9VertexBuffer();
private:
	D3D9VertexBuffer();
	//IDirect3DVertexDeclaration9* m_pVertexDecal;
	IDirect3DVertexBuffer9* m_pVertexBuffer;
	stD3DVertexBuffDecal* m_pVertexBuffDecal;



	friend class D3D9RenderSystem;
	friend class D3D9Render;
};

