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

int _tmain(int argc, _TCHAR* argv[])
{
	RayTraceApplication::GetInstance()->Init();
	return 0;
}

