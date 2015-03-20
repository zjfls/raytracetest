#pragma once
#include "IRender.h"
#include "IRenderable.h"
class RasterRender :
	public IRender
{
public:
	RasterRender();
	virtual ~RasterRender();
	//render a obj
	void Render(IRenderable* pRender);
private:

};

