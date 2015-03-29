#include "stdafx.h"
#include <direct.h>
#include "FbxAppManager.h"
#include "AssetManager.h"
#include "FbxAppImporter.h"
#include "ResourceManager.h"
#include "MeshResource.h"
int _tmain(int argc, _TCHAR* argv[])
{
	_chdir("../");
	//ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>("fdsf");
	FbxAppManager::GetInstance()->Init();
	AssetManager::GetInstance()->Init();

	FbxAppImporter::GetInstance()->ImportFbxFile("./data/meshes/porlfull.fbx");
	return 0;
}