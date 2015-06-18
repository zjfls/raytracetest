#pragma once
#include <unordered_map>
#include "AnimationBind.h"
namespace ZG
{
	class AnimationResource;
	class AnimationTrack:public GameObjectBase
	{
	public:
		//AnimationTrack();
		AnimationTrack(AnimationResource* pRes);
		virtual ~AnimationTrack();
		void SetBind(bool bBind);
		
	private:
		std::unordered_map<std::string, SmartPointer<AnimationBindBase>> m_mapAnims;
		bool m_bIsBind;
	public:
		SmartPointer<AnimationResource> m_pResource;
		string m_strName;
	};
}


