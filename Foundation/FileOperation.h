#pragma once
#include <string>
#include <vector>

namespace ZG
{
	FOUNDATION_API bool CpyFile(std::string src, std::string dst);
	//�ҵ�������Ӧ���͵��ļ���
	FOUNDATION_API void FindFile(std::string path, std::vector<std::string>& vecPath, std::string strSpec, bool bRecursive = false);
}