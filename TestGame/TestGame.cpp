// TestGame.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "TestGame.h"
#include "GameApp.h"

// ���ǵ���������һ��ʾ��
TESTGAME_API int nTestGame=0;

// ���ǵ���������һ��ʾ����
TESTGAME_API int fnTestGame(void)
{
	return 42;
}

// �����ѵ�����Ĺ��캯����
// �й��ඨ�����Ϣ������� TestGame.h
CTestGame::CTestGame()
{
	return;
}
extern "C" TESTGAME_API ZG::ApplicationBase* GetApplication()
{
	return GameApp::GetInstance();
}