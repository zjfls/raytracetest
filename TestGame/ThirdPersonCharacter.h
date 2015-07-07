#pragma once
#include "CharacterController.h"
namespace ZG
{
	class IWorldObj;
}
class ThirdPersonCharacter:public CharacterController
{
public:
	ThirdPersonCharacter();
	virtual ~ThirdPersonCharacter();


	void OnInput();

	IWorldObj* m_pCamera;
};

