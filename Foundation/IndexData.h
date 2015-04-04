#pragma once
#include "RenderEnum.h"
class IndexData;
class FOUNDATION_API IndexData
{
public:
	IndexData()
		:pData(nullptr)
		, indexNum(0)
	{

	}
	void* pData;
	~IndexData()
	{
		if (pData != nullptr)
		{
			delete[] pData;
			pData = nullptr;
		}

	}
	unsigned int GetBuffLength() const;

	//nv:0,1,2
	unsigned int GetIndexAt(int nTriangle, int nV) const;
	EnumIndexDesc indexDesc;
	int indexNum;

};

