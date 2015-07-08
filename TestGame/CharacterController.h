#pragma once
#include <unordered_map>
namespace ZG
{
	class IWorldObj;
	class AnimationTrack;
}

//¿ØÖÆ½ÇÉ«
class CharacterController
{
public:
	CharacterController();
	virtual ~CharacterController();


	void LoadAnimation(std::string strName, std::string path);
	void PlayAnimation(std::string strName);

	std::string curAnimation;
	IWorldObj* m_pObj;
	std::unordered_map<std::string, AnimationTrack*> m_pAnimations;
};

