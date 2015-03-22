#pragma once
#include "RasterRender.h"
class D3D9Render :
	public RasterRender
{
public:
	D3D9Render(const RenderPath* pPath);
	virtual ~D3D9Render();


	//static D3D9Render* create(void* pArg);
};

