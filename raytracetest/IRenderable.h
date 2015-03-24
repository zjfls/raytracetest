#pragma once
#include "ModuleBase.h"
#include "VertexData.h"
#include "IndexData.h"
class MaterialResource;
class IRenderable :public ModuleBase
{
public:
	IRenderable();
	virtual ~IRenderable();

	virtual shared_ptr<MaterialResource> GetDefaultMaterial();

	virtual void Update();
	shared_ptr<MaterialResource> m_pMaterial;
protected:
	VertexData* m_pVertexData;
	IndexData* m_pIndexData;

	friend class RenderPass;
};

