#pragma once

#include "Singleton.h"
class MAIN_API BuiltInResource :public Singleton<BuiltInResource>
{
public:
	BuiltInResource();
	virtual ~BuiltInResource();
	

	bool InitBuiltInResource();
};

extern template class MAIN_API  Singleton < BuiltInResource >;