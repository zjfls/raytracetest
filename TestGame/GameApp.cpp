#include "stdafx.h"
#include "GameApp.h"

template<> SmartPointer<GameApp> Singleton<GameApp>::_instance = nullptr;
GameApp::GameApp()
{
}


GameApp::~GameApp()
{
}
