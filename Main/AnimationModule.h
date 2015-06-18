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

		virtual bool BindAnimation(AnimationTrack* pTrack);
		virtual bool PlayAnimation(std::string strName);
		virtual bool PlayAnimation(unsigned int index);
		bool	AddAnimationTrack(AnimationTrack* pTrack);


		void	SetDefaultAnimationTrack(AnimationTrack* pTrack);
		AnimationTrack*	GetDefaultAnimationTrack() const { return m_pDefaultTrack; };
		//
		AnimationTrack*								m_pDefaultTrack;
		std::vector<SmartPointer<AnimationTrack>> m_vecTracks;
	};
}


