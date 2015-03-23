#pragma once
#include "MaterialResource.h"
#include "RenderPass.h"
#include "RenderEnum.h"
class RasterMaterial :
	public MaterialResource
{
public:
	RasterMaterial();
	virtual ~RasterMaterial();

	void BuildPassParameter(RenderPass* pPass);
	std::map<string, RenderPass*> m_RenderPassMap;
};

