#pragma once
#include "RenderEnum.h"
#include "GameObjectBase.h"
class IndexData;
using ZG::GameObjectBase;
class FOUNDATION_API IndexData:public GameObjectBase
{
public:
	IndexData()
		:pData(nullptr)
		, indexNum(0)
	{

	}
	void* pData;
	~IndexData();

	unsigned int GetBuffLength() const;

	//nv:0,1,2
	unsigned int GetIndexAt(int nTriangle, int nV) const;
	EnumIndexDesc indexDesc;
	int indexNum;

};

