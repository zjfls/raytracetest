// raytracetest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "SimpleWorld.h"
#include "SimpleWorldObj.h"
#include "RayTraceCamera.h"
#include "Vector3.h"
#include "Sphere3D.h"
#include "MaterialManager.h"
#include "LightBase.h"
#include "RayTraceApplication.h"
#include "SimpleD3D9Application.h"
#include "SimpleGLApplication.h"

#include "FbxAppManager.h"
#include "AssetManager.h"
#include "FbxAppImporter.h"
int _tmain(int argc, _TCHAR* argv[])
{
	FbxAppManager::GetInstance()->Init();
	AssetManager::GetInstance()->Init();
	FbxAppImporter::GetInstance()->ImportFbxFile("../data/meshes/file_split.fbx");
	//IAsset* pAsset = AssetManager::GetInstance()->LoadAsset("../data/meshes/file_split.fbx");
	return 0;
	//SimpleD3D9Application::GetInstance()->Init(argc, argv);
	//SimpleD3D9Application::GetInstance()->Run();

	//RayTraceApplication::GetInstance()->Init(argc, argv);
	//RayTraceApplication::GetInstance()->Run();
	//return 0;
}
