#include "stdafx.h"
#include "StrUtil.h"
void ZG::replaceCharInString(string& str, char cSrc, char cDst)
{
	int nLength = str.length();
	for (int i = 0; i < nLength; ++i)
	{
		if (str[i] == cSrc)
		{
			str[i] = cDst;
		}
	}
}

FOUNDATION_API std::string ZG::numberToString(int nNumber, int rad)
{
	char temp[10];
	_itoa_s(nNumber, temp, 10, rad);
	return temp;
}

