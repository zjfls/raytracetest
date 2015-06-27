#include "stdafx.h"
#include "FragShader.h"
#include "ResourceManager.h"
template class MAIN_API Singleton<ResourceManager<FragShader>>;
template<> SmartPointer<ResourceManager<FragShader>> Singleton<ResourceManager<FragShader>>::_instance = nullptr;

FragShader::FragShader()
	:m_pCodeBuffer(nullptr)
{
	
}


FragShader::~FragShader()
{
}
