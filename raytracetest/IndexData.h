#pragma once
#include "RenderEnum.h"
class IndexData
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

	EnumIndexDesc indexDesc;
	int indexNum;

};

