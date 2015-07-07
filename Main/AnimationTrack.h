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
		bool GetBind()
		{
			return m_bIsBind;
		}
		void ClearBind()
		{
			m_mapAnims.clear();
		}
		template<class T>
		void	AddBind(std::string strName, T* pRef);
		

		void	Start();
		void	Update();
	private:
		std::unordered_map<std::string, SmartPointer<AnimationBindBase>> m_mapAnims;
		bool m_bIsBind;
		float m_fStartTime;
	public:
		SmartPointer<AnimationResource> m_pResource;
		std::string m_strName;
	};

	template<class T>
	void ZG::AnimationTrack::AddBind(std::string strName, T* pRef)
	{
		AnimationCurve<T>* pAnim = dynamic_cast<AnimationCurve<T>*>(m_pResource->getCurveByName(strName));
		if (pAnim == nullptr)
		{
			std::cout << "add bind failed"<<std::endl;
			return;
		}
		AnimationBind<T>* pBind = new AnimationBind<T>();
		pBind->pAnimationCurve = pAnim;
		pBind->m_pValue = pRef;
		m_mapAnims[strName] = pBind;
	}


}


