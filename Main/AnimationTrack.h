#pragma once
#include <unordered_map>
#include "AnimationBind.h"
namespace ZG
{
	class AnimationTrack
	{
	public:
		AnimationTrack();
		virtual ~AnimationTrack();



		void AddTrack(std::string strName, SmartPointer<AnimationBindBase>);
	private:
		std::unordered_map<std::string, SmartPointer<AnimationBindBase>> m_mapAnims;
	};
}


