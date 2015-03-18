#pragma once
#include "IWorldObj.h"
class SkeletonObj :
	public IWorldObj
{
public:
	SkeletonObj();
	virtual ~SkeletonObj();
	virtual void OnAdded();
};

