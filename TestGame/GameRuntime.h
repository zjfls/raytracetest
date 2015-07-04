#pragma once
#include "ModuleBase.h"
#include "Vector3.h"
#include "Vector2.h"
namespace ZG
{
	class CameraBase;
	class IWorldObj;
}
class CharacterController;
//所有逻辑暂时写这里
class GameRuntime:public ModuleBase
{
public:
	GameRuntime();
	virtual ~GameRuntime();
	void OnUpdate() override;
	void OnLateUpdate() override;
	SmartPointer<ModuleBase> Clone() override;
	CharacterController* createCharacterController(std::string fileName);
private:
	void UpdateInput();
	void UpdateCamera();
	void UpdateCharacter();
private:
	//
	IWorldObj* m_pCamera;
	std::vector<CharacterController*> m_vecCharacter;


	//input
	Vector2 m_LastCursorPos;
	friend class GameApp;
};

