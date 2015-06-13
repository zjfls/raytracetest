#pragma once
#include "ModuleBase.h"
namespace ZG
{
	class AnimationTrack;
	class MAIN_API AnimationModule:public ModuleBase
	{
	public:
		AnimationModule();
		virtual ~AnimationModule();


		virtual bool PlayAnimation(std::string strName);

		//
		std::unordered_map<std::string, SmartPointer<AnimationTrack>> m_mapTracks;
	};
}


