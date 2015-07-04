#pragma once
namespace ZG
{
	class IWorldObj;
}

//¿ØÖÆ½ÇÉ«
class CharacterController
{
public:
	CharacterController();
	virtual ~CharacterController();


	IWorldObj* m_pObj;
};

