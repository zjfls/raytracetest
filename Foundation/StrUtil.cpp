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

