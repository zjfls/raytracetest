#pragma once
#include "RasterRender.h"
class D3D9Render :
	public RasterRender
{
public:
	D3D9Render(const RenderPath* pPath);
	virtual ~D3D9Render();
	virtual bool SetVertexShader(HardwareVertexShader* pVertexShader);
	virtual bool SetFragShader(HardwareFragShader* pFragShader);

	//static D3D9Render* create(void* pArg);
};

