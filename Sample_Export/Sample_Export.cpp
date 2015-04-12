#include "stdafx.h"
#include <direct.h>
#include "FbxAppManager.h"
#include "AssetManager.h"
#include "FbxAppImporter.h"
#include "ResourceManager.h"
#include "MeshResource.h"
#include "D3D9Application.h"
#include "windows.h"
#define LEN 1024
BOOL  DirectoryList(LPCSTR Path)
{
	WIN32_FIND_DATA FindData;
	HANDLE hError;
	int FileCount = 0;
	char FilePathName[LEN];
	// 构造路径
	char FullPathName[LEN];
	strcpy_s(FilePathName, Path);
	strcat_s(FilePathName, "\\*.*");
	hError = FindFirstFile(FilePathName, &FindData);
	if (hError == INVALID_HANDLE_VALUE)
	{
		printf("搜索失败!");
		return 0;
	}
	while (::FindNextFile(hError, &FindData))
	{
		// 过虑.和..
		if (strcmp(FindData.cFileName, ".") == 0
			|| strcmp(FindData.cFileName, "..") == 0)
		{
			continue;
		}

		// 构造完整路径
		sprintf_s(FullPathName, "%s\\%s", Path, FindData.cFileName);
		FileCount++;
		FbxAppImporter::GetInstance()->ImportFbxFile(FullPathName);
		// 输出本级的文件
		printf_s("\n%d  %s  ", FileCount, FullPathName);

		if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf("\n<Dir>");
			DirectoryList(FullPathName);
		}



	}
	return 0;
}
int _tmain(int argc, _TCHAR* argv[])
{
	_chdir("../");
	//ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>("fdsf");
	FbxAppManager::GetInstance()->Init();
	AssetManager::GetInstance()->Init();
	//FbxAppImporter::GetInstance()->ImportFbxFile("./data/fbx/plane.fbx");
	//return 0;
	DirectoryList("H:\\github\\raytracetest\\data\\fbx\\");
	std::cout << std::endl;
	system("pause");
	

	return 0;
}