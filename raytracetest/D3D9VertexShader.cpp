#include "stdafx.h"
#include "D3D9VertexShader.h"
#include "d3d9.h"


D3D9VertexShader::D3D9VertexShader()
	:m_pVertexShader(nullptr)
{
}


D3D9VertexShader::~D3D9VertexShader()
{
	SAFE_RELEASE(m_pVertexShader);
}
