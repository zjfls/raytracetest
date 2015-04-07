#include "stdafx.h"
#include "GlobalRenderConfig.h"
template<> shared_ptr<GlobalRenderConfig> Singleton<GlobalRenderConfig>::_instance = nullptr;
template class MAIN_API  Singleton < GlobalRenderConfig >;
GlobalRenderConfig::GlobalRenderConfig()
{
	m_AmbientColor = Color();
	m_AmbientColor.m_fA = 0.0f;
	m_AmbientColor.m_fR = 0.1f;
	m_AmbientColor.m_fG = 0.1f;
	m_AmbientColor.m_fB = 0.1f;
}


GlobalRenderConfig::~GlobalRenderConfig()
{
}
