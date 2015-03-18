#include "stdafx.h"
#include "Geometry.h"


Geometry::Geometry()
	:m_pVertexData(nullptr)
	, m_pIndexData(nullptr)
{
}


Geometry::~Geometry()
{
}

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
