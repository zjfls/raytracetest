#pragma once
namespace ZG
{
	class IWorldObj;
}

//���ƽ�ɫ
class CharacterController
{
public:
	CharacterController();
	virtual ~CharacterController();


	IWorldObj* m_pObj;
};

