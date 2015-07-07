#include "stdafx.h"
#include "FileOperation.h"
//
//
#include<stdlib.h>
#include<stdio.h>
#include <iostream>
#include <io.h>
#include <direct.h>
long filesize(FILE *stream)
{
	long curpos, length;

	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}




FOUNDATION_API bool ZG::CpyFile(std::string src, std::string dst)
{
	std::cout << "copy file from " << src.c_str() << "\" to \"" << dst.c_str()<<"\"" << std::endl;

	std::string order;
	order = std::string("COPY  \"") + src + "\" \"" + dst + "\"";
	std::cout << order.c_str() << std::endl;
	system(order.c_str());





	return true;
	//FILE* inFile;
	//fopen_s(&inFile, src.c_str(), "rb");
	//FILE* outFile;
	//fopen_s(&outFile, dst.c_str(), "wb+");
	//if (inFile == nullptr || outFile == nullptr)
	//{
	//	return false;
	//}
	//int buffsize;
	//int begin;
	//int end;
	//char* buffer;
	//if (inFile != NULL)
	//{
	//	buffsize = filesize(inFile);
	//	//printf("%d", buffsize);
	//	fseek(inFile, 0, SEEK_SET);
	//	buffer = (char*)new char[buffsize];
	//	fread(buffer, buffsize, 1, inFile);
	//	fwrite(buffer, buffsize, 1, outFile);
	//}
	//else
	//{
	//	return false;
	//}
	//delete[] buffer;
	//return true;
}

FOUNDATION_API void ZG::FindFile(std::string path, std::vector<std::string>& vecPath, std::string strSpec, bool bRecursive /*= false*/)
{
	char curDir[_MAX_PATH];
	_getcwd(curDir, _MAX_PATH);
	//_chdir(path.c_str());
	//首先查找dir中符合要求的文件  
	long hFile;
	_finddata_t fileinfo;
	if ((hFile = _findfirst((path + strSpec).c_str(), &fileinfo)) != -1)
	{
		do
		{
			//检查是不是目录  
			//如果不是,则进行处理  
			if (!(fileinfo.attrib & _A_SUBDIR))
			{
				char filename[_MAX_PATH];
				strcpy_s<_MAX_PATH>(filename, path.c_str());
				strcat_s<_MAX_PATH>(filename, fileinfo.name);
				vecPath.push_back(filename);
				//if (!ProcessFile(filename))
				//	return false;
			}
		} while (_findnext(hFile, &fileinfo) == 0);
		_findclose(hFile);
	}
	//_chdir(curDir);
}
