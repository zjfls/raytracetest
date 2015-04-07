#pragma once
#include "Singleton.h"
#include "Color.h"
class MAIN_API GlobalRenderConfig:public Singleton<GlobalRenderConfig>
{
public:
	GlobalRenderConfig();
	virtual ~GlobalRenderConfig();


	Color m_AmbientColor;
};

extern template class MAIN_API  Singleton < GlobalRenderConfig >;