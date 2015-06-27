#pragma once
#include <assert.h>

namespace ZG
{
	//#include "GameObjectBase.h"
	class GameObjectBase;
	template<class T>
	class SmartPointer
	{
	public:
		SmartPointer()
			:m_pTarget(nullptr)
		{

		}
		SmartPointer(const SmartPointer<T>& pTarget);
		SmartPointer(T* pTarget);
		~SmartPointer();
		//
		unsigned int RefCount();
		//
		T* operator=(T* pTarget);
		//
		T* operator=(const SmartPointer<T>& pTarget);
		//
		T* operator->() const;
		//
		bool operator!();
		//
		bool operator==(T* t) const;
		//
		bool operator!=(T* t) const ;
		//
		bool operator==(const SmartPointer<T>& pTarget) const;
		//
		bool operator!=(const SmartPointer<T>& pTarget) const;
		//
		template<class T2>
		SmartPointer<T2> SmartPointerCast();
		//
		T& operator*();
		//
		T* get() const;
	private:
		T* m_pTarget;
	};

	template<class T> template<class T2>
	SmartPointer<T2> ZG::SmartPointer<T>::SmartPointerCast()
	{
		return SmartPointer<T2>(dynamic_cast<T2*>(m_pTarget));
	}

	template<class T>
	ZG::SmartPointer<T>::SmartPointer(const SmartPointer<T>& pTarget)
	{
		m_pTarget = pTarget.m_pTarget;
		if (m_pTarget != nullptr)
		{
			m_pTarget->m_nRefCount++;
		}
	}

	//template<class T> template<class T2>
	//T* ZG::SmartPointer<T>::operator=(const SmartPointer<T2>& pTarget)
	//{
	//	if (m_pTarget != nullptr)
	//	{
	//		m_pTarget->m_nRefCount--;
	//		if (m_pTarget->m_nRefCount == 0)
	//		{
	//			delete m_pTarget;
	//		}
	//	}
	//	T* pT2Target = dynamic_cast<T*>(pTarget.m_pTarget);
	//	if (pT2Target == nullptr)
	//	{
	//		m_pTarget = nullptr;
	//	}
	//	else
	//	{
	//		m_pTarget = pT2Target;
	//		m_pTarget->m_nRefCount++;
	//	}
	//}

	template<class T>
	T* ZG::SmartPointer<T>::get() const
	{
		return dynamic_cast<T*>(m_pTarget);
	}

	template<class T>
	T& ZG::SmartPointer<T>::operator*()
	{
		return *(dynamic_cast<T*>(m_pTarget));
	}






	template<class T>
	bool ZG::SmartPointer<T>::operator!=(const SmartPointer<T>& pTarget) const
	{
		if (m_pTarget != pTarget.m_pTarget)
		{
			return true;
		}
		return false;
	}

	template<class T>
	bool ZG::SmartPointer<T>::operator==(const SmartPointer<T>& pTarget) const
	{
		if (m_pTarget == pTarget.m_pTarget)
		{
			return true;
		}
		return false;
	}

	template<class T>
	bool ZG::SmartPointer<T>::operator!=(T* t) const
	{
		if (m_pTarget != dynamic_cast<T*>(t))
		{
			return true;
		}
		return false;
	}

	template<class T>
	bool ZG::SmartPointer<T>::operator==(T* t) const
	{
		if (m_pTarget == dynamic_cast<T*>(t))
		{
			return true;
		}
		return false;
	}


	template<class T>
	bool ZG::SmartPointer<T>::operator!()
	{
		if (m_pTarget == nullptr)
		{
			return true;
		}
		return false;
	}

	template<class T>
	T* ZG::SmartPointer<T>::operator=(const SmartPointer<T>& pTarget)
	{
		if (m_pTarget == pTarget.m_pTarget)
		{
			return (T*)m_pTarget;
		}
		if (m_pTarget != nullptr)
		{
			m_pTarget->m_nRefCount--;
			if (m_pTarget->m_nRefCount == 0)
			{
				delete m_pTarget;
			}
		}
		m_pTarget = pTarget.m_pTarget;
		if (m_pTarget != nullptr)
		{
			m_pTarget->m_nRefCount++;
		}
		return (T*)m_pTarget;
	}

	template<class T>
	T* ZG::SmartPointer<T>::operator->() const
	{
		return (T*)m_pTarget;
	}

	template<class T>
	T* ZG::SmartPointer<T>::operator=(T* pTarget)
	{
		if (m_pTarget == dynamic_cast<T*>(pTarget))
		{
			return (T*)m_pTarget;
		}
		if (m_pTarget != nullptr)
		{
			m_pTarget->m_nRefCount--;
			if (m_pTarget->m_nRefCount == 0)
			{
				delete m_pTarget;
			}
		}
		
		//assert(pTarget != nullptr);
		m_pTarget = dynamic_cast<T*>(pTarget);
		if (m_pTarget != nullptr)
		{
			m_pTarget->m_nRefCount++;
		}
		return (T*)m_pTarget;
	}

	template<class T>
	unsigned int ZG::SmartPointer<T>::RefCount()
	{
		if (m_pTarget == nullptr)
		{
			return 0;
		}
		return m_pTarget->m_nRefCount;
	}

	template<class T>
	ZG::SmartPointer<T>::~SmartPointer()
	{
		if (m_pTarget == nullptr)
		{
			return;
		}
		m_pTarget->m_nRefCount--;
		if (m_pTarget->m_nRefCount == 0)
		{
			delete m_pTarget;
			m_pTarget = nullptr;
		}
	}

	template<class T>
	ZG::SmartPointer<T>::SmartPointer(T* pTarget)
		//:m_pTarget((T*)pTarget)
	{
		m_pTarget = dynamic_cast<T*>(pTarget);
		if (m_pTarget == nullptr)
		{
			return;
		}
		m_pTarget->m_nRefCount++;
	}

}


