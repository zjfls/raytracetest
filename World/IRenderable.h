#pragma once
#include "ModuleBase.h"
#include "VertexData.h"
#include "IndexData.h"
#include <vector>
class LightBase;
class MaterialResource;
class WORLD_API IRenderable :public ModuleBase
{
public:
	IRenderable();
	virtual ~IRenderable();

	virtual shared_ptr<MaterialResource> GetDefaultMaterial();

	virtual void Update();
	shared_ptr<MaterialResource> m_pMaterialInstance;
	shared_ptr<MaterialResource> m_pSharedMaterial;
	virtual ModuleBase* Clone(){ return nullptr; };
protected:
	VertexData* m_pVertexData;
	IndexData* m_pIndexData;

	friend class RenderPass;
public:
	std::vector<LightBase*> m_vecLight;
};

