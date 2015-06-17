#pragma once
#include <vector>
#include "KeyFrame.h"
#include "MathFunc.h"
namespace ZG
{
	enum AnimationType
	{
		EANITYPENONE,
		EANIFLOAT,
		EANIVECTOR3,
		EANITRANSFORM
	};
	enum AnimationWarpMode
	{

	};
	class MAIN_API AnimationCurveBase :public GameObjectBase
	{
	public:
		AnimationCurveBase(AnimationType eType)
			:m_eType(eType)
		{

		}
		virtual ~AnimationCurveBase(){};
		AnimationType getType(){ return m_eType; }
	private:
		AnimationType m_eType;
	};
	template<class T>
	class MAIN_API AnimationCurve :public AnimationCurveBase
	{
	public:
		AnimationCurve(AnimationType eType);
		virtual ~AnimationCurve();
		//
		void AddKeyFrame(float fTime, T& value);
		void RemoveKeyFrame(int nIndex);
		//evaluate in milisecond
		void RemoveKeyFrame(float fTime);
		//
		T	Evaluate(float fTime);
		unsigned int GetSize() const;
		KeyFrame<T>   GetKeyFrame(int nIndex){ return m_KeyFrames[nIndex]; };



	private:
		void sort();
		bool SortFunc(const KeyFrame<T>& d1, const KeyFrame<T>& d2);
		//
	private:
		float m_fLength;
		std::vector<KeyFrame<T>> m_KeyFrames;
	};

	template<class T>
	unsigned int ZG::AnimationCurve<T>::GetSize() const
	{
		return m_KeyFrames.size();
	}

	template<class T>
	bool ZG::AnimationCurve<T>::SortFunc(const KeyFrame<T>& d1, const KeyFrame<T>& d2)
	{
		return d1.m_fTime < d2.m_fTime;
	}

	template<class T>
	void ZG::AnimationCurve<T>::sort()
	{

	}

	template<class T>
	T ZG::AnimationCurve<T>::Evaluate(float fTime)
	{
		std::vector<KeyFrame<T>>::iterator iter = m_KeyFrames.begin();
		for (; iter != m_KeyFrames.end(); ++iter)
		{
			if (fTime >= iter->m_fTime)
			{
				KeyFrame<T> prev = *iter;
				std::vector<KeyFrame<T>>::iterator iterNext = iter + 1;
				if (iterNext == m_KeyFrames.end())
				{
					return prev.m_KeyFrameData;
				}
				else
				{
					float time1 = prev.m_fTime;
					float time2 = iterNext->m_fTime;
					//
					float fi = (fTime - time1) / (time2 - time1);
					return Interpolate(iter->m_KeyFrameData,iterNext->m_KeyFrameData,fi);
				}
			}
		}
	}

	template<class T>
	void ZG::AnimationCurve<T>::RemoveKeyFrame(float fTime)
	{
		std::vector<KeyFrame<T>>::iterator iter = m_KeyFrames.begin();
		for (; iter != m_KeyFrames.end(); ++iter)
		{
			if (int(iter->m_fTime * 1000) == int(fTime * 1000))
			{
				m_KeyFrames.erase(iter);
			}
		}
	}

	template<class T>
	void ZG::AnimationCurve<T>::RemoveKeyFrame(int nIndex)
	{
		if (nIndex >= m_KeyFrames.size())
		{
			return;
		}
		std::vector<KeyFrame<T>>::iterator iter = m_KeyFrames.begin();
		iter = iter + nIndex;
		m_KeyFrames.erase(iter);
		return;
	}

	template<class T>
	void ZG::AnimationCurve<T>::AddKeyFrame(float fTime, T& value)
	{
		RemoveKeyFrame(fTime);
		KeyFrame<T> keyframe(value, fTime);
		//
		m_KeyFrames.push_back(keyframe);
		sort();
		//
		if (fTime > m_fLength)
		{
			m_fLength = fTime;
		}
		
	}

	template<class T>
	ZG::AnimationCurve<T>::~AnimationCurve()
	{

	}

	template<class T>
	ZG::AnimationCurve<T>::AnimationCurve(AnimationType eType)
		:AnimationCurveBase(eType)
	{
		m_fLength = 0.0f;
		
	}

}


