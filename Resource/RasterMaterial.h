#pragma once
#include "MaterialResource.h"
//#include "RenderPass.h"
#include "RenderEnum.h"

class RenderPass;
class RESOURCE_API RasterMaterial :
	public MaterialResource
{
public:
	RasterMaterial();
	virtual ~RasterMaterial();
	void	AddPass(string strName, RenderPass* pPass);
	virtual shared_ptr<MaterialResource> clone();
	//void BuildPassParameter(RenderPass* pPass);
protected:
	std::map<string, RenderPass*> m_RenderPassMap;
	friend class RenderStage;
};

