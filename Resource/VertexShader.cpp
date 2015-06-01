#include "stdafx.h"
#include "VertexShader.h"
#include "ResourceManager.h"
SmartPointer<ResourceManager<VertexShader>> Singleton<ResourceManager<VertexShader>>::_instance = nullptr;


VertexShader::VertexShader()
	:m_pCodeBuffer(nullptr)
{
}


VertexShader::~VertexShader()
{
}


