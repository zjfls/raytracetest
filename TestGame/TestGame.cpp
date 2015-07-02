// TestGame.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TestGame.h"
#include "GameApp.h"

// 这是导出变量的一个示例
TESTGAME_API int nTestGame=0;

// 这是导出函数的一个示例。
TESTGAME_API int fnTestGame(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 TestGame.h
CTestGame::CTestGame()
{
	return;
}
extern "C" TESTGAME_API ZG::ApplicationBase* GetApplication()
{
	return GameApp::GetInstance();
}