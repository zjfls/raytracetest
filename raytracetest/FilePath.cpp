#include "stdafx.h"
#include "FilePath.h"
std::string getFileSuffix(string fullFilePath)
{
	string suffix = "";
	if (fullFilePath.length() <= 2)
	{
		return suffix;
	}
	int length = fullFilePath.length();
	int nLoc = -1;
	for (int i = length - 2; i >= 0; --i)
	{
		char c = fullFilePath.at(i);
		if (c == '.')
		{
			nLoc = i;
			break;
		}
	}
	if (nLoc != -1)
	{
		suffix = fullFilePath.c_str() + nLoc + 1;
	}
	return suffix;
}

