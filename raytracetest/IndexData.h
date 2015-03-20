#pragma once
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
	enum EnumIndexDesc
	{
		EIndexInvalid = 0,
		EIndexInt,
		EIndexShort
	};
	EnumIndexDesc indexDesc;
	int indexNum;

};

