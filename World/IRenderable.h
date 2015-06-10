#pragma once
#include "ModuleBase.h"
#include "VertexData.h"
#include "IndexData.h"
#include <vector>
#include "IListenerSubject.h"
#include "SmartPointer.h"
namespace ZG
{
	class LightBase;
	class MaterialResource;
	class BoundingBase;
	class AABBBox;
	class WORLD_API IRenderable :public ModuleBase
	{
	public:
		IRenderable();
		virtual ~IRenderable();

		virtual SmartPointer<MaterialResource> GetDefaultMaterial();

		virtual void Update();

		SmartPointer<MaterialResource> m_pSharedMaterial;
		virtual SmartPointer<ModuleBase> Clone(){ return nullptr; };
		virtual void BuildBoundingVolume();


		virtual SmartPointer<MaterialResource> GetMaterialInstance();
		//if MaterialInstance is not nullptr return MaterialInstance else return sharedMaterial;
		virtual SmartPointer<MaterialResource> getRenderMaterial();
	protected:
		friend class RenderPass;
		SmartPointer<MaterialResource> m_pMaterialInstance;
	public:
		std::vector<SmartPointer<LightBase>> m_vecLight;
		BoundingBase* m_pBounding;
		SmartPointer<VertexData> m_pVertexData;
		SmartPointer<IndexData> m_pIndexData;
		//AABBBox* m_pBox
	};

}