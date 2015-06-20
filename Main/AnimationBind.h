#pragma once
#include "AnimationCurve.h"
#include "AnimationResource.h"
namespace ZG
{

	class AnimationBindBase:public GameObjectBase
	{
	public:
		AnimationBindBase();
		virtual ~AnimationBindBase();
		//virtual void Bind(void* pValue, AnimationType eType) = 0;
		virtual void EvaluateDirect(float fTime) = 0;
		//
		//virtual void EvaluateDirect(float fTime, EAnimationWarpMode eWrapMode);
		//
	};

	template<class T>
	class AnimationBind:public AnimationBindBase
	{
	public:
		AnimationBind(){};
		virtual ~AnimationBind(){};
		//
		void EvaluateDirect(float fTime);
		//T    Evaluate(float fTime, EAnimationWarpMode eWrapMode);
		//
	public:
		AnimationCurve<T>* pAnimationCurve;
		T* m_pValue;
	};

	template<class T>
	void ZG::AnimationBind<T>::EvaluateDirect(float fTime)
	{
		*m_pValue = pAnimationCurve->Evaluate(fTime);
	}

}


