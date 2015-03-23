#include "stdafx.h"
#include "D3D9FragShader.h"
#include "d3d9.h"
#include "d3dx9.h"

D3D9FragShader::D3D9FragShader()
	:m_pFragShader(nullptr)
{
}


D3D9FragShader::~D3D9FragShader()
{
	SAFE_RELEASE(m_pFragShader);
}
