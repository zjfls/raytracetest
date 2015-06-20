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
		virtual bool PlayAnimation(AnimationTrack* pTrack);
		bool	AddAnimationTrack(AnimationTrack* pTrack);


		void	SetDefaultAnimationTrack(AnimationTrack* pTrack);
		AnimationTrack*	GetDefaultAnimationTrack() const { return m_pDefaultTrack; };

	protected:
		void OnUpdate() override;
		void OnStart() override;
	public:


		std::vector<AnimationTrack*>			m_vecActiveTrack;
		//
		AnimationTrack*								m_pDefaultTrack;
		std::vector<SmartPointer<AnimationTrack>> m_vecTracks;
	};
}


