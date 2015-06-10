#include "stdafx.h"
#include "FilePath.h"
#include "StrUtil.h"
#include "CommonDef.h"
#include <tchar.h>
#include <string.h>
std::string ZG::getFileSuffix(string fullFilePath)
{
	if (fullFilePath[fullFilePath.length() - 1] == '.')
	{
		return "";
	}
	string suffix;
	string name = getFileName(fullFilePath);
	//string suffix = "";
	//if (fullFilePath.length() <= 2)
	//{
	//	return suffix;
	//}
	//int length = fullFilePath.length();
	//int nLoc = -1;
	//for (int i = length - 2; i >= 0; --i)
	//{
	//	char c = fullFilePath.at(i);
	//	if (c == '.')
	//	{
	//		nLoc = i;
	//		break;
	//	}
	//}
	//if (nLoc != -1)
	//{
	//	suffix = fullFilePath.c_str() + nLoc + 1;
	//}
	const char* pPos = strchr(name.c_str(), '.');
	if (pPos == nullptr)
	{
		return "";
	}
	suffix = pPos + 1;
	return suffix;
}

std::string ZG::getFileName(string fullFilePath)
{
	replaceCharInString(fullFilePath, '\\', '/');
	string strRet;
	const char* pPos = strrchr(fullFilePath.c_str(), '/');
	if (pPos == nullptr)
	{
		strRet = fullFilePath;
	}
	else
	{
		TCHAR temp[MAX_FILENAME_LENGTH];
		_tcscpy_s(temp, pPos);
		strRet = temp + 1;
	}
	
	return strRet;
}

std::string ZG::getFileDirectory(string fullFilePath)
{
	replaceCharInString(fullFilePath, '\\', '/');
	string strRet;
	const char* pPos = strrchr(fullFilePath.c_str(), '/');
	if (pPos == nullptr)
	{
		strRet = "./";
	}
	else
	{
		TCHAR temp[MAX_FILEPATH_LENGTH];
		unsigned int nLength = _tcslen(fullFilePath.c_str()) - _tcslen(pPos) + 1;
		_tcsncpy_s(temp, fullFilePath.c_str(), nLength);
		temp[nLength] = 0;
		strRet = temp;
	}
	return strRet;
}

std::string ZG::removeSuffix(string fileName)
{
	string strRet;
	const char* pPos = strrchr(fileName.c_str(), '.');
	if (pPos == nullptr)
	{
		strRet = fileName;
	}
	else
	{
		TCHAR temp[MAX_FILENAME_LENGTH];
		unsigned int nLength = _tcslen(fileName.c_str()) - _tcslen(pPos);
		_tcsncpy_s(temp, fileName.c_str(), nLength);
		strRet = temp;
	}
	return strRet;
}

std::string ZG::getFileNameWithoutSuffix(string fullFilePath)
{
	string fileName = getFileName(fullFilePath);
	return removeSuffix(fileName);
}

