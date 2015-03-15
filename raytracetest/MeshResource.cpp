#include "stdafx.h"
#include "MeshResource.h"
#include "ResourceMananger.h"
ResourceManager<MeshResource>* Singleton<ResourceManager<MeshResource>>::_instance = nullptr;


MeshResource::MeshResource()
{
}


MeshResource::~MeshResource()
{
}

//Vector3 MeshResource::GetPositionDataAt(int nIndex)
//{
//	return m_VertexData.GetPositionDataAt(nIndex);
//}
//
//Vector3 MeshResource::GetNormalDataAt(int nIndex)
//{
//	return m_VertexData.GetPositionDataAt(nIndex);
//}

void* stVertexData::GetElementData(int descIndex, int posIndex) const
{
	if (descIndex >= vecDataDesc.size())
	{
		return nullptr;
	}
	if (posIndex >= nNumVertex)
	{
		return nullptr;
	}
	VertexDataDesc desc = vecDataDesc[descIndex];
	int nOffset = desc.nOffset;
	int nUnitLength = GetTypeLength(desc);

	return (char*)pData + nOffset + posIndex * nUnitLength;
}

int stVertexData::GetTypeLength(const VertexDataDesc& desc) const
{
	switch (desc.typedesc)
	{
		case EVertexTypeFloat1:
		{
			return 4;
		}
		break;
		case EVertexTypeFloat2:
		{
			return 8;
		}
		break;
		case EVertexTypeFloat3:
		{
			return 12;
		}
		break;
		case EVertexTypeFloat4:
		{
			return 16;
		}
		break;
	}
	return 0;

}

int stVertexData::GetVertexDataLength() const
{
	int nLength = 0;
	for each (VertexDataDesc desc in vecDataDesc)
	{
		nLength += GetTypeLength(desc);
	}
	return nLength;
}
