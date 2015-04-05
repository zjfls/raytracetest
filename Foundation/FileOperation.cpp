#include "stdafx.h"
#include "FileOperation.h"
//
//
#include<stdlib.h>
#include<stdio.h>
#include <iostream>
long filesize(FILE *stream)
{
	long curpos, length;

	curpos = ftell(stream);
	fseek(stream, 0L, SEEK_END);
	length = ftell(stream);
	fseek(stream, curpos, SEEK_SET);
	return length;
}




FOUNDATION_API bool CpyFile(std::string src, std::string dst)
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
