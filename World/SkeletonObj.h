#pragma once
#include "IWorldObj.h"
namespace ZG
{
	class WORLD_API SkeletonObj :
		public IWorldObj
	{
	public:
		SkeletonObj();
		virtual ~SkeletonObj();
		virtual void OnAdded();
	};

}