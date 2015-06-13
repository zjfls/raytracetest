#pragma once
#include "AnimationCurve.h"
namespace ZG
{
	enum AnimationBindType
	{
		EANIFLOAT,
		EANIVECTOR3
	};
	class AnimationBindBase:public GameObjectBase
	{
	public:
		AnimationBindBase();
		virtual ~AnimationBindBase();
		virtual void Bind(void* pValue, AnimationBindType eType) = 0;
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


