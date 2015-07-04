#pragma once
#include "ApplicationBase.h"
#include "D3D9Application.h"
#include "Singleton.h"
class GameRuntime;
class GameApp :public ZG::D3D9Application, public Singleton<GameApp>
{
public:
	GameApp();
	virtual ~GameApp();

	void SetupScene() override;

	GameRuntime* m_pGameRuntime;
};

