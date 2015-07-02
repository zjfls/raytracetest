// AppLoader.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "windows.h"
#include "tinyxml2.h"
#include <string>
#include "ApplicationBase.h"
#include "D3D9Application.h"
using namespace tinyxml2;
typedef ApplicationBase* (WINAPI *GetApplication)();
int _tmain(int argc, _TCHAR* argv[])
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../gameInfo.xml");

	XMLElement* pElem = doc.FirstChildElement("GameInfo");
	std::string strName = pElem->Attribute("name");

	HMODULE hRenderDLL = LoadLibrary((strName + ".dll").c_str());
	GetApplication pFunc = (GetApplication)GetProcAddress(hRenderDLL, "GetApplication");
	D3D9Application::theApp = (D3D9Application*)pFunc();
	D3D9Application::theApp->Init(argc, argv);
	D3D9Application::theApp->Run();
	return 0;
}

