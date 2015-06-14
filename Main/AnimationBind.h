#pragma once
#include "AnimationCurve.h"
namespace ZG
{

	class AnimationBindBase:public GameObjectBase
	{
	public:
		AnimationBindBase();
		virtual ~AnimationBindBase();
		virtual void Bind(void* pValue, AnimationType eType) = 0;
		virtual void Evaluate(float fTime) = 0;
	};

	template<class T>
	class AnimationBind
	{
		//
		//
		AnimationCurve<T>* pAnimationCurve;
		T* m_pValue;
	};
}


