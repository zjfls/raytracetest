#pragma once
#include "IWorldObj.h"
namespace ZG
{
	class MAIN_API SkeletonObj :
		public IWorldObj
	{
	public:
		SkeletonObj();
		virtual ~SkeletonObj();
		virtual void OnAdded();

		virtual SmartPointer<IWorldObj> Clone(bool bRecursive);
		bool m_bIsRoot;
	};

}