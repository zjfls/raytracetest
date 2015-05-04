#include "stdafx.h"
#include <direct.h>
#include "FbxAppManager.h"
#include "AssetManager.h"
#include "FbxAppImporter.h"
#include "ResourceManager.h"
#include "MeshResource.h"
#include "PrefabResource.h"
#include "D3D9Application.h"
int _tmain(int argc, _TCHAR* argv[])
{
	//_chdir("../");
	////ResourceManager<MeshResource>::GetInstance()->CreateResource<MeshResource>("fdsf");
	//FbxAppManager::GetInstance()->Init();
	//AssetManager::GetInstance()->Init();
	//FbxAppImporter::GetInstance()->ImportFbxFile("./data/meshes/plane.fbx");
	//return 0;
	ResourceManager<PrefabResource>::GetInstance();
	//
	D3D9Application::GetInstance()->Init(argc, argv);
	D3D9Application::GetInstance()->Run();
	//
	return 0;
}