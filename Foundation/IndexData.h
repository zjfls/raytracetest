#pragma once
#include "RenderEnum.h"
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

	EnumIndexDesc indexDesc;
	int indexNum;

};

