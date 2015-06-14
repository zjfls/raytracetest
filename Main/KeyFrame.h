#pragma once

namespace ZG
{
	template<class T>
	class KeyFrame:public GameObjectBase
	{
	public:
		KeyFrame(const T& theData, float fTime);
		KeyFrame(){};
		virtual ~KeyFrame();

		float m_fTime;
		T m_KeyFrameData;
	};

	template<class T>
	ZG::KeyFrame<T>::~KeyFrame()
	{

	}

	template<class T>
	ZG::KeyFrame<T>::KeyFrame(const T& theData, float fTime)
		:m_fTime(fTime)
	{
		m_KeyFrameData = theData;
	}

}

