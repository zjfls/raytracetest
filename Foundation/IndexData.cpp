#include "stdafx.h"
#include "IndexData.h"



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
