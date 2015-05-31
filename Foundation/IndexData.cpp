#include "stdafx.h"
#include "IndexData.h"
#include "VertexIndexDataEventProxy.h"
using namespace ZG;


unsigned int IndexData::GetBuffLength() const
{
	switch (indexDesc)
	{
		case EIndexInt:
		return 4 * indexNum;
		break;
		case EIndexShort:
		return 2 * indexNum;
		break;
		default:
		break;
	}
	return 0;
}

unsigned int IndexData::GetIndexAt(int nTriangle, int nV) const
{
	if (nTriangle * 3 + nV > indexNum)
	{
		return -1;
	}
	if (indexDesc == EIndexInt)
	{
		return *((int*)pData + nTriangle * 3 + nV);
	}
	else
	{
		return *((unsigned short*)pData + nTriangle * 3 + nV);
	}
}

IndexData::~IndexData()
{
	IndexDataEventArg arg;
	arg.m_pIndexData = this;
	Event<IndexDataEventArg>* e = VertexIndexDataEventProxy::GetInstance()->getEvent<IndexDataEventArg>("INDEXDATADELETE");
	(*e)(arg);
	if (pData != nullptr)
	{
		delete[] pData;
		pData = nullptr;
	}

}
