#pragma once
#include "ObjComponent.h"
class IRenderable;
class RenderComponent :
	public ObjComponent
{
public:
	RenderComponent();
	~RenderComponent();


	IRenderable* m_pTobeRender;
};

