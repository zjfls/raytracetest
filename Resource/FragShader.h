#pragma once
#include "IResource.h"
#include "RenderEnum.h"
#include "Singleton.h"
class FragShader;
class FragShaderDesc
{
public:
	shared_ptr<FragShader> m_pFragShader;
	ESTAGESHADERTYPE m_eStageDesc;
	EFRAGSHADERTYPE	m_eFragShaderDesc;
};
class HardwareFragShader;

template <class T>
class ResourceManager;
class RESOURCE_API FragShader :public IResource
{
public:
	FragShader();
	virtual ~FragShader();

	//HardwareFragShader* GetHardwareFragShader(const FragShaderDesc& desc) const;


	const char* m_pCodeBuffer;
	friend class ResourceManager < FragShader > ;
};

RESOURCE_TEMPLATE template class RESOURCE_API  Singleton < ResourceManager<FragShader> >;
