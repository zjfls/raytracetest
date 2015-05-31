#pragma once
#include "ModuleBase.h"
#include "VertexData.h"
#include "IndexData.h"
#include <vector>
#include "IListenerSubject.h"
#include "SmartPointer.h"
class LightBase;
class MaterialResource;
class BoundingBase;
using ZG::SmartPointer;
class WORLD_API IRenderable :public ModuleBase
{
public:
	IRenderable();
	virtual ~IRenderable();

	virtual shared_ptr<MaterialResource> GetDefaultMaterial();

	virtual void Update();
	shared_ptr<MaterialResource> m_pMaterialInstance;
	shared_ptr<MaterialResource> m_pSharedMaterial;
	virtual shared_ptr<ModuleBase> Clone(){ return nullptr; };
	virtual void BuildBoundingVolume();
protected:
	SmartPointer<VertexData> m_pVertexData;
	SmartPointer<IndexData> m_pIndexData;
	BoundingBase* m_pBounding;
	friend class RenderPass;
public:
	std::vector<shared_ptr<LightBase>> m_vecLight;
};

