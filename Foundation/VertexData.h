#pragma once
#include "RenderEnum.h"
#include "VertexData.h"
#include "Vector3.h"
#include "GameObjectBase.h"
#include "Matrix44.h"
namespace ZG
{
	struct SkinMatrixInfo:public GameObjectBase
	{
		SkinMatrixInfo()
		{
			nSize = 0;
		}
		int nSize;
		Matrix44 matArray[256];
	};
	class IndexData;
	class AABBBox;
	class FOUNDATION_API VertexData :public GameObjectBase
	{
	public:
		VertexData() :nBoneNum(0)
			, nNumVertex(0)
			, m_PrimitiveType(EPRIMITIVE_TRIANGLE)
			, m_pAABB(nullptr)
			, m_SkinMatrix(nullptr)
		{};
		virtual ~VertexData();
		virtual void getBoundingMaxAndMin(Vector3& min, Vector3& max) = 0;
		virtual Vector3 GetPositionDataAt(int nIndex) const = 0;
		int		GetVertexDataLength()const;
		struct VertexDataDesc
		{
			EnumVertexUseDesc usedesc;
			EnumVertexTypeDesc typedesc;
			unsigned int nOffset;//in byte
		};
		static int		GetTypeLength(const VertexDataDesc& desc);




	public:
		std::vector<VertexData::VertexDataDesc> vecDataDesc;
		unsigned int nNumVertex;
		unsigned int nBoneNum;//每个顶点对应的骨头数量
		EDRAWPRIMITIVETYPE m_PrimitiveType;

		SmartPointer<SkinMatrixInfo> m_SkinMatrix;
		AABBBox* m_pAABB;
	};
	class FOUNDATION_API MeshVertexData :public VertexData
	{
	public:
		MeshVertexData()
			:pData(nullptr)

		{

		}
		virtual ~MeshVertexData()
		{
			if (pData != nullptr)
			{
				delete[](unsigned char*)pData;
				pData = nullptr;
			}

		}
		void* pData;

		//Vector3 getPositionByIndex(int nIndex) override;
		void getBoundingMaxAndMin(Vector3& min, Vector3& max) override;
		Vector3 GetPositionDataAt(int nIndex) const override
		{
			Vector3 vecPos;
			VertexDataDesc desc = vecDataDesc[0];
			float* pfData = (float*)pData;
			pfData = (float*)((char*)pfData + desc.nOffset + nIndex * GetVertexDataLength());
			vecPos.m_fx = *pfData;
			pfData++;
			vecPos.m_fy = *pfData;
			pfData++;
			vecPos.m_fz = *pfData;
			return vecPos;
		}
		//默认normal描述是第2个
		Vector3 GetNormalDataAt(int nIndex)
		{
			Vector3 vecNormal;
			VertexDataDesc desc = vecDataDesc[1];
			float* pfData = (float*)pData;
			pfData = (float*)((char*)pfData + desc.nOffset + nIndex * GetVertexDataLength());
			vecNormal.m_fx = *pfData;
			pfData++;
			vecNormal.m_fy = *pfData;
			pfData++;
			vecNormal.m_fz = *pfData;
			return vecNormal;
		}
		void ComputeTangent(const IndexData& indexData);
		unsigned int GetBuffLength() const;

		void*	GetElementData(int descIndex, int posIndex) const;





	};
}


