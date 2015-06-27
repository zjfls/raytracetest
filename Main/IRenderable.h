#pragma once
#include "ModuleBase.h"
#include "VertexData.h"
#include "IndexData.h"
#include <vector>
#include "IListenerSubject.h"
#include "SmartPointer.h"
#include "Triangle.h"
#include "MaterialResource.h"
#include "LightBase.h"
namespace ZG
{
	class LightBase;
	class MaterialResource;
	class BoundingBase;
	class AABBBox;
	class MAIN_API IRenderable :public ModuleBase
	{
	public:
		IRenderable();
		virtual ~IRenderable();

		virtual SmartPointer<MaterialResource> GetDefaultMaterial();

		virtual void OnUpdate();

		SmartPointer<MaterialResource> m_pSharedMaterial;


		virtual SmartPointer<ModuleBase> Clone();
		virtual void BuildBoundingVolume();


		virtual SmartPointer<MaterialResource> GetMaterialInstance();
		//if MaterialInstance is not nullptr return MaterialInstance else return sharedMaterial;
		virtual SmartPointer<MaterialResource> getRenderMaterial();

		//
		Triangle GetTriangle(unsigned int nIndex) const;
		Triangle GetWorldTriangle(unsigned int nIndex) const;
		int		GetTriangleNum() const;
	protected:
		friend class RenderPass;
		SmartPointer<MaterialResource> m_pMaterialInstance;
	public:
		std::vector<SmartPointer<LightBase>> m_vecLight;
		BoundingBase* m_pBounding;
		SmartPointer<VertexData> m_pVertexData;
		SmartPointer<IndexData> m_pIndexData;
		SmartPointer<SkinMatrixInfo> m_pSkinMatrixInfo;
		//AABBBox* m_pBox
	};

}