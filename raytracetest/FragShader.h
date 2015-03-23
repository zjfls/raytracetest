#pragma once
#include "IResource.h"
#include "RenderEnum.h"
class FragShaderDesc
{
public:
	ESTAGESHADERTYPE m_eStageDesc;
};
class HardwareFragShader;
class FragShader:public IResource
{
public:
	FragShader();
	virtual ~FragShader();

	HardwareFragShader* GetHardwareFragShader(const FragShaderDesc& desc) const;
};

