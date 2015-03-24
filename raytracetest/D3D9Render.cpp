#include "stdafx.h"
#include "D3D9Render.h"


D3D9Render::D3D9Render(const RenderPath* pPath)
	:RasterRender(pPath)
{
}


D3D9Render::~D3D9Render()
{
}

bool D3D9Render::SetVertexShader(HardwareVertexShader* pVertexShader)
{
	return true;
}

bool D3D9Render::SetFragShader(HardwareFragShader* pFragShader)
{
	return true;
}

